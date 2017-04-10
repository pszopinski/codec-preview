#ifndef CMDTHREAD_H
#define CMDTHREAD_H

#include <QThread>


class CmdThread : public QThread {
    Q_OBJECT

private:
    const char *command;

protected:
    void run();

public:
    void runCommand(const char *command);
};




#endif // CMDTHREAD_H
