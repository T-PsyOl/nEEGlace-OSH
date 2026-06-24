function playTriggerCode(value)
% playTriggerCode Plays a 4-bit trigger code as an audio pulse sequence.
%
% This function encodes an integer value between 0 and 15 into a 4-bit
% binary representation and transmits it using audio pulses. 
%
% This is used as manual trigger markers for nEEGlace to indicate start/stop 
% of the experiment or any such required manual markers.  
%
% INPUT
%   value : Integer between 0 and 15 (inclusive).
%
% EXAMPLES
%   playTriggerCode(5)
%
% REQUIREMENTS
%   - Psychtoolbox must be installed.
%   - InitializePsychSound and PsychPortAudio must be available.

    assert(value >= 0 && value <= 15, ...
        'Value must be between 0 and 15');

    bits = dec2bin(value,4) - '0';

    fs = 44100;
    pulseDur = 0.1;
    gapDur = 0.7;
    freq = 1000;
    amp = 0.9;

    InitializePsychSound(1);

    pahandle = PsychPortAudio('Open', [], 1, 1, fs, 1);

    tPulse = 0:1/fs:pulseDur-1/fs;
    pulse = amp*sin(2*pi*freq*tPulse);

    gap = zeros(1, round(gapDur*fs));

    signal = [];

    for i = 1:4

        if bits(i)
            signal = [signal pulse];
        else
            signal = [signal zeros(size(pulse))];
        end

        if i < 4
            signal = [signal gap];
        end
    end

    PsychPortAudio('FillBuffer', pahandle, signal);

    startTime = PsychPortAudio('Start', pahandle, 1, 0, 1);

    fprintf('Played code: %s at %.6f s\n', dec2bin(value,4), startTime);

    PsychPortAudio('Stop', pahandle, 1);
    PsychPortAudio('Close', pahandle);

end