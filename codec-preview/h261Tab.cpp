#include "h261Tab.h"

H261::H261()
{

}

void H261::start(QProcess &process)
{
    QString command = QString("ffmpeg -re -i \""+getFile()+"\" -c:v h261 -vf scale=352:288 -an -f matroska udp://localhost:2000 -c:v h261 -vf scale=352:288 -an -f matroska udp://localhost:2001");
    process.start(command.toUtf8().constData());
}
