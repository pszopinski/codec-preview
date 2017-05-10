#include "mjpegTab.h"

MJPEG::MJPEG()
{

}

void MJPEG::start(QProcess &process)
{
    process.start(QString("ffmpeg -re -i "+getFile()+" -c:v libx265 -preset ultrafast -an -f matroska udp://localhost:2000").toUtf8().constData());
}
