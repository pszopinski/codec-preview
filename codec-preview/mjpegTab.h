#ifndef MJPEG_H
#define MJPEG_H

#include "codecTab.h"

class MJPEG : public Codec
{
public:
    MJPEG();
    void start(QProcess &process);
};

#endif // MJPEG_H
