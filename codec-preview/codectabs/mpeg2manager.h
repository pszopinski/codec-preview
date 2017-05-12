#ifndef MPEG2_H
#define MPEG2_H

#include "codecmanager.h"

#include "constants.h"

class MPEG2Manager : public CodecManager
{
public:
    MPEG2Manager();
    void start(QProcess &process, QString file);
};

#endif // MPEG2_H
