#include "avc.h"

AVC::AVC()
{

}

void AVC::start()
{
    process.start(QString("ffmpeg -re -i  \"" + getFile() + "\" -preset ultrafast -an -strict experimental -f mpegts udp://localhost:2000").toUtf8().constData());
}
