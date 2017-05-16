#include "codeccomparisonwindow.h"
#include "ui_codeccomparisonwindow.h"

CodecComparisonWindow::CodecComparisonWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::CodecComparisonWindow) {
    ui->setupUi(this);

    initCodecs();
    initVlc();
    connectSlots();

    // prints probe output to standard output
    //probeProcess.setProcessChannelMode(QProcess::ForwardedChannels);

    ui->frameTypes->setReadOnly(true);
    ui->tabWidget->setCurrentIndex(0);
}

CodecComparisonWindow::~CodecComparisonWindow() { delete ui; }

void CodecComparisonWindow::closeEvent(QCloseEvent *event) {
    (void)event; // silence annoying warning
    streamingProcess.kill();
    probeProcess.kill();

    streamingProcess.waitForFinished();
    probeProcess.waitForFinished();
}

void CodecComparisonWindow::readOutput() {
    while (probeProcess.canReadLine()) {
        QString output = probeProcess.readLine();

        if (output.startsWith("pict_type=")) {
            typesOfFrames.enqueue(output.toUtf8().constData()[10]);
            if (typesOfFrames.size() > 16)
                typesOfFrames.dequeue();

            QString currentFrameTypes;

            QListIterator<char> i(typesOfFrames);

            while (i.hasNext()) {
                currentFrameTypes.append(i.next());
            }

            ui->frameTypes->setText(currentFrameTypes);
        }
    }
}

