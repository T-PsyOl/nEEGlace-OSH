function EEG = add_events_from_markers(EEG, markerChan, threshold)
% Detects onset events from an audio marker channel and adds them to 
% the EEG event structure.
%
% Inputs:
%   EEG         - EEGLAB EEG structure
%   markerChan  - Index of the marker channel
%   threshold   - Threshold used for event detection (default = 10000)
%
% Output:
%   EEG         - EEG structure with added 'SoundOnset' events
%
% Example:
%   EGG = add_events_from_markers(EEG);
%   EEG = add_events_from_markers(EEG, 8);
%   EEG = add_events_from_markers(EEG, 8, 8000);

    if nargin < 2 || isempty(markerChan)
        markerChan = 8;
    end

    if nargin < 3 || isempty(threshold)
        threshold = 10000;
    end

    markerSignal = EEG.data(markerChan, :);
    crossings = find(diff(markerSignal >= threshold) == -1);
    display(['Events Detected: ', num2str(length(crossings))]);

    % add detected events to EEG
    for k = 1:numel(crossings)
        EEG.event(end+1).latency = crossings(k);
        EEG.event(end).type = 'SoundOnset';
    end

    EEG = eeg_checkset(EEG, 'eventconsistency');
    EEG = pop_editeventvals(EEG, 'sort', {'latency' 0});
    disp('New events added as ''SoundOnset''.')

end