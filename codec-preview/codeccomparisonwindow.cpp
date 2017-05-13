#include "codeccomparisonwindow.h"
#include "ui_codeccomparisonwindow.h"

CodecComparisonWindow::CodecComparisonWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::CodecComparisonWindow)
{
    ui->setupUi(this);

    initCodecs();


    connect(&probeProcess, &QProcess::readyRead, this, &CodecComparisonWindow::readOutput);

    vlcInstance = new VlcInstance(VlcCommon::args(), NULL);

    // Initialise raw video display
    vlcPlayerRaw = new VlcMediaPlayer(vlcInstance);
    vlcPlayerRaw->setVideoWidget(ui->rawVideo);
    vlcPlayerRaw->audio()->setMute(true);
    ui->rawVideo->setMediaPlayer(vlcPlayerRaw);
    vlcMediaRaw = new VlcMedia(RAW_VIDEO_PROTOCOL + "://@" + RAW_VIDEO_HOST + ":" + RAW_VIDEO_PORT , false, vlcInstance);
    vlcPlayerRaw->openOnly(vlcMediaRaw);


    // Initialise encoded video display
    vlcPlayerEncoded = new VlcMediaPlayer(vlcInstance);
    vlcPlayerEncoded->setVideoWidget(ui->encodedVideo);
    vlcPlayerEncoded->audio()->setMute(true);
    ui->encodedVideo->setMediaPlayer(vlcPlayerEncoded);
    vlcMediaEncoded =  new VlcMedia(ENCODED_VIDEO_PROTOCOL + "://@" + ENCODED_VIDEO_HOST + ":" + ENCODED_VIDEO_PORT , false, vlcInstance);
    vlcPlayerEncoded->openOnly(vlcMediaEncoded);

    connect(this, &CodecComparisonWindow::settingsChanged, this, &CodecComparisonWindow::broadcast);
    connect(ui->tabWidget, &QTabWidget::currentChanged, this, &CodecComparisonWindow::broadcast);


    // Provide debug info for raw player
    connect(vlcPlayerRaw, &VlcMediaPlayer::stopped, [] () {
        qDebug() << "\tvlcPlayerRaw stopped";
    });
    connect(vlcPlayerRaw, &VlcMediaPlayer::playing, [] () {
        qDebug() << "\tvlcPlayerRaw playing";
    });
    connect(vlcPlayerRaw, &VlcMediaPlayer::paused, [] () {
        qDebug() << "\tvlcPlayerRaw paused";
    });
    connect(vlcPlayerRaw, &VlcMediaPlayer::end, [] () {
        qDebug() << "\tvlcPlayerRaw end";
    });
    connect(vlcPlayerRaw, &VlcMediaPlayer::error, [] () {
        qDebug() << "\tvlcPlayerRaw error";
    });
    connect(vlcPlayerRaw, &VlcMediaPlayer::opening, [] () {
        qDebug() << "\tvlcPlayerRaw opening";
    });

    //prints probe output to standard output
    //framesProbe.setProcessChannelMode(QProcess::ForwardedChannels);

    ui->frameTypes->setReadOnly(true);
}

CodecComparisonWindow::~CodecComparisonWindow()
{
    delete ui;

    //TODO: manage memory clearup, simply deleting causes tons of errors

    /*
    delete vlcPlayer;
    delete vlcMedia;
    delete vlcInstance;

    delete vlcPlayerEncoded;
    delete vlcMediaEncoded;
    delete vlcInstanceEncoded;
    */

    //for(int i=0;i<CODECS_NUMBER;i++) delete codecs[i];
    //delete[] codecs;

}

void CodecComparisonWindow::closeEvent(QCloseEvent *event)
{
    (void)event; //silence annoying warning
    encodingProcess.kill();
    probeProcess.kill();
}

void CodecComparisonWindow::initCodecs()
{
    codecs = new CodecManager*[NUMBER_OF_CODECS];
    codecs[0] = new MJPEGManager();
    codecs[1] = new H261Manager();
    codecs[2] = new MPEG1Manager();
    codecs[3] = new MPEG2Manager();
    codecs[4] = new H264Manager();
    codecs[5] = new H265Manager();
}

