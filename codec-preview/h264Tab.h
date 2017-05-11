#ifndef H264_H
#define H264_H

#include "codecTab.h"

class H264 : public Codec
{
public:
    H264();
    void start(QProcess &process);
};


#endif // H264_H
