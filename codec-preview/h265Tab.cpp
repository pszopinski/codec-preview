#include "h265Tab.h"

H265::H265()
{

}

void H265::start(QProcess &process)
{
    QString command = QString("ffmpeg -re -i \""+getFile()+"\" -c:v libx265 -preset ultrafast -an -f matroska udp://localhost:2000 -c:v libx265 -preset ultrafast -an -f matroska udp://localhost:2001");
    process.start(command.toUtf8().constData());
}
