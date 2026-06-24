function EEG = add_event_info(EEG, csv_file) 
% add_event_info Enriches EEG event structure with external feature data.
%
% This function loads a CSV file containing audio features from nEEGlace and 
% aligns them with EEG event markers. Selected feature values are appended to 
% the  EEG.event structure under the field eventinfo.
%
% INPUTS
%   EEG       : EEGLAB EEG structure containing events.
%   csv_file  : Path to CSV file containing event features.
%
% OUTPUT
%   EEG : Updated EEG structure with additional fields in:
%         EEG.event(i).eventinfo.rms
%         EEG.event(i).eventinfo.freqcentroid
%
% ASSUMPTIONS
%   - EEG.event.type contains 'SoundOnset' markers.
%   - Each valid CSV event corresponds to exactly one EEG event.
%
% EXAMPLE
%   EEG = add_event_info(EEG, 'session1_features.csv');


    % load feature CSV 
    features           = readtable(csv_file);
    eventTime          = features{:, 1};
    eventDet           = features{:, 2};
    eventRms           = features{:, 3};
    eventCentroid      = features{:, 4};
    eventLevel         = features{:, 5};
    eventOnsetStrength = features{:, 6};
    fprintf("Loaded feature file: %s\n", csv_file);
    
    tol = 0.02;
    dt = diff(eventTime);
    good = abs(dt - 0.8) < tol;
    removeIdx = [];
    
    i = 1;
    while i <= length(good)-2
        if all(good(i:i+2))
            removeIdx = [removeIdx i:i+3];
            i = i + 4;   
        else
            i = i + 1;
        end
    end
    removeIdx = unique(removeIdx);
    st = removeIdx(1) +4;
    ed = removeIdx(end) -4;
    validIdx = st:ed;
    
    eventTime          = eventTime(validIdx);
    eventDet           = eventDet(validIdx);
    eventRms           = eventRms(validIdx);
    eventCentroid      = eventCentroid(validIdx);
    eventLevel         = eventLevel(validIdx);
    eventOnsetStrength = eventOnsetStrength(validIdx);
    
    fprintf("Valid events detected: %d\n\n", numel(eventTime));
    soundEvents = find(strcmp({EEG.event.type}, 'SoundOnset'));
    
    if numel(eventTime)== numel(soundEvents)
        for i = 1:numel(soundEvents)
            ev = soundEvents(i);
            EEG.event(ev).eventinfo.rms = eventRms(i);
            EEG.event(ev).eventinfo.freqcentroid = eventCentroid(i);
        end
    else
        error('Number of EEG events and CSV events are different');
    end
    EEG = eeg_checkset(EEG, 'eventconsistency');
    display('Event info added');

end
