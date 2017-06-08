#include "showcodecs.h"
#include "ui_showcodecs.h"


ShowCodecs::ShowCodecs(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ShowCodecs)
{
    ui->setupUi(this);
    initVlc();
}


ShowCodecs::~ShowCodecs()
{
    delete ui;
}

void ShowCodecs::initVlc()
{
    vlcInstance = new VlcInstance(VlcCommon::args(), NULL);
    // vlcInstance->setLogLevel(Vlc::DisabledLevel);

    // Initialise raw video display
    vlcPlayerEncoded1 = new VlcMediaPlayer(vlcInstance);
    vlcPlayerEncoded1->setVideoWidget(ui->encodedVideo1);
    vlcPlayerEncoded1->audio()->setMute(true);
    ui->encodedVideo1->setMediaPlayer(vlcPlayerEncoded1);
    vlcMediaEncoded1 =new VlcMedia(ENCODED_VIDEO_PROTOCOL1 + "://@" + ENCODED_VIDEO_HOST1 +
                                   ":" + ENCODED_VIDEO_PORT1,
                               false, vlcInstance);
    vlcPlayerEncoded1->openOnly(vlcMediaEncoded1);

    // Initialise encoded video display
    vlcPlayerEncoded2 = new VlcMediaPlayer(vlcInstance);
    vlcPlayerEncoded2->setVideoWidget(ui->encodedVideo2);
    vlcPlayerEncoded2->audio()->setMute(true);
    ui->encodedVideo2->setMediaPlayer(vlcPlayerEncoded2);
    vlcMediaEncoded2 =
        new VlcMedia(ENCODED_VIDEO_PROTOCOL2 + "://@" + ENCODED_VIDEO_HOST2 +
                         ":" + ENCODED_VIDEO_PORT2,
                     false, vlcInstance);
    vlcPlayerEncoded2->openOnly(vlcMediaEncoded2);
}

void ShowCodecs::broadcast(QString streamingCommand1, QProcess* streamingProcess, QProcess* probeProcess, VlcMediaPlayer* vlcPlayerEncoded)
{
    if (inputLocation.isEmpty())
    {
        qDebug() << "Input location is missing! Not starting player.";
        return;
    }
    qDebug() << "Stopping the players...";
   // qDebug() << "player1 "<<vlcPlayerEncoded1;
    vlcPlayerEncoded1->stop();
    vlcPlayerEncoded2->stop();
    vlcPlayerEncoded->stop();

    qDebug() << "Killing current encoding and probe processes...";
    streamingProcess1.kill();
    streamingProcess->kill();
    probeProcess->kill();
    //streamingProcess2.kill();
    //probeProcess.kill();

    streamingProcess1.waitForFinished();
    streamingProcess->waitForFinished();
    probeProcess->waitForFinished();

    qDebug() << "Starting the encoding process...";

    streamingProcess1.start(streamingCommand1);


    qDebug() << "Starting the players...";
    vlcPlayerEncoded1->play();
    vlcPlayerEncoded2->play();
}

void ShowCodecs::setCodecInd(int first, int second)
{
    firstCodecIndex = first;
    secondCodecIndex = second;
}

void ShowCodecs::setInputLocation(QString location)
{
    inputLocation = location;
}
