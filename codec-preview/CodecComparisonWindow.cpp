#include "CodecComparisonWindow.h"
#include "ui_CodecComparisonWindow.h"

CodecComparisonWindow::CodecComparisonWindow(QWidget *parent) : QWidget(parent), ui(new Ui::CodecComparisonWindow) {
    setWindowState(Qt::WindowMaximized);
    ui->setupUi(this);

    codecWidgets.push_back(mjpegManager);
    codecWidgets.last()->setCodecName("MJPEG");
    codecWidgets.push_back(h261Manager);
    codecWidgets.last()->setCodecName("H261");
    codecWidgets.push_back(mpeg1Manager);
    codecWidgets.last()->setCodecName("MPEG1");
    codecWidgets.push_back(mpeg2Manager);
    codecWidgets.last()->setCodecName("MPEG2");
    codecWidgets.push_back(h264Manager);
    codecWidgets.last()->setCodecName("H264");
    codecWidgets.push_back(h265Manager);
    codecWidgets.last()->setCodecName("H265");

    for (auto codecWidget : codecWidgets) {

        /*    connect(codecWidget, &CodecParametersWidget::parametersChanged, this,
                    &MainWindow::settingsChanged);*/
        connect(codecWidget, SIGNAL(parametersChanged()), this, SLOT(compareWindowStream()));
    }

    vlcInstance = new VlcInstance({""}, NULL);

    for (int i = 0; i < 4; i++) {
        // initialize media objects
        vlcMedia[i] = new VlcMedia(RAW_VIDEO_PROTOCOL + "://@" + compareWindowHosts[i] + ":" + compareWindowPorts[i],
                                   false, vlcInstance);

        // initialize video displays
        vlcMediaPlayers[i] = new VlcMediaPlayer(vlcInstance);
        vlcMediaPlayers[i]->audio()->setMute(true);
        vlcMediaPlayers[i]->openOnly(vlcMedia[i]);
    }

    // connect video widgets
    vlcMediaPlayers[0]->setVideoWidget(ui->rawVideo);
    ui->rawVideo->setMediaPlayer(vlcMediaPlayers[0]);
    vlcMediaPlayers[1]->setVideoWidget(ui->encodedVideo1);
    ui->encodedVideo1->setMediaPlayer(vlcMediaPlayers[1]);
    vlcMediaPlayers[2]->setVideoWidget(ui->encodedVideo2);
    ui->encodedVideo2->setMediaPlayer(vlcMediaPlayers[2]);
    vlcMediaPlayers[3]->setVideoWidget(ui->encodedVideo3);
    ui->encodedVideo3->setMediaPlayer(vlcMediaPlayers[3]);

    // init labels
    original = ui->original;
    label1 = ui->first;
    label2 = ui->second;
    label3 = ui->third;

    // react to frame probe output with parseFrameProbeOutput
    /*connect(&frameProbes[0], &QProcess::readyRead, this,
            &CodecCompareWindow::parseFrameProbeOutput0);

    connect(&frameProbes[3], &QProcess::readyRead, this,
            &CodecCompareWindow::parseFrameProbeOutput3);*/

    connect(this, &CodecComparisonWindow::statsChanged1, ui->videoInfo1, &VideoStatisticsWidget::onStatsChange);
    connect(this, &CodecComparisonWindow::statsChanged2, ui->videoInfo2, &VideoStatisticsWidget::onStatsChange);
    connect(this, &CodecComparisonWindow::statsChanged3, ui->videoInfo3, &VideoStatisticsWidget::onStatsChange);

    connect(vlcMediaPlayers[1], &VlcMediaPlayer::timeChanged, this, &CodecComparisonWindow::whilePlaying1);
    connect(vlcMediaPlayers[2], &VlcMediaPlayer::timeChanged, this, &CodecComparisonWindow::whilePlaying2);
    connect(vlcMediaPlayers[3], &VlcMediaPlayer::timeChanged, this, &CodecComparisonWindow::whilePlaying3);
}

CodecComparisonWindow::~CodecComparisonWindow() { delete ui; }

void CodecComparisonWindow::closeEvent(QCloseEvent *event) {
    (void)event;
    for (int i = 0; i < 4; i++) {
        // stop player
        vlcMediaPlayers[i]->stop();
    }
    // kill streaming process
    streamingProcess.kill();
    streamingProcess.waitForFinished();

    ui->videoInfo1->stopProbe();
    ui->videoInfo2->stopProbe();
    ui->videoInfo3->stopProbe();
}

CodecParametersWidget *CodecComparisonWindow::getManager(int i) {

    switch (i) {
    case 0:
        return mjpegManager;
        break;
    case 1:
        return h261Manager;
        break;
    case 2:
        return mpeg1Manager;
        break;
    case 3:
        return mpeg2Manager;
        break;
    case 4:
        return h264Manager;
        break;
    case 5:
        return h265Manager;
        break;
    }
    return NULL;
}

