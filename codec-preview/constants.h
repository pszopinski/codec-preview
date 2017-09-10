#ifndef CONSTANTS_H
#define CONSTANTS_H

#include <QString>

const QString FFMPEG = "ffmpeg";
const QString FFPROBE = "ffprobe";

/*
const QString VIDEO_PROTOCOLS[4] = {"udp", "udp", "udp", "udp"};
const QString VIDEO_HOSTS[4] = {"localhost", "localhost", "localhost",
                                "localhost"};
const QString VIDEO_PORTS[4] = {"41291", "41292", "41293", "41294"};

const QString RAW_VIDEO_PROTOCOL = "udp";
const QString RAW_VIDEO_HOST = "localhost"; //"231.25.66.0";
const QString RAW_VIDEO_PORT = "41295";

const QString ENCODED_VIDEO_PROTOCOL = "udp";
const QString ENCODED_VIDEO_HOST = "localhost"; //"231.25.66.0";
const QString ENCODED_VIDEO_PORT = "41296";

const QString VIDEO_PROBE_PROTOCOL = "udp";
const QString VIDEO_PROBE_HOST = "localhost"; //"231.25.66.0";
const QString VIDEO_PROBE_PORT = "41297";

const QString STREAM_PROBE_PROTOCOL = "udp";
const QString STREAM_PROBE_HOST = "localhost"; //"231.25.66.0";
const QString STREAM_PROBE_PORT = "41303";
*/

const QString RAW_VIDEO_PROTOCOL = "udp";
const QString RAW_VIDEO_HOST = "localhost";
const QString RAW_VIDEO_PORT = "41291";

const QString ENCODED_VIDEO_PROTOCOL = "udp";
const QString ENCODED_VIDEO_HOST = "224.0.0.133";
const QString ENCODED_VIDEO_PORT = "41292";

const QString RAW_ADDRESS = RAW_VIDEO_PROTOCOL + "://" + RAW_VIDEO_HOST + ":" + RAW_VIDEO_PORT;
const QString ENCODED_ADDRESS = ENCODED_VIDEO_PROTOCOL + "://" + ENCODED_VIDEO_HOST + ":" + ENCODED_VIDEO_PORT;

const QString PROBE_FILE_NAME = "PROBEFILE";

#endif // CONSTANTS_H
