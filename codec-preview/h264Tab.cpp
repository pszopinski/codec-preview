#include "h264Tab.h"
#include <iostream>

H264::H264()
{

}

void H264::start(QProcess &process)
{
    std::cout<<"h264"<<std::endl;
    process.start(QString("ffmpeg -re -i "+getFile()+" -c:v libx264 -preset ultrafast -an -f mpegts udp://localhost:2000").toUtf8().constData());
}
