#include "h265Tab.h"
#include <iostream>

H265::H265()
{

}

void H265::start(QProcess &process)
{
    std::cout<<"h265"<<std::endl;
    process.start(QString("ffmpeg -re -i "+getFile()+" -c:v libx265 -preset ultrafast -an -f mpegts udp://localhost:2000").toUtf8().constData());
}
