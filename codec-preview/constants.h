#ifndef CONSTANTS_H
#define CONSTANTS_H

#include <QString>

const QString FFMPEG = "ffmpeg";
const QString FFPROBE = "ffprobe";

const QString VIDEO_PROTOCOLS[4] = {"udp", "udp", "udp", "udp"};
const QString VIDEO_HOSTS[4] = {"224.0.0.133", "224.0.0.133", "224.0.0.133",
                                "224.0.0.133"};
const QString VIDEO_PORTS[4] = {"41291", "41292", "41293", "41294"};

const QString RAW_VIDEO_PROTOCOL = "udp";
const QString RAW_VIDEO_HOST = "224.0.0.133";
const QString RAW_VIDEO_PORT = "41291";

const QString ENCODED_VIDEO_PROTOCOL = "udp";
const QString ENCODED_VIDEO_HOST = "224.0.0.133";
const QString ENCODED_VIDEO_PORT = "41292";

const QString RAW_ADDRESS =
    RAW_VIDEO_PROTOCOL + "://" + RAW_VIDEO_HOST + ":" + RAW_VIDEO_PORT;
const QString ENCODED_ADDRESS = ENCODED_VIDEO_PROTOCOL + "://" +
                                ENCODED_VIDEO_HOST + ":" + ENCODED_VIDEO_PORT;

const QString PROBE_FILE_NAME = "PROBEFILE";

#endif // CONSTANTS_H
