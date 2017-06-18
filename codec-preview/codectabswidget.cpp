#include "codectabswidget.h"
#include "ui_codectabswidget.h"

CodecTabsWidget::CodecTabsWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CodecTabsWidget)
{
    ui->setupUi(this);


    ui->tabWidget->setCurrentIndex(0);

    connect(ui->tabWidget, &QTabWidget::currentChanged, this, CodecTabsWidget::onTabChange);

    codecManagers.push_back(ui->mjpegtab);
    codecManagers.push_back(ui->h261tab);
    codecManagers.push_back(ui->mpeg1tab);
    codecManagers.push_back(ui->mpeg2tab);
    codecManagers.push_back(ui->h264tab);
    codecManagers.push_back(ui->h265tab);

}

CodecTabsWidget::~CodecTabsWidget()
{
    delete ui;
}



void CodecTabsWidget::setSelectedCodecs(int first, int second,
                                              int third) {
    qDebug() << "Selected codecs: " << first << second << third;

    QString streamingParameters1 = "-c:v copy -f nut -an";
    QString streamingParameters2 =
        parametersToString(codecManagers.at(first)->getStreamingParameters()) + " -an";
    QString streamingParameters3 =
        parametersToString(codecManagers.at(second)->getStreamingParameters()) + " -an";
    QString streamingParameters4 =
        parametersToString(codecManagers.at(third)->getStreamingParameters()) + " -an";

    qDebug() << "Streaming parameters:";
    qDebug() << streamingParameters1;
    qDebug() << streamingParameters2;
    qDebug() << streamingParameters3;
    qDebug() << streamingParameters4;

    QString streamingCommand1 = buildStreamingCommand(
        inputParameters, inputLocation, {streamingParameters1},
        {VIDEO_PROTOCOLS[0] + "://" + VIDEO_HOSTS[0] + ":" + VIDEO_PORTS[0]});
    QString streamingCommand2 = buildStreamingCommand(
        inputParameters, inputLocation, {streamingParameters2},
        {VIDEO_PROTOCOLS[1] + "://" + VIDEO_HOSTS[1] + ":" + VIDEO_PORTS[1]});
    QString streamingCommand3 = buildStreamingCommand(
        inputParameters, inputLocation, {streamingParameters3},
        {VIDEO_PROTOCOLS[2] + "://" + VIDEO_HOSTS[2] + ":" + VIDEO_PORTS[2]});
    QString streamingCommand4 = buildStreamingCommand(
        inputParameters, inputLocation, {streamingParameters4},
        {VIDEO_PROTOCOLS[3] + "://" + VIDEO_HOSTS[3] + ":" + VIDEO_PORTS[3]});

    qDebug() << "Streaming commands:";
    qDebug() << streamingCommand1;
    qDebug() << streamingCommand2;
    qDebug() << streamingCommand3;
    qDebug() << streamingCommand4;

    showCodecs.show();
    showCodecs.broadcast(streamingCommand1, streamingCommand2,
                         streamingCommand3, streamingCommand4);
}

QVector<CodecManager *> CodecTabsWidget::getCodecManagers() {
    return codecManagers;
}


void CodecTabsWidget::stopStreaming() {
    streamingProcess.kill();
    streamingProcess.waitForFinished();
}


QString CodecTabsWidget::buildStreamingCommand(
    QString inputParameters, QString inputLocation,
    QVector<QString> outputPrameters, QVector<QString> outputLocations) {
    QStringList list;
    list << FFMPEG;
    list << inputParameters;
    list << "-i " << inputLocation;
    for (int i = 0;
         i < outputPrameters.length() && i < outputLocations.length(); i++) {
        list << outputPrameters[i] << outputLocations[i];
    }

    QString command = list.join(" ");
    qDebug() << "Produced the following encoding command:\n"
             << command.toUtf8().constData();
    return command;
}

QString CodecTabsWidget::buildProbeCommand(QString location, QString params) {
    QStringList list;
    list << FFPROBE;
    list << location;
    list << params;

    QString command = list.join(" ");
    qDebug() << "Produced the following probe command:\n"
             << command.toUtf8().constData();
    return command;
}

QString CodecTabsWidget::parametersToString(QMap<QString, QString> parameters) {
    QStringList result;

    for(auto key : parameters.keys())
    {
      result << "-" + key << parameters.value(key);
    }

    return result.join(" ");
}

void CodecTabsWidget::openFromFile(QString filePath) {
    if (!filePath.isEmpty()) {
        inputParameters = "-re";
        inputLocation = "\"" + filePath + "\"";
        settingsChanged();
    }
}

void CodecTabsWidget::openFromCamera() {
    #ifdef Q_OS_WIN
        inputParameters = "-f dshow";
        inputLocation = "video=\"Lenovo EasyCamera\"";
        settingsChanged();
    #else
        inputParameters = "-f v4l2";
        inputLocation = "/dev/video0";
        settingsChanged();
    #endif
}

void CodecTabsWidget::onTabChange() {
    currentTabChanged();
}


QString CodecTabsWidget::getStreamingParameters() {
    if (inputLocation.isEmpty()) {
        qDebug() << "Input location is missing! Not starting player.";
        return "";
    }
    if (inputParameters.isEmpty()) {
        qDebug() << "Input parameters are missing! Not starting player.";
        return "";
    }
    QMap<QString, QString> streamingParametersMap =
        codecManagers.at(ui->tabWidget->currentIndex())
            ->getStreamingParameters();
    if (streamingParametersMap.isEmpty()) {
        qDebug() << "Encoding parameters are missing! Not starting player.";
        return "";
    }

    QString streamingParameters = parametersToString(streamingParametersMap) + " -an";

    return streamingParameters;
}


void CodecTabsWidget::startStreaming(QString streamingParameters) {
    qDebug() << "Starting the encoding process...";
    QString streamingCommand = buildStreamingCommand(
        inputParameters, inputLocation,
        {"-c:v copy -f nut -an", streamingParameters, streamingParameters, streamingParameters},
        {RAW_VIDEO_PROTOCOL + "://" + RAW_VIDEO_HOST + ":" + RAW_VIDEO_PORT,
         ENCODED_VIDEO_PROTOCOL + "://" + ENCODED_VIDEO_HOST + ":" + ENCODED_VIDEO_PORT,
         VIDEO_PROBE_PROTOCOL + "://" + VIDEO_PROBE_HOST + ":" + VIDEO_PROBE_PORT,
         STREAM_PROBE_PROTOCOL + "://" + STREAM_PROBE_HOST + ":" + STREAM_PROBE_PORT       });
    streamingProcess.start(streamingCommand);
}


QString CodecTabsWidget::getProbeCommand() {
    qDebug() << "Starting the probe process...";

    QString frameProbeCommand =
        buildProbeCommand(VIDEO_PROBE_PROTOCOL + "://" + VIDEO_PROBE_HOST +
                          ":" + VIDEO_PROBE_PORT, "-show_frames -show_entries frame=pict_type,width,height");

    return frameProbeCommand;

}

QString CodecTabsWidget::getStreamCommand() {
    QString streamProbeCommand =
            buildProbeCommand(STREAM_PROBE_PROTOCOL + "://" + STREAM_PROBE_HOST +
                              ":" + STREAM_PROBE_PORT, "-show_streams -select_streams v:0");

    return streamProbeCommand;
}

void CodecTabsWidget::setCRF(QString value) {
    codecManagers.at(ui->tabWidget->currentIndex())->setCRF(value);
    settingsChanged();
}
