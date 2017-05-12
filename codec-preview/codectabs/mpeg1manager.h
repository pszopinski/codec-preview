#ifndef MPEG1_H
#define MPEG1_H

#include "codecmanager.h"

#include "constants.h"

class MPEG1Manager : public CodecManager
{
public:
    MPEG1Manager();
    void start(QProcess &process, QString file);
};

#endif // MPEG1_H
