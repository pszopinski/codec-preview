#include "mjpegTab.h"

MJPEG::MJPEG()
{

}

void MJPEG::start(QProcess &process)
{
    QString command = QString("ffmpeg -re -i \""+getFile()+"\" -c:v libx265 -preset ultrafast -an -f matroska udp://localhost:2000 -c:v libx265 -preset ultrafast -an -f matroska udp://localhost:2001");
    process.start(command.toUtf8().constData());
}
