#include "h265manager.h"

H265Manager::H265Manager()
{
    encodingParameters = "-c:v libx265 -preset ultrafast -f matroska";
}

void H265Manager::start(QProcess &process, QString file)
{
    QString command = "ffmpeg -re -i \"" + file + "\" -c:v libx265 -preset ultrafast -an -f matroska udp://localhost:" + ENCODED_VIDEO_PORT + " -c:v libx265 -preset ultrafast -an -f matroska udp://localhost:"  + VIDEO_PROBE_PORT;
    process.start(command.toUtf8().constData());
}