QString CodecComparisonWindow::buildStreamingCommand(
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

QString CodecComparisonWindow::buildProbeCommand(QString location) {
    QStringList list;
    list << FFPROBE;
    list << location;
    list << "-show_frames";

    QString command = list.join(" ");
    qDebug() << "Produced the following probe command:\n"
             << command.toUtf8().constData();
    return command;
}

void CodecComparisonWindow::broadcast() {
    if (inputLocation.isEmpty()) {
        qDebug() << "Input location is missing! Not starting player.";
        return;
    }
    if (inputParameters.isEmpty()) {
        qDebug() << "Input parameters are missing! Not starting player.";
        return;
    }
    QString streamingParameters =
        codecManagers.at(ui->tabWidget->currentIndex())
            ->getStreamingParameters();
    if (streamingParameters.isEmpty()) {
        qDebug() << "Encoding parameters are missing! Not starting player.";
        return;
    }

    typesOfFrames.clear();
    ui->frameTypes->setText("");

    qDebug() << "Stopping the players...";
    vlcPlayerRaw->stop();
    vlcPlayerEncoded->stop();

    qDebug() << "Killing current encoding and probe processes...";
    streamingProcess.kill();
    probeProcess.kill();

    streamingProcess.waitForFinished();
    probeProcess.waitForFinished();

    qDebug() << "Starting the encoding process...";
    QString streamingCommand = buildStreamingCommand(
        inputParameters, inputLocation,
        {"-r 25 -c:v copy -f nut", streamingParameters},
        {RAW_VIDEO_PROTOCOL + "://" + RAW_VIDEO_HOST + ":" + RAW_VIDEO_PORT,
         ENCODED_VIDEO_PROTOCOL + "://" + ENCODED_VIDEO_HOST + ":" +
             ENCODED_VIDEO_PORT});
    streamingProcess.start(streamingCommand);

    qDebug() << "Starting the probe process...";
    QString probeCommand =
        buildProbeCommand(ENCODED_VIDEO_PROTOCOL + "://" + ENCODED_VIDEO_HOST +
                          ":" + ENCODED_VIDEO_PORT);
    probeProcess.start(probeCommand);

    qDebug() << "Starting the players...";
    vlcPlayerRaw->setTime(0);
    vlcPlayerEncoded->setTime(0);
    vlcPlayerRaw->play();
    vlcPlayerEncoded->play();
}

void CodecComparisonWindow::on_actionOpenFile_triggered() {
    QString filePath = QFileDialog::getOpenFileName(
        this, tr("Open file"), QDir::homePath(), tr("Multimedia files (*)"),
        Q_NULLPTR, QFileDialog::DontUseNativeDialog);
    if (!filePath.isEmpty()) {
        inputParameters = "-re";
        inputLocation = "\"" + filePath + "\"";
        settingsChanged();
    }
}

void CodecComparisonWindow::on_actionOpenCamera_triggered() {
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

void CodecComparisonWindow::initCodecs() {
    codecManagers.push_back(new MJPEGManager());
    codecManagers.push_back(new H261Manager());
    codecManagers.push_back(new MPEG1Manager());
    codecManagers.push_back(new MPEG2Manager());
    codecManagers.push_back(new H264Manager());
    codecManagers.push_back(new H265Manager());
}

void CodecComparisonWindow::initVlc() {
    vlcInstance = new VlcInstance(VlcCommon::args(), NULL);
    // vlcInstance->setLogLevel(Vlc::DisabledLevel);

    // Initialise raw video display
    vlcPlayerRaw = new VlcMediaPlayer(vlcInstance);
    vlcPlayerRaw->setVideoWidget(ui->rawVideo);
    vlcPlayerRaw->audio()->setMute(true);
    ui->rawVideo->setMediaPlayer(vlcPlayerRaw);
    vlcMediaRaw = new VlcMedia(RAW_VIDEO_PROTOCOL + "://@" + RAW_VIDEO_HOST +
                                   ":" + RAW_VIDEO_PORT,
                               false, vlcInstance);
    vlcPlayerRaw->openOnly(vlcMediaRaw);

    // Initialise encoded video display
    vlcPlayerEncoded = new VlcMediaPlayer(vlcInstance);
    vlcPlayerEncoded->setVideoWidget(ui->encodedVideo);
    vlcPlayerEncoded->audio()->setMute(true);
    ui->encodedVideo->setMediaPlayer(vlcPlayerEncoded);
    vlcMediaEncoded =
        new VlcMedia(ENCODED_VIDEO_PROTOCOL + "://@" + ENCODED_VIDEO_HOST +
                         ":" + ENCODED_VIDEO_PORT,
                     false, vlcInstance);
    vlcPlayerEncoded->openOnly(vlcMediaEncoded);
}

void CodecComparisonWindow::connectSlots() {

    connect(this, &CodecComparisonWindow::settingsChanged, this,
            &CodecComparisonWindow::broadcast);
    connect(ui->tabWidget, &QTabWidget::currentChanged, this,
            &CodecComparisonWindow::broadcast);

    // Provide debug info for raw player
    connect(vlcPlayerRaw, &VlcMediaPlayer::stopped,
            []() { qDebug() << "vlcPlayerRaw stopped"; });
    connect(vlcPlayerRaw, &VlcMediaPlayer::playing,
            []() { qDebug() << "vlcPlayerRaw playing"; });
    connect(vlcPlayerRaw, &VlcMediaPlayer::paused,
            []() { qDebug() << "vlcPlayerRaw paused"; });
    connect(vlcPlayerRaw, &VlcMediaPlayer::end,
            []() { qDebug() << "vlcPlayerRaw end"; });
    connect(vlcPlayerRaw, &VlcMediaPlayer::error,
            []() { qDebug() << "vlcPlayerRaw error"; });
    connect(vlcPlayerRaw, &VlcMediaPlayer::opening,
            []() { qDebug() << "vlcPlayerRaw opening"; });

    // Provide debug info for encoded player
    connect(vlcPlayerEncoded, &VlcMediaPlayer::stopped,
            []() { qDebug() << "vlcPlayerEncoded stopped"; });
    connect(vlcPlayerEncoded, &VlcMediaPlayer::playing,
            []() { qDebug() << "vlcPlayerEncoded playing"; });
    connect(vlcPlayerEncoded, &VlcMediaPlayer::paused,
            []() { qDebug() << "vlcPlayerEncoded paused"; });
    connect(vlcPlayerEncoded, &VlcMediaPlayer::end,
            []() { qDebug() << "vlcPlayerEncoded end"; });
    connect(vlcPlayerEncoded, &VlcMediaPlayer::error,
            []() { qDebug() << "vlcPlayerEncoded error"; });
    connect(vlcPlayerEncoded, &VlcMediaPlayer::opening,
            []() { qDebug() << "vlcPlayerEncoded opening"; });

    connect(&probeProcess, &QProcess::readyRead, this,
            &CodecComparisonWindow::readOutput);
}
