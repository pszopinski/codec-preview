#include "mjpegTab.h"

MJPEG::MJPEG()
{

}

void MJPEG::start(QProcess &process)
{
    process.start(QString("ffmpeg -re -i "+getFile()+" -c:v mjpeg -preset ultrafast -an -f mpegts udp://localhost:2000").toUtf8().constData());
}
