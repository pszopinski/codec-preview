#include "h261Tab.h"

H261::H261()
{

}

void H261::start(QProcess &process)
{
    process.start(QString("ffmpeg -re -i "+getFile()+" -c:v h261 -vf scale=352:288 -an -f matroska udp://localhost:2000").toUtf8().constData());
}
