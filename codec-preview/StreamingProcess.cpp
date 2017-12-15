#include "StreamingProcess.h"

StreamingProcess::StreamingProcess()
{

}


QString StreamingProcess::buildStreamingCommand(QString inputParameters,
                                               QString inputLocation,
                                               QString outputPrameters,
                                               QString rawLocation,
                                               QString encodedLocation) {
    QStringList list;
    list << FFMPEG;
    list << "-flags2 +export_mvs";
    list << inputParameters;
    list << "-i " << inputLocation;

    // TEMPORARY CHANGE FROM COPY TO MJPEG
    // PP: mjpeg
    list << "-f nut -an" << rawLocation + "?ttl=0";

    list << outputPrameters << encodedLocation + "?ttl=0";

    QString command = list.join(" ");
    qDebug() << "\nproduced following encoding command:\n"
             << command.toUtf8().constData() << "\n";
    return command;
}


void StreamingProcess::startStreaming(QString streamingParameters) {
    qDebug() << "starting encoding process...";

    QString rawAddress =
        RAW_VIDEO_PROTOCOL + "://" + rawVideoHost + ":" + rawVideoPort;
    QString encodedAddress = ENCODED_VIDEO_PROTOCOL + "://" + encodedVideoHost +
                             ":" + encodedVideoPort;

    QString streamingCommand =
        buildStreamingCommand(inputParameters, inputLocation,
                              streamingParameters, rawAddress, encodedAddress);
    start(streamingCommand);
}


void StreamingProcess::stopStreaming() {
    kill();
    waitForFinished();
}

void StreamingProcess::setInputLocation(QString location) {
    this->inputLocation = location;
}

void StreamingProcess::setInputParameters(QString parameters) {
    this->inputParameters = parameters;
}

QString StreamingProcess::getInputLocation() {
    return inputLocation;
}
QString StreamingProcess::getInputParameters() {
    return inputParameters;
}
