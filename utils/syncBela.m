function syncBela(savepath, project_name, ip_address, deleteAfterSync)
% syncBela saves audio files from Bela device to the local machine.
% Optionally deletes the files from Bela after successful synchronization.
%
% Inputs:
%   savepath        - Local directory where files will be saved
%   project_name    - Name of the Bela project folder
%   ip_address      - IP address of the Bela device
%   deleteAfterSync - (optional) true/false. If true, files are deleted
%                     from Bela after syncing. Default = false.
%
% Example:
%   syncBela(savepath, project_name, ip_address)
%   syncBela(savepath, project_name, ip_address, true)

    % default value
    if nargin < 4
        deleteAfterSync = false;
    end

    % create local directory if not exist
    if ~exist(savepath,'dir')
        mkdir(savepath);
    end

    % define file patterns to be copied from the Bela device
    files2load = {'audiofile_*', 'audio_features_*'};

    % testing SSH connection to the Bela device
    testCmd = sprintf('ssh root@%s "echo connection_ok"', ip_address);
    status = system(testCmd);

    % checking connection status
    if status ~= 0
        error(['Cannot connect to Bela at %s. Please make sure Bela ' ...
               'is connected to the computer via USB.'], ip_address);
    end

    % sync files
    for k = 1:length(files2load)

        % copy files
        copyCmd = sprintf(['scp root@%s:/root/Bela/projects/%s/%s "%s"'], ...
                          ip_address, project_name, files2load{k}, savepath);

        status = system(copyCmd);

        % optionally delete after successful copy
        if deleteAfterSync && status == 0
            deleteCmd = sprintf(['ssh root@%s "rm -f ' ...
                                 '/root/Bela/projects/%s/%s"'], ...
                                 ip_address, project_name, files2load{k});
            system(deleteCmd);
        end
    end
    
    dir(savepath)

    fprintf('\nSync completed.\n');

    if deleteAfterSync
        fprintf('Source files deleted from Bela.\n');
    end

    
end