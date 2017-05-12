#ifndef H264_H
#define H264_H

#include "codecmanager.h"

#include "constants.h"

class H264Manager : public CodecManager
{
public:
    H264Manager();
    void start(QProcess &process, QString file);
};

#endif // H264_H
