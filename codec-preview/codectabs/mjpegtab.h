#ifndef MJPEG_H
#define MJPEG_H

#include "codectab.h"

#include "constants.h"

class MJPEG : public Codec
{
public:
    MJPEG();
    void start(QProcess &process, QString file);
};

#endif // MJPEG_H
