#include "CodecTabsWidget.h"
#include "ui_codectabswidget.h"

CodecTabsWidget::CodecTabsWidget(QWidget *parent)
    : QWidget(parent), ui(new Ui::CodecTabsWidget) {
    ui->setupUi(this);

    ui->tabWidget->setCurrentIndex(0);

    connect(ui->tabWidget, &QTabWidget::currentChanged, this,
            &CodecTabsWidget::onTabChange);

    codecWidgets.push_back(
        new CodecParametersWidget("mjpeg", "mjpeg", "matroska", this));
    codecWidgets.last()->setCodecName("MJPEG");
    codecWidgets.push_back(
        new CodecParametersWidget("h261", "h261", "matroska", this));
    codecWidgets.last()->setCodecName("H261");
    codecWidgets.push_back(
        new CodecParametersWidget("mpeg1", "mpeg1video", "mpegts", this));
    codecWidgets.last()->setCodecName("MPEG1");
    codecWidgets.push_back(
        new CodecParametersWidget("mpeg2", "mpeg2video", "mpegts", this));
    codecWidgets.last()->setCodecName("MPEG2");
    codecWidgets.push_back(
        new CodecParametersWidget("h264", "libx264", "matroska", this));
    codecWidgets.last()->setCodecName("H264");
    codecWidgets.push_back(
        new CodecParametersWidget("h265", "libx265", "matroska", this));
    codecWidgets.last()->setCodecName("H265");

    // connect codec managers' signals to settingsChanged
    for (auto codecWidget : codecWidgets) {

        ui->tabWidget->addTab(codecWidget, codecWidget->getCodecName());

        connect(codecWidget, &CodecParametersWidget::parametersChanged, this,
                &CodecTabsWidget::settingsChanged);
    }

    for (int i = 0; i < 6; i++) {
        // connect(compareWindow.getManager(i),
        // &CodecWidget::parametersChanged, this,
        // &CodecTabsWidget::compareWindowStream);
        connect(compareWindow.getManager(i), SIGNAL(parametersChanged()), this,
                SLOT(compareWindowStream()));
    }

    connect(&cameraNameGetterProcess,
            SIGNAL(finished(int, QProcess::ExitStatus)), this,
            SLOT(parseCameraNameProbeOutput(int, QProcess::ExitStatus)));

    connect(&singleFrameProcess, SIGNAL(finished(int, QProcess::ExitStatus)),
            this, SLOT(onSingleFrameGotten(int, QProcess::ExitStatus)));
}

CodecTabsWidget::~CodecTabsWidget() { delete ui; }

void CodecTabsWidget::compareWindowStream(int first, int second, int third) {
    previousFirst = first;
    previousSecond = second;
    previousThird = third;
    qDebug() << "selected codecs: " << first << second << third;

    // PP: mjpeg
    QString streamingParameters1 = "-c:v mjpeg -f nut -an";
    QString streamingParameters2 = parametersToString(
        compareWindow.getManager(first)->getStreamingParameters());
    QString streamingParameters3 = parametersToString(
        compareWindow.getManager(second)->getStreamingParameters());
    QString streamingParameters4 = parametersToString(
        compareWindow.getManager(third)->getStreamingParameters());

    qDebug() << "streaming parameters:";
    qDebug() << streamingParameters1;
    qDebug() << streamingParameters2;
    qDebug() << streamingParameters3;
    qDebug() << streamingParameters4;

    QString streamingCommand = buildMultipleStreamingCommands(
        inputParameters, inputLocation,
        {streamingParameters1, streamingParameters2, streamingParameters3,
         streamingParameters4},
        {ENCODED_VIDEO_PROTOCOL + "://" + compareWindowHosts[0] + ":" +
             compareWindowPorts[0] + "?ttl=0",
         ENCODED_VIDEO_PROTOCOL + "://" + compareWindowHosts[1] + ":" +
             compareWindowPorts[1] + "?ttl=0",
         ENCODED_VIDEO_PROTOCOL + "://" + compareWindowHosts[2] + ":" +
             compareWindowPorts[2] + "?ttl=0",
         RAW_VIDEO_PROTOCOL + "://" + compareWindowHosts[3] + ":" +
             compareWindowPorts[3] + "?ttl=0"});

    qDebug() << "streaming command:";

    qDebug() << streamingCommand;
    compareWindow.original->setText("Original");
    compareWindow.label1->setText(codecWidgets.at(first)->getCodecName());
    compareWindow.label2->setText(codecWidgets.at(second)->getCodecName());
    compareWindow.label3->setText(codecWidgets.at(third)->getCodecName());
    compareWindow.setManagers(first, second, third);
    compareWindow.show();
    compareWindow.stream(streamingCommand);
}

