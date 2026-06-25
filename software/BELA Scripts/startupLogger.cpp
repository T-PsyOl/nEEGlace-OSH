#include "startupLogger.h"

#include <fstream>
#include <ctime>
#include <unistd.h>
#include <cstdlib>

void appendStartupModeToFile()
{
    std::ofstream file("bela_startup_log.txt", std::ios::app);

    if(!file.is_open())
        return;

    std::time_t now = std::time(nullptr);

    bool hasTerminal = isatty(STDIN_FILENO);
    const char* systemdId = std::getenv("INVOCATION_ID");

    file << "------------------------\n";
    file << "Time: " << std::asctime(std::localtime(&now));

    if(systemdId)
        file << "Mode: boot/service mode\n";
    else if(hasTerminal)
        file << "Mode: terminal mode\n";
    else
        file << "Mode: no terminal\n";

    file << "\n";
}
