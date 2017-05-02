#include "h264.h"
#include <iostream>

H264::H264()
{

}

void H264::start()
{
    if(getFile() == NULL) std::cout<<"null"<<std::endl;
    else qDebug("woda"+getFile().toLatin1()+"woda");
    process.start(QString("ffmpeg -re -i  \"" + getFile() + "\" -preset ultrafast -an -strict experimental -f mpegts udp://localhost:2000").toUtf8().constData());
}
