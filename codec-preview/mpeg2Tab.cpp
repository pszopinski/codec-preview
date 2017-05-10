#include "mpeg2Tab.h"

MPEG2::MPEG2()
{

}

void MPEG2::start(QProcess &process)
{
    process.start(QString("ffmpeg -re -i "+getFile()+" -c:v mpeg2video -preset ultrafast -an -f mpegts udp://localhost:2000").toUtf8().constData());
}
