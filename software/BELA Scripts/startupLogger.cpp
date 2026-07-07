#include "startupLogger.h"

#include <fstream>
#include <ctime>
#include <unistd.h>
#include <cstdlib>
#include <string>
#include <regex>
#include <iomanip>
#include <sstream>

int getNextRecordingNumber(const std::string& filename)
{
    std::ifstream file(filename);

    if(!file.is_open())
        return 1;   // First recording

    std::string line;
    int lastRecording = 0;

    std::regex pattern(R"(Recording\s+(\d+))");
    std::smatch match;

    while(std::getline(file, line))
    {
        if(std::regex_search(line, match, pattern))
        {
            lastRecording = std::stoi(match[1]);
        }
    }

    return lastRecording + 1;
}

std::string formatRecordingNumber(int number)
{
    std::ostringstream ss;
    ss << std::setw(4) << std::setfill('0') << number;
    return ss.str();
}

void appendStartupModeToFile()
{
    const std::string logFile = "bela_startup_log.txt";

    int recordingNumber = getNextRecordingNumber(logFile);
    std::string recording = formatRecordingNumber(recordingNumber);

    std::ofstream file(logFile, std::ios::app);

    if(!file.is_open())
        return;

    std::time_t now = std::time(nullptr);

    bool hasTerminal = isatty(STDIN_FILENO);
    const char* systemdId = std::getenv("INVOCATION_ID");

    file << "------------------------\n";
    file << "Recording " << recording << "\n";
    file << "Time: " << std::asctime(std::localtime(&now));

    if(systemdId)
        file << "Mode: boot/service mode\n";
    else if(hasTerminal)
        file << "Mode: terminal mode\n";
    else
        file << "Mode: no terminal\n";
	
    file << "Feature File: audio_features_recording_" << recording << "\n";
    file << "\n";
}