void CodecComparisonWindow::setManagers(int one, int two, int three) {
    ui->encodedParams1->setVisible(false);
    ui->encodedParams2->setVisible(false);
    ui->encodedParams3->setVisible(false);

    switch (one) {
    case 0:
        ui->outerLayout->replaceWidget(ui->encodedParams1, mjpegManager);
        break;
    case 1:
        ui->outerLayout->replaceWidget(ui->encodedParams1, h261Manager);
        break;
    case 2:
        ui->outerLayout->replaceWidget(ui->encodedParams1, mpeg1Manager);
        break;
    case 3:
        ui->outerLayout->replaceWidget(ui->encodedParams1, mpeg2Manager);
        break;
    case 4:
        ui->outerLayout->replaceWidget(ui->encodedParams1, h264Manager);
        break;
    case 5:
        ui->outerLayout->replaceWidget(ui->encodedParams1, h265Manager);
        break;
    }

    switch (two) {
    case 0:
        ui->outerLayout->replaceWidget(ui->encodedParams2, mjpegManager);
        break;
    case 1:
        ui->outerLayout->replaceWidget(ui->encodedParams2, h261Manager);
        break;
    case 2:
        ui->outerLayout->replaceWidget(ui->encodedParams2, mpeg1Manager);
        break;
    case 3:
        ui->outerLayout->replaceWidget(ui->encodedParams2, mpeg2Manager);
        break;
    case 4:
        ui->outerLayout->replaceWidget(ui->encodedParams2, h264Manager);
        break;
    case 5:
        ui->outerLayout->replaceWidget(ui->encodedParams2, h265Manager);
        break;
    }

    switch (three) {
    case 0:
        ui->outerLayout->replaceWidget(ui->encodedParams3, mjpegManager);
        break;
    case 1:
        ui->outerLayout->replaceWidget(ui->encodedParams3, h261Manager);
        break;
    case 2:
        ui->outerLayout->replaceWidget(ui->encodedParams3, mpeg1Manager);
        break;
    case 3:
        ui->outerLayout->replaceWidget(ui->encodedParams3, mpeg2Manager);
        break;
    case 4:
        ui->outerLayout->replaceWidget(ui->encodedParams3, h264Manager);
        break;
    case 5:
        ui->outerLayout->replaceWidget(ui->encodedParams3, h265Manager);
        break;
    }
}

void CodecComparisonWindow::stream(QString streamingCommand) {
    for (int i = 0; i < 4; i++) {
        // stop player
        vlcMediaPlayers[i]->stop();

        frameProbes[i].kill();
        frameProbes[i].waitForFinished();

        streamProbes[i].kill();
        streamProbes[i].waitForFinished();
    }

    // kill streaming process
    streamingProcess.kill();
    streamingProcess.waitForFinished();

    // start streaming process
    streamingProcess.start(streamingCommand);

    for (int i = 0; i < 4; i++) {
        vlcMediaPlayers[i]->play();
    }

    QString frameProbeCommand = FFmpegCommand::getFrameProbeCommand(compareWindowHosts[1], compareWindowPorts[1]);
    ui->videoInfo1->startFrameProbe(frameProbeCommand);
    QString streamProbeCommand = FFmpegCommand::getStreamProbeCommand(compareWindowHosts[1], compareWindowPorts[1]);
    ui->videoInfo1->startStreamProbe(streamProbeCommand);
    frameProbeCommand = FFmpegCommand::getFrameProbeCommand(compareWindowHosts[2], compareWindowPorts[2]);
    ui->videoInfo2->startFrameProbe(frameProbeCommand);
    streamProbeCommand = FFmpegCommand::getStreamProbeCommand(compareWindowHosts[2], compareWindowPorts[2]);
    ui->videoInfo2->startStreamProbe(streamProbeCommand);
    frameProbeCommand = FFmpegCommand::getFrameProbeCommand(compareWindowHosts[3], compareWindowPorts[3]);
    ui->videoInfo3->startFrameProbe(frameProbeCommand);
    streamProbeCommand = FFmpegCommand::getStreamProbeCommand(compareWindowHosts[3], compareWindowPorts[3]);
    ui->videoInfo3->startStreamProbe(streamProbeCommand);
}

void CodecComparisonWindow::whilePlaying1() { emit statsChanged1(vlcMedia[1]->getStats()); }

void CodecComparisonWindow::whilePlaying2() { emit statsChanged2(vlcMedia[2]->getStats()); }

void CodecComparisonWindow::whilePlaying3() { emit statsChanged3(vlcMedia[3]->getStats()); }

