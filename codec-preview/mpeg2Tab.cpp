#include "mpeg2Tab.h"

MPEG2::MPEG2()
{

}

void MPEG2::start(QProcess &process)
{
    QString command = QString("ffmpeg -re -i \""+getFile()+"\" -c:v mpeg2video -preset ultrafast -an -f matroska udp://localhost:2000 -c:v mpeg2video -preset ultrafast -an -f matroska udp://localhost:2001");
    process.start(command.toUtf8().constData());
}
