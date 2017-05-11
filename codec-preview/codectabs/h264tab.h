#ifndef H264_H
#define H264_H

#include "codectab.h"

#include "constants.h"

class H264 : public Codec
{
public:
    H264();
    void start(QProcess &process, QString file);
};

#endif // H264_H
