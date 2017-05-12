#include "codeccomparisonwindow.h"
#include "ui_codeccomparisonwindow.h"

CodecComparisonWindow::CodecComparisonWindow(QWidget *parent) :
    QMainWindow(parent),
    vlcMediaRaw(0),
    vlcMediaEncoded(0),
    ui(new Ui::CodecComparisonWindow)
{
    ui->setupUi(this);

    initCodecs();

    connect(ui->tabWidget, SIGNAL(currentChanged(int)), this, SLOT(tabSelected()));

    vlcInstance = new VlcInstance(VlcCommon::args(), NULL);

    vlcPlayerRaw = new VlcMediaPlayer(vlcInstance);
    vlcPlayerRaw->setVideoWidget(ui->rawVideo);
    ui->rawVideo->setMediaPlayer(vlcPlayerRaw);
    vlcVolumeRaw = new VlcWidgetVolumeSlider();
    vlcVolumeRaw->setMediaPlayer(vlcPlayerRaw);
    vlcVolumeRaw->mute();


    vlcPlayerEncoded = new VlcMediaPlayer(vlcInstance);
    vlcPlayerEncoded->setVideoWidget(ui->encodedVideo);
    ui->encodedVideo->setMediaPlayer(vlcPlayerEncoded);
    vlcVolumeEncoded = new VlcWidgetVolumeSlider();
    vlcVolumeEncoded->setMediaPlayer(vlcPlayerEncoded);
    vlcVolumeEncoded->mute();



    vlcMediaEncoded = new VlcMedia("udp://@localhost:" + ENCODED_VIDEO_PORT, vlcInstance);
    vlcPlayerEncoded->open(vlcMediaEncoded);

    connect(&probeProcess, &QProcess::readyRead, this, &CodecComparisonWindow::readOutput);

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


void CodecComparisonWindow::openLocal()
{
    //kill existing streaming process
    encodingProcess.kill();

    //get file directory from user prompt
    file = QFileDialog::getOpenFileName(this, tr("Open file"), QDir::homePath(), tr("Multimedia files(*)"));

    if (file.isEmpty()) return;

    vlcMediaRaw = new VlcMedia(file, true, vlcInstance);

    vlcPlayerRaw->open(vlcMediaRaw);

    codecs[ui->tabWidget->currentIndex()]->start(encodingProcess, file);

    // Start the probe
    probeProcess.start("ffprobe udp://localhost:" + VIDEO_PROBE_PORT + " -show_frames");
}

void CodecComparisonWindow::openCamera()
{
    // Create OS-dependent vlcMedia and command objects
    QString command;
    #ifdef Q_OS_WIN
    QString cameraName = "Lenovo EasyCamera";
    command = "ffmpeg -f dshow -i video=\"" + cameraName + "\" -q 50 -f mpegts udp://localhost:" + ENCODED_VIDEO_PORT;
    #else
    QString devicePath = QString("/dev/video0");
    command = "ffmpeg -i \"" + devicePath + "\" -q 50 -f mpegts udp://localhost:" + ENCODED_VIDEO_PORT + " -vcodec copy -f nut udp://localhost:2005";
    #endif

    // Run the command
    qDebug() << command;
    encodingProcess.start(command);

    // Start displaying raw video
    vlcMediaRaw = new VlcMedia("udp://@localhost:" + RAW_VIDEO_PORT, false, vlcInstance);
    vlcPlayerRaw->open(vlcMediaRaw);

    // Start displaying encoded video
    vlcMediaEncoded = new VlcMedia("udp://@localhost:" + ENCODED_VIDEO_PORT, vlcInstance);
    vlcPlayerEncoded->open(vlcMediaEncoded);

    // Start the probe
    probeProcess.start("ffprobe udp://localhost:" + VIDEO_PROBE_PORT + " -show_frames");
}

void CodecComparisonWindow::on_actionOpen_file_triggered()
{
    openLocal();
}

void CodecComparisonWindow::on_actionOpen_camera_triggered()
{
    openCamera();
}

void CodecComparisonWindow::closeEvent(QCloseEvent *event)
{
    (void)event; //silence annoying warning
    encodingProcess.kill();
    probeProcess.kill();
}

void CodecComparisonWindow::tabSelected()
{
    if(file != NULL)
    {
        encodingProcess.kill();
        vlcMediaRaw = new VlcMedia(file, true, vlcInstance);
        vlcPlayerRaw->open(vlcMediaRaw);
        codecs[ui->tabWidget->currentIndex()]->start(encodingProcess, file);
    }
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

void CodecComparisonWindow::broadcast(QString encodingParameters) {
    qDebug() << "Stopping the players.";
    vlcPlayerRaw->stop();
    vlcPlayerEncoded->stop();

    qDebug() << "Killing current encoding and probe processes...";
    encodingProcess.kill();
    probeProcess.kill();

    qDebug() << "Starting the encoding process...";
    QString encodingCommand = buildEncodingCommand(
        "-f v4l2",
        "/dev/video0",
        {
            "-c:v copy -an -f nut",
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

    qDebug() << "Starting the players.";
            // DELETE THIS LATER!
            vlcMediaRaw = new VlcMedia(RAW_VIDEO_PROTOCOL + "://@" + RAW_VIDEO_HOST + ":" + RAW_VIDEO_PORT , false, vlcInstance);
            vlcMediaEncoded =  new VlcMedia(ENCODED_VIDEO_PROTOCOL + "://@" + ENCODED_VIDEO_HOST + ":" + ENCODED_VIDEO_PORT , false, vlcInstance);
    vlcPlayerRaw->open(vlcMediaRaw);
    vlcPlayerEncoded->open(vlcMediaEncoded);
}
