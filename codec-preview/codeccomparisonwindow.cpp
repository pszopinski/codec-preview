#include "codeccomparisonwindow.h"
#include "ui_codeccomparisonwindow.h"
#include <iostream>


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

    for(int i=0;i<CODECS_NUMBER;i++) delete codecs[i];
    delete[] codecs;

}


void CodecComparisonWindow::openLocal()
{
    if(!first)
    {
        process.kill();
    }
    else first = false;
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


    //H.265
    //process.start(QString("ffmpeg -r 25 -i \"" + file + "\" -c:v libx265 -preset ultrafast -x265-params crf=23 -strict experimental -an -re -f mpegts udp://localhost:2000").toUtf8().constData());

    //MJPEG
   // process.start(QString("ffmpeg -re -i  \"" + file + "\" -preset ultrafast -an -strict experimental -f mpegts udp://localhost:2000").toUtf8().constData());
    std::cout<<&process<<std::endl;
    std::cout<<tabWidget->currentIndex()<<std::endl;
    codecs[tabWidget->currentIndex()]->start(process);
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
}

void CodecComparisonWindow::tabSelected()
{
    if(file != NULL)
    {
        std::cout<<"Change codec!!!"<<std::endl;
        process.kill();
        vlcMedia = new VlcMedia(file, true, vlcInstance);
        vlcPlayer->open(vlcMedia);
        std::cout<<&process<<std::endl;
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

