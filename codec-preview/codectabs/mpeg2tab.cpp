#include "mpeg2tab.h"

MPEG2::MPEG2()
{

}

void MPEG2::start(QProcess &process, QString file)
{
    QString command = "ffmpeg -re -i \"" + file + "\" -c:v mpeg2video -preset ultrafast -an -f matroska udp://localhost:" + ENCODED_VIDEO_PORT + " -c:v mpeg2video -preset ultrafast -an -f matroska udp://localhost:"  + VIDEO_PROBE_PORT;
    process.start(command.toUtf8().constData());
}
