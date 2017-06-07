#include "showcodecs.h"
#include "ui_showcodecs.h"

ShowCodecs::ShowCodecs(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ShowCodecs)
{
    ui->setupUi(this);
}

void ShowCodecs::setMainWindowHandler(CodecComparisonWindow* ccw)
{
    this->ccw = ccw;
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
    vlcMediaEncoded1 = new VlcMedia(RAW_VIDEO_PROTOCOL + "://@" + RAW_VIDEO_HOST +
                                   ":" + RAW_VIDEO_PORT,
                               false, vlcInstance);
    vlcPlayerEncoded1->openOnly(vlcMediaEncoded1);

    // Initialise encoded video display
    vlcPlayerEncoded2 = new VlcMediaPlayer(vlcInstance);
    vlcPlayerEncoded2->setVideoWidget(ui->encodedVideo2);
    vlcPlayerEncoded2->audio()->setMute(true);
    ui->encodedVideo2->setMediaPlayer(vlcPlayerEncoded2);
    vlcMediaEncoded2 =
        new VlcMedia(ENCODED_VIDEO_PROTOCOL + "://@" + ENCODED_VIDEO_HOST +
                         ":" + ENCODED_VIDEO_PORT,
                     false, vlcInstance);
    vlcPlayerEncoded2->openOnly(vlcMediaEncoded2);
}

void ShowCodecs::broadcast()
{
    if (inputLocation.isEmpty()) {
        qDebug() << "Input location is missing! Not starting player.";
        return;
    }
    /*
    if (inputParameters.isEmpty()) {
        qDebug() << "Input parameters are missing! Not starting player.";
        return;
    }
    */
    QString streamingParameters1 =
        ccw->getCodecManagers().at(firstCodecIndex)
            ->getStreamingParameters();
    if (streamingParameters1.isEmpty()) {
        qDebug() << "Encoding parameters are missing! Not starting player.";
        return;
    }
    QString streamingParameters2 =
        ccw->getCodecManagers().at(secondCodecIndex)
            ->getStreamingParameters();
    if (streamingParameters2.isEmpty()) {
        qDebug() << "Encoding parameters are missing! Not starting player.";
        return;
    }

    //typesOfFrames.clear();
    //ui->frameTypes->setText("");

    qDebug() << "Stopping the players...";
    vlcPlayerEncoded1->stop();
    vlcPlayerEncoded2->stop();
    ccw->vlcPlayerEncoded->stop();

    qDebug() << "Killing current encoding and probe processes...";
    streamingProcess1.kill();
    ccw->streamingProcess.kill();
    ccw->probeProcess.kill();
    //streamingProcess2.kill();
    //probeProcess.kill();

    streamingProcess1.waitForFinished();
    //streamingProcess2.waitForFinished();
    //probeProcess.waitForFinished();

    qDebug() << "Starting the encoding process...";
    QString streamingCommand1 = ccw->buildStreamingCommand(
        "",inputLocation,
        {"-c:v copy -f nut -an", streamingParameters1, streamingParameters1},
        {ENCODED_VIDEO_PROTOCOL1 + "://" + ENCODED_VIDEO_HOST1 + ":" + ENCODED_VIDEO_PORT1,
         ENCODED_VIDEO_PROTOCOL2 + "://" + ENCODED_VIDEO_HOST2 + ":" + ENCODED_VIDEO_PORT2,
         VIDEO_PROBE_PROTOCOL1 + "://" + VIDEO_PROBE_HOST1 + ":" + VIDEO_PROBE_PORT1});
    streamingProcess1.start(streamingCommand1);

    /*
    QString streamingCommand2 = ccw->buildStreamingCommand(
        "",inputLocation,
        {"-c:v copy -f nut -an", streamingParameters2, streamingParameters2},
        {RAW_VIDEO_PROTOCOL + "://" + RAW_VIDEO_HOST + ":" + RAW_VIDEO_PORT,
         ENCODED_VIDEO_PROTOCOL + "://" + ENCODED_VIDEO_HOST + ":" + ENCODED_VIDEO_PORT,
         VIDEO_PROBE_PROTOCOL + "://" + VIDEO_PROBE_HOST + ":" + VIDEO_PROBE_PORT});
    streamingProcess2.start(streamingCommand2);
    */

    /*
    qDebug() << "Starting the probe process...";
    QString probeCommand =
        buildProbeCommand(VIDEO_PROBE_PROTOCOL + "://" + VIDEO_PROBE_HOST +
                          ":" + VIDEO_PROBE_PORT);
    probeProcess.start(probeCommand);
    */

    qDebug() << "Starting the players...";
    //vlcPlayerRaw->setTime(0);
    //vlcPlayerEncoded->setTime(0);
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
