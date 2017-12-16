#include "FFmpegCommand.h"

QString FFmpegCommand::getFrameProbeCommand(QString host, QString port) {
    qDebug() << "starting probe process...";

    QString encodedAddress = ENCODED_VIDEO_PROTOCOL + "://" + host + ":" + port;

    QString frameProbeCommand =
        buildProbeCommand(encodedAddress, "-show_frames -show_entries frame=pict_type,width,height");

    return frameProbeCommand;
}

QString FFmpegCommand::getStreamProbeCommand(QString host, QString port) {
    QString encodedAddress = ENCODED_VIDEO_PROTOCOL + "://" + host + ":" + port;

    QString streamProbeCommand = buildProbeCommand(encodedAddress, "-show_streams -select_streams v:0");

    return streamProbeCommand;
}

QString FFmpegCommand::buildProbeCommand(QString location, QString params) {
    QStringList list;
    list << FFPROBE;
    list << location;
    list << params;

    QString command = list.join(" ");
    qDebug() << "\nproduced following probe command:\n" << command.toUtf8().constData() << "\n";
    return command;
}

QString FFmpegCommand::parametersToString(QMap<QString, QString> *parameters) {
    QStringList result;

    // We will store filters to consolidate and consolidate them later
    QStringList filters;

    for (auto key : parameters->keys()) {
        if (key.startsWith("-")) {
            if (key.startsWith("-vf")) {
                // filter out raw -vf parameter
                filters << key.mid(4);
            } else {
                // add raw parameter
                result << key;
            }
        }

        if (!parameters->value(key).isEmpty()) {
            if (key == "vf") {
                // filter out regular -vf parameter
                filters << parameters->value(key);
            } else {
                // add a regular parameter
                result << "-" + key << parameters->value(key);
            }
        }
    }

    // Consolidate filters
    result << "-vf \"" + filters.join(", ") + "\"";

    return result.join(" ");
}
