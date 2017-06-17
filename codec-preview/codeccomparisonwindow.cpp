#include "codeccomparisonwindow.h"
#include "selectcodecs.h"
#include "ui_codeccomparisonwindow.h"

CodecComparisonWindow::CodecComparisonWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::CodecComparisonWindow) {
    ui->setupUi(this);

    initCodecs();
    initVlc();
    connectSlots();

    // prints probe output to standard output
    //probeProcess.setProcessChannelMode(QProcess::ForwardedChannels);
   // streamProbeProcess.setProcessChannelMode(QProcess::SeparateChannels);
    //streamingProcess.setStandardOutputFile("main_output.txt");
    // probeProcess.setProcessChannelMode(QProcess::ForwardedChannels);

    /*ui->frameTypes->setReadOnly(true);
    ui->frameWidth->setReadOnly(true);
    ui->frameHeight->setReadOnly(true);
    ui->codecName->setReadOnly(true);
    ui->bitRate->setReadOnly(true);
    ui->aspectRatio->setReadOnly(true);
    ui->tabWidget->setCurrentIndex(0);
*/
    //probe = new VideoInfoProbe(this);//(ui->frameTypes, ui->frameWidth, ui->frameHeight);
    videoInfo = ui->videoInfo;
}

CodecComparisonWindow::~CodecComparisonWindow() { delete ui; }

void CodecComparisonWindow::closeEvent(QCloseEvent *event) {
    (void)event; // silence annoying warning
    streamingProcess.kill();
    streamingProcess.waitForFinished();
    videoInfo->stopProbe();


}

/*void CodecComparisonWindow::readStreamOutput() {
    //qDebug() << "getting stream probe output";
    while (streamProbeProcess.canReadLine()) {
        //qDebug() << "in loop";
        QString output = streamingProcess.readLine();
        if(output.isEmpty()) continue;
        //if(output.startsWith("avg_frame_rate=")) {
        //    qDebug() << "got some output for frame rate";
        //    ui->frameRate->setText(output);
        //}
        qDebug() << "show streams output: " +  output;
    }
}*/

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

QString CodecComparisonWindow::buildProbeCommand(QString location, QString params) {
    QStringList list;
    list << FFPROBE;
    list << location;
    list << params;

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
    QMap<QString, QString> streamingParametersMap =
        codecManagers.at(ui->tabWidget->currentIndex())
            ->getStreamingParameters();
    if (streamingParametersMap.isEmpty()) {
        qDebug() << "Encoding parameters are missing! Not starting player.";
        return;
    }

    QString streamingParameters = parametersToString(streamingParametersMap) + " -an";




    videoInfo->clearFrameQueue();
    //ui->frameTypes->setText("");
    ui->crf->setText(codecManagers.at(ui->tabWidget->currentIndex())->getCRF());

    qDebug() << "Stopping the players...";
    vlcPlayerRaw->stop();
    vlcPlayerEncoded->stop();

    qDebug() << "Killing current encoding and probe processes...";
    streamingProcess.kill();
    streamingProcess.waitForFinished();
    videoInfo->stopProbe();



    qDebug() << "Starting the encoding process...";
    QString streamingCommand = buildStreamingCommand(
        inputParameters, inputLocation,
        {"-c:v copy -f nut -an", streamingParameters, streamingParameters, streamingParameters},
        {RAW_VIDEO_PROTOCOL + "://" + RAW_VIDEO_HOST + ":" + RAW_VIDEO_PORT,
         ENCODED_VIDEO_PROTOCOL + "://" + ENCODED_VIDEO_HOST + ":" + ENCODED_VIDEO_PORT,
         VIDEO_PROBE_PROTOCOL + "://" + VIDEO_PROBE_HOST + ":" + VIDEO_PROBE_PORT,
         STREAM_PROBE_PROTOCOL + "://" + STREAM_PROBE_HOST + ":" + STREAM_PROBE_PORT       });
    streamingProcess.start(streamingCommand);

    qDebug() << "Starting the probe process...";

    QString frameProbeCommand =
        buildProbeCommand(VIDEO_PROBE_PROTOCOL + "://" + VIDEO_PROBE_HOST +
                          ":" + VIDEO_PROBE_PORT, "-show_frames -show_entries frame=pict_type,width,height");


    videoInfo->startFrameProbe(frameProbeCommand);

    QString streamProbeCommand =
            buildProbeCommand(STREAM_PROBE_PROTOCOL + "://" + STREAM_PROBE_HOST +
                              ":" + STREAM_PROBE_PORT, "-show_streams -select_streams v:0");

    videoInfo->startStreamProbe(streamProbeCommand);
    //qDebug() << "starteeeed";
    //streamProbeProcess.moveToThread(new QThread());
    //streamProbeProcess.waitForBytesWritten(10000);
    //streamProbeProcess.kill();
    //streamProbeProcess.moveToThread(new QThread( ));

    //QThread::msleep(700);
    //QFile inputFile("output_stream.txt");


    //streamProbeProcess.waitForFinished(500);
    //streamProbeProcess.kill();

    //std::ifstream ifs("D", std::ios::binary);
    //std::ofstream ofs("copy.txt", std::ios::binary);

   // ofs << ifs.rdbuf();






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

//    for(int i = 0; i < codecManagers.size(); i++) {
//        connect(codecManagers.at(i), &CodecManager::parametersChanged, this, &CodecComparisonWindow::broadcast);
//    }

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



    //connect(&streamProbeProcess, &QProcess::readyRead, this,
            //&CodecComparisonWindow::readStreamOutput);



}

void CodecComparisonWindow::on_compareCodecs_clicked() {
    qDebug() << "Clicked!\n";
    SelectCodecs selectCodecs;
    selectCodecs.setMainWindowHandler(this);
    selectCodecs.setModal(true);
    selectCodecs.exec();
}

void CodecComparisonWindow::setSelectedCodecs(int first, int second,
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

QVector<CodecManager *> CodecComparisonWindow::getCodecManagers() {
    return codecManagers;
}



QString CodecComparisonWindow::parametersToString(QMap<QString, QString> parameters) {
    QStringList result;

    for(auto key : parameters.keys())
    {
      result << "-" + key << parameters.value(key);
    }

    return result.join(" ");
}

void CodecComparisonWindow::on_crf_returnPressed()
{
    codecManagers.at(ui->tabWidget->currentIndex())->setCRF(ui->crf->text());
    settingsChanged();
}

void CodecComparisonWindow::on_crf_editingFinished()
{
    codecManagers.at(ui->tabWidget->currentIndex())->setCRF(ui->crf->text());
    settingsChanged();
}
