function syncBela(savepath, project_name, ip_address)
% syncBela saves audio files from Bela device to the local machine.
% ![IMPORTANT] Make sure the Bela decice is conencted via USB before
% running the script. 
%
%   Inputs:
%       savepath     - Local directory where files will be saved (string/char)
%       project_name - Name of the Bela project folder on the device (string/char)
%       ip_address   - IP address of the Bela device (string/char)
%
%   The function retrieves files matching:
%       - audiofile_*
%       - audio_features_*
%
%   Example:
%       syncBela(savepath, project_name, ip_address);

    % create local directory if not exist
    if ~exist(savepath,'dir')
        mkdir(savepath);
    end
    
    % define file patterns to be copied from the Bela device
    files2load = { 'audiofile_*','audio_features_*' };

    % testing SSH connection to the Bela device
    testCmd = sprintf('ssh root@%s "echo connection_ok"', ip_address);
    status = system(testCmd);

    % checking connection status
    if status ~= 0
        error('Cannot connect to Bela at %s. Please make sure Bela is connected to the computer via USB.', ip_address);
    else    
        % if connected loop through files and save them 
        for k = 1:length(files2load)
            cmd = sprintf(['scp root@', ip_address, ':/root/Bela/projects/', project_name, '/%s "%s"'], files2load{k}, savepath);
            system(cmd);
        end
    end 
end 