void CodecComparisonWindow::compareWindowStream(int first, int second, int third) {
    previousFirst = first;
    previousSecond = second;
    previousThird = third;
    qDebug() << "selected codecs: " << first << second << third;

    // PP: mjpeg
    QString streamingParameters1 = "-c:v mjpeg -f nut -an";
    QString streamingParameters2 = FFmpegCommand::parametersToString(getManager(first)->getStreamingParameters());
    QString streamingParameters3 = FFmpegCommand::parametersToString(getManager(second)->getStreamingParameters());
    QString streamingParameters4 = FFmpegCommand::parametersToString(getManager(third)->getStreamingParameters());

    qDebug() << "streaming parameters:";
    qDebug() << streamingParameters1;
    qDebug() << streamingParameters2;
    qDebug() << streamingParameters3;
    qDebug() << streamingParameters4;

    QString streamingCommand = buildMultipleStreamingCommands(
        inputParameters, inputLocation,
        {streamingParameters1, streamingParameters2, streamingParameters3, streamingParameters4},
        {ENCODED_VIDEO_PROTOCOL + "://" + compareWindowHosts[0] + ":" + compareWindowPorts[0] + "?ttl=0",
         ENCODED_VIDEO_PROTOCOL + "://" + compareWindowHosts[1] + ":" + compareWindowPorts[1] + "?ttl=0",
         ENCODED_VIDEO_PROTOCOL + "://" + compareWindowHosts[2] + ":" + compareWindowPorts[2] + "?ttl=0",
         RAW_VIDEO_PROTOCOL + "://" + compareWindowHosts[3] + ":" + compareWindowPorts[3] + "?ttl=0"});

    qDebug() << "streaming command:";

    qDebug() << streamingCommand;
    original->setText("Original");
    label1->setText(codecWidgets.at(first)->getCodecName());
    label2->setText(codecWidgets.at(second)->getCodecName());
    label3->setText(codecWidgets.at(third)->getCodecName());
    setManagers(first, second, third);
    show();
    stream(streamingCommand);
}

void CodecComparisonWindow::compareWindowStream() {
    int first = previousFirst;
    int second = previousSecond;
    int third = previousThird;

    qDebug() << "selected codecs: " << first << second << third;

    // PP: mjpeg
    QString streamingParameters1 = "-c:v mjpeg -f nut -an";
    QString streamingParameters2 = FFmpegCommand::parametersToString(getManager(first)->getStreamingParameters());
    QString streamingParameters3 = FFmpegCommand::parametersToString(getManager(second)->getStreamingParameters());
    QString streamingParameters4 = FFmpegCommand::parametersToString(getManager(third)->getStreamingParameters());

    qDebug() << "streaming parameters:";
    qDebug() << streamingParameters1;
    qDebug() << streamingParameters2;
    qDebug() << streamingParameters3;
    qDebug() << streamingParameters4;

    QString streamingCommand = buildMultipleStreamingCommands(
        inputParameters, inputLocation,
        {streamingParameters1, streamingParameters2, streamingParameters3, streamingParameters4},
        {ENCODED_VIDEO_PROTOCOL + "://" + compareWindowHosts[0] + ":" + compareWindowPorts[0] + "?ttl=0",
         ENCODED_VIDEO_PROTOCOL + "://" + compareWindowHosts[1] + ":" + compareWindowPorts[1] + "?ttl=0",
         ENCODED_VIDEO_PROTOCOL + "://" + compareWindowHosts[2] + ":" + compareWindowPorts[2] + "?ttl=0",
         RAW_VIDEO_PROTOCOL + "://" + compareWindowHosts[3] + ":" + compareWindowPorts[3] + "?ttl=0"});

    qDebug() << "streaming command:";

    qDebug() << streamingCommand;
    original->setText("Original");
    label1->setText(codecWidgets.at(first)->getCodecName());
    label2->setText(codecWidgets.at(second)->getCodecName());
    label3->setText(codecWidgets.at(third)->getCodecName());
    setManagers(first, second, third);
    show();
    stream(streamingCommand);
}

QString CodecComparisonWindow::buildMultipleStreamingCommands(QString inputParameters, QString inputLocation,
                                                              QVector<QString> outputPrameters,
                                                              QVector<QString> outputLocations) {
    QStringList list;
    list << FFMPEG;
    list << "-flags2 +export_mvs";
    list << inputParameters;
    list << "-i " << inputLocation;
    for (int i = 0; i < outputPrameters.length() && i < outputLocations.length(); i++) {
        list << outputPrameters[i] << outputLocations[i];
    }

    QString command = list.join(" ");
    qDebug() << "\nproduced following encoding command:\n" << command.toUtf8().constData() << "\n";
    return command;
}

void CodecComparisonWindow::setInputLocation(QString location) { this->inputLocation = location; }

void CodecComparisonWindow::setInputParameters(QString parameters) { this->inputParameters = parameters; }

QString CodecComparisonWindow::getInputLocation() { return inputLocation; }
QString CodecComparisonWindow::getInputParameters() { return inputParameters; }
