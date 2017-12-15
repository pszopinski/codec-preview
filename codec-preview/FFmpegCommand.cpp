#include "FFmpegCommand.h"

QString FFmpegCommand::getFrameProbeCommand(QString host, QString port) {
    qDebug() << "starting probe process...";

    QString encodedAddress = ENCODED_VIDEO_PROTOCOL + "://" + host +
                             ":" + port;

    QString frameProbeCommand = buildProbeCommand(
        encodedAddress,
        "-show_frames -show_entries frame=pict_type,width,height");

    return frameProbeCommand;
}

QString FFmpegCommand::getStreamProbeCommand(QString host, QString port) {
    QString encodedAddress = ENCODED_VIDEO_PROTOCOL + "://" + host +
                             ":" + port;

    QString streamProbeCommand =
        buildProbeCommand(encodedAddress, "-show_streams -select_streams v:0");

    return streamProbeCommand;
}

QString FFmpegCommand::buildProbeCommand(QString location, QString params) {
    QStringList list;
    list << FFPROBE;
    list << location;
    list << params;

    QString command = list.join(" ");
    qDebug() << "\nproduced following probe command:\n"
             << command.toUtf8().constData() << "\n";
    return command;
}



QString
FFmpegCommand::parametersToString(QMap<QString, QString> *parameters) {
    QStringList result;

    for (auto key : parameters->keys()) {
        if (key.startsWith("-")) {
            // raw option used for check boxes
            result << key;
        }

        if (!parameters->value(key).isEmpty())
            result << "-" + key << parameters->value(key);
    }

    qDebug();
    qDebug() << parameters->keys();
    qDebug() << parameters->values();
    qDebug() << result.join(" ");
    qDebug();

    return result.join(" ");
}
