#include "codeccomparisonwindow.h"
#include "ui_codeccomparisonwindow.h"

CodecComparisonWindow::CodecComparisonWindow(QWidget *parent) :
    QMainWindow(parent),
    vlcMedia(0),
    vlcMediaEncoded(0),
    ui(new Ui::CodecComparisonWindow)
{

    ui->setupUi(this);
    tabWidget = ui->tabWidget;
    initCodecs();
    connect(ui->tabWidget, SIGNAL(currentChanged(int)), this, SLOT(tabSelected()));
    vlcInstance = new VlcInstance(VlcCommon::args(), NULL);
    vlcPlayer = new VlcMediaPlayer(vlcInstance);
    vlcPlayer->setVideoWidget(ui->rawVideo);
    ui->rawVideo->setMediaPlayer(vlcPlayer);
    vlcVolume = new VlcWidgetVolumeSlider();
    vlcVolume->setMediaPlayer(vlcPlayer);
    vlcVolume->mute();


    vlcPlayerEncoded = new VlcMediaPlayer(vlcInstance);
    vlcPlayerEncoded->setVideoWidget(ui->encodedVideo);
    ui->encodedVideo->setMediaPlayer(vlcPlayerEncoded);
    vlcVolumeEncoded = new VlcWidgetVolumeSlider();
    vlcVolumeEncoded->setMediaPlayer(vlcPlayerEncoded);
    vlcVolumeEncoded->mute();
    vlcMediaEncoded = new VlcMedia("udp://@localhost:2000", vlcInstance);
    vlcPlayerEncoded->open(vlcMediaEncoded);

    connect(&framesProbe, &QProcess::readyRead, this, &CodecComparisonWindow::readOutput);

    //prints probe output to standard output
    //framesProbe.setProcessChannelMode(QProcess::ForwardedChannels);

    ui->frameTypes->setReadOnly(true);
}

CodecComparisonWindow::~CodecComparisonWindow()
{
    delete ui;
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
    process.kill();

    file =
          QFileDialog::getOpenFileName(this, tr("Open file"),
                                       QDir::homePath(),
                                       tr("Multimedia files(*)"));

    if (file.isEmpty())
        return;

    for(int i=0;i<CODECS_NUMBER;i++)
    {
        codecs[i]->setFile(file);
    }

    vlcMedia = new VlcMedia(file, true, vlcInstance);

    vlcPlayer->open(vlcMedia);

    codecs[tabWidget->currentIndex()]->start(process);

    // Start the probe
    framesProbe.start(QString("ffprobe udp://localhost:2001 -show_frames"));
}

void CodecComparisonWindow::openCamera()
{
    // Create OS-dependent vlcMedia and command objects
    QString command;
    #ifdef Q_OS_WIN
    QString cameraName = QString("Lenovo EasyCamera");
    command = QString("ffmpeg -f dshow -i video=\"") + cameraName + QString("\" -q 50 -f mpegts udp://localhost:2000");
    #else
    QString devicePath = QString("/dev/video0");
    command = QString("ffmpeg -i \"") + devicePath + QString("\" -q 50 -f mpegts udp://localhost:2000 -vcodec copy -f nut udp://localhost:2005");
    #endif

    // Run the command
    qDebug() << command;
    process.start(command);

    // Start displaying raw video
    vlcMedia = new VlcMedia(QString("udp://@localhost:2005"), false, vlcInstance);
    vlcPlayer->open(vlcMedia);

    // Start displaying encoded video
    vlcMediaEncoded = new VlcMedia("udp://@localhost:2000", vlcInstance);
    vlcPlayerEncoded->open(vlcMediaEncoded);

    // Start the probe
    framesProbe.start(QString("ffprobe udp://localhost:2001 -show_frames"));
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
    process.kill();
    framesProbe.kill();
}

void CodecComparisonWindow::tabSelected()
{
    if(file != NULL)
    {
        process.kill();
        vlcMedia = new VlcMedia(file, true, vlcInstance);
        vlcPlayer->open(vlcMedia);
        codecs[tabWidget->currentIndex()]->start(process);
    }
}

void CodecComparisonWindow::initCodecs()
{
    codecs = new Codec*[CODECS_NUMBER];
    codecs[0] = new MJPEG();
    codecs[1] = new H261();
    codecs[2] = new MPEG1();
    codecs[3] = new MPEG2();
    codecs[4] = new H264();
    codecs[5] = new H265();
}

void CodecComparisonWindow::readOutput(){
    while(framesProbe.canReadLine()){
        QString output = framesProbe.readLine();

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
