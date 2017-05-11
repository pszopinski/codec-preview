#include "avc.h"
#include <iostream>

AVC::AVC()
{

}

void AVC::start(QProcess &process)
{
    std::cout<<&process<<std::endl;
    process.start(QString("ffmpeg -re -i  \"" + getFile() + "\" -preset ultrafast -an -strict experimental -f mpegts udp://localhost:2000").toUtf8().constData());
}
