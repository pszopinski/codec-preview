#include "h264Tab.h"

H264::H264()
{

}

void H264::start(QProcess &process)
{
    QString command = QString("ffmpeg -re -i \""+getFile()+"\" -c:v libx264 -preset ultrafast -an -f matroska udp://localhost:2000 -c:v libx264 -preset ultrafast -an -f matroska udp://localhost:2001");
    process.start(command.toUtf8().constData());
}
