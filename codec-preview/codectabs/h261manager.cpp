#include "h261manager.h"

H261Manager::H261Manager()
{

}

void H261Manager::start(QProcess &process, QString file)
{
    QString command = "ffmpeg -re -i \"" + file + "\" -c:v h261 -vf scale=352:288 -an -f matroska udp://localhost:" + QString::number(ENCODED_VIDEO_PORT) + " -c:v h261 -vf scale=352:288 -an -f matroska udp://localhost:" + QString::number(VIDEO_PROBE_PORT);
    process.start(command.toUtf8().constData());
}