void CodecTabsWidget::compareWindowStream() {
    int first = previousFirst;
    int second = previousSecond;
    int third = previousThird;

    qDebug() << "selected codecs: " << first << second << third;

    // PP: mjpeg
    QString streamingParameters1 = "-c:v mjpeg -f nut -an";
    QString streamingParameters2 = parametersToString(
        compareWindow.getManager(first)->getStreamingParameters());
    QString streamingParameters3 = parametersToString(
        compareWindow.getManager(second)->getStreamingParameters());
    QString streamingParameters4 = parametersToString(
        compareWindow.getManager(third)->getStreamingParameters());

    qDebug() << "streaming parameters:";
    qDebug() << streamingParameters1;
    qDebug() << streamingParameters2;
    qDebug() << streamingParameters3;
    qDebug() << streamingParameters4;

    QString streamingCommand = buildMultipleStreamingCommands(
        inputParameters, inputLocation,
        {streamingParameters1, streamingParameters2, streamingParameters3,
         streamingParameters4},
        {ENCODED_VIDEO_PROTOCOL + "://" + compareWindowHosts[0] + ":" +
             compareWindowPorts[0] + "?ttl=0",
         ENCODED_VIDEO_PROTOCOL + "://" + compareWindowHosts[1] + ":" +
             compareWindowPorts[1] + "?ttl=0",
         ENCODED_VIDEO_PROTOCOL + "://" + compareWindowHosts[2] + ":" +
             compareWindowPorts[2] + "?ttl=0",
         RAW_VIDEO_PROTOCOL + "://" + compareWindowHosts[3] + ":" +
             compareWindowPorts[3] + "?ttl=0"});

    qDebug() << "streaming command:";

    qDebug() << streamingCommand;
    compareWindow.original->setText("Original");
    compareWindow.label1->setText(codecWidgets.at(first)->getCodecName());
    compareWindow.label2->setText(codecWidgets.at(second)->getCodecName());
    compareWindow.label3->setText(codecWidgets.at(third)->getCodecName());
    compareWindow.setManagers(first, second, third);
    compareWindow.show();
    compareWindow.stream(streamingCommand);
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
    list << "-flags2 +export_mvs";
    list << inputParameters;
    list << "-i " << inputLocation;

    // TEMPORARY CHANGE FROM COPY TO MJPEG
    // PP: mjpeg
    list << "-c:v mjpeg -f nut -an" << rawLocation + "?ttl=0";

    list << outputPrameters
         << encodedLocation + "?ttl=0" + " -vstats_file " + STATS_FILE_NAME;

    QString command = list.join(" ");
    qDebug() << "\nproduced following encoding command:\n"
             << command.toUtf8().constData() << "\n";
    return command;
}

QString CodecTabsWidget::buildMultipleStreamingCommands(
    QString inputParameters, QString inputLocation,
    QVector<QString> outputPrameters, QVector<QString> outputLocations) {
    QStringList list;
    list << FFMPEG;
    list << "-flags2 +export_mvs";
    list << inputParameters;
    list << "-i " << inputLocation;
    for (int i = 0;
         i < outputPrameters.length() && i < outputLocations.length(); i++) {
        list << outputPrameters[i] << outputLocations[i];
    }

    QString command = list.join(" ");
    qDebug() << "\nproduced following encoding command:\n"
             << command.toUtf8().constData() << "\n";
    return command;
}

QString
CodecTabsWidget::parametersToString(QMap<QString, QString> *parameters) {
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

void CodecTabsWidget::openFromFile(QString filePath) {
    if (!filePath.isEmpty()) {
        inputParameters = "-re";
        inputLocation = "\"" + filePath + "\"";
        settingsChanged();
    }
}

void CodecTabsWidget::openFromCamera() {
    inputParameters = "-f dshow";

    cameraNameGetterProcess.kill();
    cameraNameGetterProcess.waitForFinished();
    cameraNameGetterProcess.start(FFMPEG +
                                  " -list_devices true -f dshow -i dummy");

    // when process is done parseCameraNameProbeOutput runs and opens camera
}

void CodecTabsWidget::onTabChange() { currentTabChanged(); }

QString CodecTabsWidget::getStreamingParameters() {
    if (inputLocation.isEmpty()) {
        return "";
    }

    if (inputParameters.isEmpty()) {
        return "";
    }

    CodecParametersWidget *codecWidget =
        codecWidgets.at(ui->tabWidget->currentIndex());
    QMap<QString, QString> *streamingParametersMap =
        codecWidget->getStreamingParameters();

    if (streamingParametersMap->isEmpty()) {
        return "";
    }

    QString streamingParameters =
        parametersToString(streamingParametersMap) + " -an";
    qDebug() << "streamingParameters =" << streamingParameters;

    return streamingParameters;
}

void CodecTabsWidget::startStreaming(QString streamingParameters) {
    qDebug() << "starting encoding process...";

    QString rawAddress =
        RAW_VIDEO_PROTOCOL + "://" + rawVideoHost + ":" + rawVideoPort;
    QString encodedAddress = ENCODED_VIDEO_PROTOCOL + "://" + encodedVideoHost +
                             ":" + encodedVideoPort;

    QString streamingCommand =
        buildStreamingCommand(inputParameters, inputLocation,
                              streamingParameters, rawAddress, encodedAddress);
    streamingProcess.start(streamingCommand);
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

void CodecTabsWidget::getSingleFrame() {
    QString address =
        RAW_VIDEO_PROTOCOL + "://" + RAW_VIDEO_HOST + ":" + RAW_VIDEO_PORT;

    singleFrameProcess.start(FFMPEG + " -i " + address +
                             " -t 1 -vframes 1 -f image2 singleframe.jpg -y");
}

void CodecTabsWidget::onSingleFrameGotten(int a, QProcess::ExitStatus b) {
    (void)a;
    (void)b;

    qDebug() << "completed";

    scene = new QGraphicsScene();
    view = new QGraphicsView(scene);
    item = new QGraphicsPixmapItem(QPixmap("singleframe.jpg"));
    scene->addItem(item);
    view->show();
}
