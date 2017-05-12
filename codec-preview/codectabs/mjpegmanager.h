#ifndef MJPEG_H
#define MJPEG_H

#include "codecmanager.h"

#include "constants.h"

class MJPEGManager : public CodecManager
{
public:
    MJPEGManager();
    void start(QProcess &process, QString file);
};

#endif // MJPEG_H
