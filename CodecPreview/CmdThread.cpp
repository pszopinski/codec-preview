#include "CmdThread.h"

void CmdThread::run()
{

    system(command);

}

void CmdThread::runCommand(const char *command) {
    this->command = command;
    start();
}
