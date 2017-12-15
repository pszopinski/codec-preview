#ifndef CONSTANTS_H
#define CONSTANTS_H

#include <QDir>
#include <QString>

const QString WORKING_DIR = QDir::currentPath();

const QString FFMPEG = WORKING_DIR + "/ffmpeg/bin/ffmpeg";
const QString FFPROBE = WORKING_DIR + "/ffmpeg/bin/ffprobe";

const QString VIDEO_HOSTS[4] = {"224.0.0.140", "224.0.0.140", "224.0.0.140",
                                "224.0.0.140"};
const QString VIDEO_PORTS[4] = {"41291", "41292", "41293", "41294"};

const QString RAW_VIDEO_PROTOCOL = "udp";
const QString RAW_VIDEO_HOST = "224.0.0.20";
const QString RAW_VIDEO_PORT = "41291";

const QString ENCODED_VIDEO_PROTOCOL = "udp";
const QString ENCODED_VIDEO_HOST = "224.0.0.20";
const QString ENCODED_VIDEO_PORT = "41292";

/*const QString RAW_ADDRESS =
    RAW_VIDEO_PROTOCOL + "://" + RAW_VIDEO_HOST + ":" + RAW_VIDEO_PORT;
const QString ENCODED_ADDRESS = ENCODED_VIDEO_PROTOCOL + "://" +
                                ENCODED_VIDEO_HOST + ":" + ENCODED_VIDEO_PORT;*/

extern QString rawVideoHost;
extern QString encodedVideoHost;
extern QString rawVideoPort;
extern QString encodedVideoPort;

extern QString compareWindowHosts[4];
extern QString compareWindowPorts[4];

const QString PROBE_FILE_NAME = "PROBEFILE";
const QString STATS_FILE_NAME = "statistics.txt";

#endif // CONSTANTS_H
