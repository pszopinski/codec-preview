#include "codectabswidget.h"
#include "ui_codectabswidget.h"

CodecTabsWidget::CodecTabsWidget(QWidget *parent)
    : QWidget(parent), ui(new Ui::CodecTabsWidget) {
    ui->setupUi(this);

    ui->tabWidget->setCurrentIndex(0);

    connect(ui->tabWidget, &QTabWidget::currentChanged, this,
            &CodecTabsWidget::onTabChange);

    // push all ui tabs into vector
    codecManagers.push_back(ui->mjpegtab);
    codecManagers.last()->setCodecName("MJPEG");
    codecManagers.push_back(ui->h261tab);
    codecManagers.last()->setCodecName("H261");
    codecManagers.push_back(ui->mpeg1tab);
    codecManagers.last()->setCodecName("MPEG1");
    codecManagers.push_back(ui->mpeg2tab);
    codecManagers.last()->setCodecName("MPEG2");
    codecManagers.push_back(ui->h264tab);
    codecManagers.last()->setCodecName("H264");
    codecManagers.push_back(ui->h265tab);
    codecManagers.last()->setCodecName("H265");

    // connect codec managers' signals to settingsChanged
    for (auto codecManager : codecManagers) {
        connect(codecManager, &CodecManager::parametersChanged, this,
                &CodecTabsWidget::settingsChanged);
    }

    connect(&cameraNameGetterProcess,
            SIGNAL(finished(int, QProcess::ExitStatus)), this,
            SLOT(parseCameraNameProbeOutput(int, QProcess::ExitStatus)));
}

CodecTabsWidget::~CodecTabsWidget() { delete ui; }

void CodecTabsWidget::setSelectedCodecs(int first, int second, int third) {
    qDebug() << "selected codecs: " << first << second << third;

    QString streamingParameters1 = "-c:v copy -f nut -an";
    QString streamingParameters2 =
        parametersToString(codecManagers.at(first)->getStreamingParameters());
    QString streamingParameters3 =
        parametersToString(codecManagers.at(second)->getStreamingParameters());
    QString streamingParameters4 =
        parametersToString(codecManagers.at(third)->getStreamingParameters());

    qDebug() << "streaming parameters:";
    qDebug() << streamingParameters1;
    qDebug() << streamingParameters2;
    qDebug() << streamingParameters3;
    qDebug() << streamingParameters4;

    QString streamingCommand = buildStreamingCommand(
        inputParameters, inputLocation,
        {streamingParameters1, streamingParameters2, streamingParameters3,
         streamingParameters4},
        {VIDEO_PROTOCOLS[0] + "://" + VIDEO_HOSTS[0] + ":" + VIDEO_PORTS[0],
         VIDEO_PROTOCOLS[1] + "://" + VIDEO_HOSTS[1] + ":" + VIDEO_PORTS[1],
         VIDEO_PROTOCOLS[2] + "://" + VIDEO_HOSTS[2] + ":" + VIDEO_PORTS[2],
         VIDEO_PROTOCOLS[3] + "://" + VIDEO_HOSTS[3] + ":" + VIDEO_PORTS[3]});

    qDebug() << "streaming command:";

    qDebug() << streamingCommand;
    showCodecs.original->setText("Original");
    showCodecs.label1->setText(codecManagers.at(first)->getCodecName());
    showCodecs.label2->setText(codecManagers.at(second)->getCodecName());
    showCodecs.label3->setText(codecManagers.at(third)->getCodecName());
    showCodecs.show();
    showCodecs.broadcast(streamingCommand);
}

void CodecTabsWidget::stopStreaming() {
    streamingProcess.kill();
    streamingProcess.waitForFinished();
}

QString CodecTabsWidget::buildStreamingCommand(QString inputParameters,
                                               QString inputLocation,
                                               QString outputPrameters,
                                               QString rawLocation,
                                               QString encodedLocation) {
    QStringList list;
    list << FFMPEG;
    list << inputParameters;
    list << "-i " << inputLocation;

    list << "-c:v copy -f nut -an" << rawLocation,

        list << outputPrameters << encodedLocation + "?ttl=0";

    QString command = list.join(" ");
    qDebug() << "produced following encoding command:\n"
             << command.toUtf8().constData();
    return command;
}

QString CodecTabsWidget::buildProbeCommand(QString location, QString params) {
    QStringList list;
    list << FFPROBE;
    list << location;
    list << params;

    QString command = list.join(" ");
    qDebug() << "produced following probe command:\n"
             << command.toUtf8().constData();
    return command;
}

QString
CodecTabsWidget::parametersToString(QMap<QString, QString> *parameters) {
    QStringList result;

    for (auto key : parameters->keys()) {
        if (!parameters->value(key).isEmpty())
            result << "-" + key << parameters->value(key);
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

    cameraNameGetterProcess.kill();
    cameraNameGetterProcess.waitForFinished();
    cameraNameGetterProcess.start(
        "ffmpeg -list_devices true -f dshow -i dummy");

    // when process is done parseCameraNameProbeOutput runs and opens camera

#else
    inputParameters = "-f v4l2";
    inputLocation = "/dev/video0";
    settingsChanged();
#endif
}

void CodecTabsWidget::onTabChange() { currentTabChanged(); }

QString CodecTabsWidget::getStreamingParameters() {
    if (inputLocation.isEmpty()) {
        return "";
    }
    if (inputParameters.isEmpty()) {
        return "";
    }
    QMap<QString, QString> *streamingParametersMap =
        codecManagers.at(ui->tabWidget->currentIndex())
            ->getStreamingParameters();
    if (streamingParametersMap->isEmpty()) {
        return "";
    }

    QString streamingParameters =
        parametersToString(streamingParametersMap) + " -an";

    return streamingParameters;
}

void CodecTabsWidget::startStreaming(QString streamingParameters) {
    qDebug() << "starting encoding process...";
    QString streamingCommand = buildStreamingCommand(
        inputParameters, inputLocation, streamingParameters, RAW_ADDRESS,
        ENCODED_ADDRESS);
    streamingProcess.start(streamingCommand);
}

QString CodecTabsWidget::getProbeCommand() {
    qDebug() << "starting probe process...";

    QString frameProbeCommand = buildProbeCommand(
        VIDEO_PROBE_PROTOCOL + "://" + VIDEO_PROBE_HOST + ":" +
            VIDEO_PROBE_PORT,
        "-show_frames -show_entries frame=pict_type,width,height");

    return frameProbeCommand;
}

QString CodecTabsWidget::getStreamCommand() {
    QString streamProbeCommand =
        buildProbeCommand(ENCODED_ADDRESS, "-show_streams -select_streams v:0");

    return streamProbeCommand;
}

void CodecTabsWidget::parseCameraNameProbeOutput(int a,
                                                 QProcess::ExitStatus b) {
    // silence warning
    (void)a;
    (void)b;

    QRegularExpression re("\"(.*?)\"");
    QRegularExpressionMatch match =
        re.globalMatch(cameraNameGetterProcess.readAllStandardError()).next();

    inputLocation =
        QString("video=") + QString(match.captured().toUtf8().constData());
    settingsChanged();

    qDebug() << inputLocation;
}
