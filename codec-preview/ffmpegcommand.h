#ifndef FFMPEGCOMMAND_H
#define FFMPEGCOMMAND_H

#include <QDebug>
#include <QString>

#include "constants.h"

class FfmpegCommand {
  public:
    static QString getFrameProbeCommand(QString host, QString port);
    static QString getStreamProbeCommand(QString host, QString port);
    static QString buildProbeCommand(QString location, QString params);
};

#endif // FFMPEGCOMMAND_H
