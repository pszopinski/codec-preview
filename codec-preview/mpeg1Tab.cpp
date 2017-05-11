#include "mpeg1Tab.h"

MPEG1::MPEG1()
{

}

void MPEG1::start(QProcess &process)
{
    process.start(QString("ffmpeg -re -i "+getFile()+" -c:v mpeg1video -preset ultrafast -an -f matroska udp://localhost:2000").toUtf8().constData());
}
