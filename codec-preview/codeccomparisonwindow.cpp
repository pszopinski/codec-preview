#include "codeccomparisonwindow.h"
#include "ui_codeccomparisonwindow.h"


CodecComparisonWindow::CodecComparisonWindow(QWidget *parent) :
    QMainWindow(parent),
    vlcMedia(0),
    vlcMediaEncoded(0),
    ui(new Ui::CodecComparisonWindow)
{

    ui->setupUi(this);


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



}

CodecComparisonWindow::~CodecComparisonWindow()
{
    delete ui;



}


void CodecComparisonWindow::openLocal()
{
    process.kill();
    process.waitForFinished();




    QString file =
            QFileDialog::getOpenFileName(this, tr("Open file"),
                                         QDir::homePath(),
                                         tr("Multimedia files(*)"));

    if (file.isEmpty())
        return;

    vlcMedia = new VlcMedia(file, true, vlcInstance);

    vlcPlayer->open(vlcMedia);


    //H.265
    //process->start(QString("ffmpeg -r 25 -i \"" + file + "\" -c:v libx265 -preset ultrafast -x265-params crf=23 -strict experimental -an -re -f mpegts udp://localhost:2000").toUtf8().constData());

    //MJPEG
    process.start(QString("ffmpeg -re -i  \"" + file + "\" -preset ultrafast -an -strict experimental -f mpegts udp://localhost:2000").toUtf8().constData());


}

void CodecComparisonWindow::openCamera()
{
    QString cameraName = QString("Lenovo EasyCamera");

    vlcMedia = new VlcMedia(QString("dshow:// :dshow-vdev=\"") + cameraName + QString("\""), vlcInstance);

    vlcPlayer->open(vlcMedia);

    //MJPEG
    process.start(QString("ffmpeg -f dshow -i video=\"") + cameraName + QString("\" -q 50 -f mpegts udp://localhost:2000"));

    vlcMediaEncoded = new VlcMedia("udp://@localhost:2000", vlcInstance);
    vlcPlayerEncoded->open(vlcMediaEncoded);
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
    process.kill();

    //vlcPlayer->stop();
    //vlcPlayerEncoded->stop();



}