void CodecComparisonWindow::readOutput()
{
    while(probeProcess.canReadLine()){
        QString output = probeProcess.readLine();

        if(output.startsWith("pict_type=")) {
            typesOfFrames.enqueue(output.toUtf8().constData()[10]);
            if(typesOfFrames.size() > 16) typesOfFrames.dequeue();

            QString currentFrameTypes;

            QListIterator<char> i(typesOfFrames);

            while(i.hasNext()) {
                currentFrameTypes.append(i.next());
            }

            ui->frameTypes->setText(currentFrameTypes);
        }
   }
}

QString CodecComparisonWindow::buildEncodingCommand(QString inputParameters, QString inputLocation, QVector<QString> outputPrameters, QVector<QString> outputLocations) {
    QStringList list;
    list << FFMPEG;
    list << inputParameters;
    list << "-i" << inputLocation;
    for (int i = 0; i < outputPrameters.length() && i < outputLocations.length(); i++) {
        list << outputPrameters[i] << outputLocations[i];
    }

    QString command = list.join(" ");
    qDebug() << "Produced the following encoding command: " << command;
    return command;
}

QString CodecComparisonWindow::buildProbeCommand(QString location) {
    QStringList list;
    list << FFPROBE;
    list << location;
    list << "-show-frames";

    QString command = list.join(" ");
    qDebug() << "Produced the following probe command: " << command;
    return command;
}

void CodecComparisonWindow::broadcast() {
    if (inputLocation.isEmpty()) {
        qDebug() << "Input location is missing!";
        return;
    }
    if (inputParameters.isEmpty()) {
        qDebug() << "Input parameters are missing!";
        return;
    }
    QString encodingParameters = codecs[ui->tabWidget->currentIndex()]->encodingParameters;
    if (encodingParameters.isEmpty()) {
        qDebug() << "Encoding parameters are missing!";
        return;
    }

    qDebug() << "Stopping the players...";
    vlcPlayerRaw->stop();
    vlcPlayerEncoded->stop();

    qDebug() << "Killing current encoding and probe processes...";
    encodingProcess.kill();
    probeProcess.kill();

    qDebug() << "Starting the encoding process...";
    QString encodingCommand = buildEncodingCommand(
        inputParameters,
        inputLocation,
        {
            "-r 25 -c:v copy -f nut",
            encodingParameters
        },
        {
            RAW_VIDEO_PROTOCOL + "://" + RAW_VIDEO_HOST + ":" + RAW_VIDEO_PORT,
            ENCODED_VIDEO_PROTOCOL + "://" + ENCODED_VIDEO_HOST + ":" + ENCODED_VIDEO_PORT
        }
    );
    encodingProcess.start(encodingCommand);

    qDebug() << "Starting the probe process...";
    QString probeCommand = buildProbeCommand(ENCODED_VIDEO_PROTOCOL + "://" + ENCODED_VIDEO_HOST + ":" + ENCODED_VIDEO_PORT);
    probeProcess.start(probeCommand);

    qDebug() << "Starting the players...";
    vlcPlayerRaw->setTime(0);
    vlcPlayerEncoded->setTime(0);
    vlcPlayerRaw->play();
    vlcPlayerEncoded->play();
}

void CodecComparisonWindow::on_actionOpenFile_triggered() {
    QString filePath = QFileDialog::getOpenFileName(this, tr("Open file"), QDir::homePath(), tr("Multimedia files (*)"));
    if (!filePath.isEmpty()) {
        inputParameters = "-re";
        inputLocation = filePath;
        settingsChanged();
    }
}

void CodecComparisonWindow::on_actionOpenCamera_triggered() {
    #ifdef Q_OS_WIN
    inputParameters = "-f dshow";
    inputLocation = "video=\"Lenovo EasyCamera\"";
    inputChanged();
    #else
    inputParameters = "-f v4l2";
    inputLocation = "/dev/video0";
    settingsChanged();
    #endif
}
