#include "h261manager.h"

H261Manager::H261Manager()
{
    encodingParameters = "-c:v h261 -filter:v scale=352:288:force_original_aspect_ratio=decrease,pad=352:288:(ow-iw)/2:(oh-ih)/2 -f matroska";
}

void H261Manager::start(QProcess &process, QString file)
{
    QString command = "ffmpeg -re -i \"" + file + "\" -c:v h261 -vf scale=352:288 -an -f matroska udp://localhost:" + ENCODED_VIDEO_PORT + " -c:v h261 -vf scale=352:288 -an -f matroska udp://localhost:" + VIDEO_PROBE_PORT;
    process.start(command.toUtf8().constData());
}
