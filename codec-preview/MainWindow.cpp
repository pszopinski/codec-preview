#include "MainWindow.h"
#include "CodecSelector.h"
#include "ui_mainwindow.h"

QString rawVideoHost = RAW_VIDEO_HOST;
QString encodedVideoHost = ENCODED_VIDEO_HOST;
QString rawVideoPort = RAW_VIDEO_PORT;
QString encodedVideoPort = ENCODED_VIDEO_PORT;

QString compareWindowHosts[4] = {VIDEO_HOSTS[0],VIDEO_HOSTS[1],VIDEO_HOSTS[2],VIDEO_HOSTS[3]};
QString compareWindowPorts[4] = {VIDEO_PORTS[0],VIDEO_PORTS[1],VIDEO_PORTS[2],VIDEO_PORTS[3]};


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
    setWindowState(Qt::WindowMaximized);
    ui->setupUi(this);

    streamingProcess = new StreamingProcess();
    codecComparisonWindow = new CodecComparisonWindow();
    //codecComparisonWindow->setHidden(true);

    ui->codecTabsWidget->setTabPosition(QTabWidget::South);
    ui->codecTabsWidget->setCurrentIndex(0);


    codecWidgets.push_back(new CodecParametersWidget("mjpeg","mjpeg","matroska",this));
    codecWidgets.last()->setCodecName("MJPEG");
    codecWidgets.push_back(new CodecParametersWidget("h261","h261","matroska",this));
    codecWidgets.last()->setCodecName("H261");
    codecWidgets.push_back(new CodecParametersWidget("mpeg1","mpeg1video","mpegts",this));
    codecWidgets.last()->setCodecName("MPEG1");
    codecWidgets.push_back(new CodecParametersWidget("mpeg2","mpeg2video","mpegts",this));
    codecWidgets.last()->setCodecName("MPEG2");
    codecWidgets.push_back(new CodecParametersWidget("h264","libx264","matroska",this));
    codecWidgets.last()->setCodecName("H264");
    codecWidgets.push_back(new CodecParametersWidget("h265","libx265","matroska",this));
    codecWidgets.last()->setCodecName("H265");

    for (auto codecWidget : codecWidgets) {

        ui->codecTabsWidget->addTab(codecWidget, codecWidget->getCodecName());

        connect(codecWidget, &CodecParametersWidget::parametersChanged, this,
                &MainWindow::settingsChanged);
    }

    // stream on settings changed
    connect(this, &MainWindow::settingsChanged, this,
            &MainWindow::stream);

    // react on stats changed
    connect(ui->videoPlayback, &VideoPlaybackWidget::statsChanged, ui->videoInfo, &VideoStatisticsWidget::onStatsChange);

    // stream on tab changed
    connect(ui->codecTabsWidget, &QTabWidget::currentChanged, this,
            &MainWindow::settingsChanged);

    connect(&cameraNameGetterProcess,
            SIGNAL(finished(int, QProcess::ExitStatus)), this,
            SLOT(parseCameraNameProbeOutput(int, QProcess::ExitStatus)));



    connect(&singleFrameProcess,
            SIGNAL(finished(int, QProcess::ExitStatus)), this,
            SLOT(onSingleFrameGotten(int, QProcess::ExitStatus)));

}

MainWindow::~MainWindow() { delete ui; }

void MainWindow::closeEvent(QCloseEvent *a) {
    (void)a;

    streamingProcess->stopStreaming();
    ui->videoInfo->stopProbe();
}

void MainWindow::on_actionOpen_file_triggered() {

    QString filePath = QFileDialog::getOpenFileName(
        this, tr("Open file"), QDir::homePath(), tr("Multimedia files (*)"),
        Q_NULLPTR, QFileDialog::DontUseNativeDialog);
    openFromFile(filePath);
}

void MainWindow::on_actionOpen_from_camera_triggered() {
    openFromCamera();
}

void MainWindow::on_actionCompare_multiple_codecs_triggered() {
    resetPlayback();

    CodecSelector codecSelector(codecComparisonWindow, this);
    //codecSelector.setMainWindowHandler(ui->codecTabs);
    codecSelector.setModal(true);
    codecSelector.exec();
}

void MainWindow::stream() {
    qDebug() << "starting stream...";
    QString streamingParameters = getStreamingParameters();

    resetPlayback();

    streamingProcess->startStreaming(streamingParameters);

    QString frameProbeCommand = FFmpegCommand::getFrameProbeCommand(encodedVideoHost, encodedVideoPort);
    ui->videoInfo->startFrameProbe(frameProbeCommand);
    QString streamProbeCommand = FFmpegCommand::getStreamProbeCommand(encodedVideoHost, encodedVideoPort);
    ui->videoInfo->startStreamProbe(streamProbeCommand);

    ui->videoPlayback->startPlayers();
    qDebug() << "started stream";
}

void MainWindow::resetPlayback() {
    ui->videoInfo->clearFrameQueue();

    ui->videoPlayback->stopPlayers();

    streamingProcess->stopStreaming();

    ui->videoInfo->stopProbe();
}





void MainWindow::on_actionChange_raw_host_triggered()
{
    bool ok;
    QString input;
    input = QInputDialog::getText(this, tr("Change host"), tr("Multicast host for streaming (raw):"), QLineEdit::Normal, rawVideoHost, &ok);
    if(ok){
        rawVideoHost = input;
        resetPlayback();
        ui->videoPlayback->startPlayers();
    }

}

void MainWindow::on_actionChange_raw_port_triggered()
{
    bool ok;
    QString input;
    input = QInputDialog::getText(this, tr("Change port"), tr("Multicast port for streaming (raw):"), QLineEdit::Normal, rawVideoPort, &ok);
    if(ok){
        rawVideoPort = input;
        resetPlayback();
        stream();
    }
}


void MainWindow::on_actionChange_encoded_host_triggered()
{
    bool ok;
    QString input;
    input = QInputDialog::getText(this, tr("Change host"), tr("Multicast host for streaming (encoded):"), QLineEdit::Normal, encodedVideoHost, &ok);
    if(ok){
        encodedVideoHost = input;
        resetPlayback();
        stream();
    }
}

void MainWindow::on_actionChange_encoded_port_triggered()
{
    bool ok;
    QString input;
    input = QInputDialog::getText(this, tr("Change port"), tr("Multicast port for streaming (encoded):"), QLineEdit::Normal, encodedVideoPort, &ok);
    if(ok){
        encodedVideoPort = input;
        resetPlayback();
        stream();
    }
}

void MainWindow::on_actionHelp_triggered()
{
    QMessageBox msgBox;
    msgBox.setWindowTitle("Help");
    msgBox.setText("\t\t\tCodec Preview\n\n\n\nCreated by Kamil Kurp, Piotr Puszkarski and Paweł Szopiński\t");
    msgBox.exec();
}

void MainWindow::on_actionMacroblocks_triggered()
{
    getSingleFrame();
}


void MainWindow::openFromFile(QString filePath) {
    if (!filePath.isEmpty()) {
        streamingProcess->setInputParameters("-re");
        streamingProcess->setInputLocation("\"" + filePath + "\"");
        codecComparisonWindow->setInputParameters("-re");
        codecComparisonWindow->setInputLocation("\"" + filePath + "\"");
        settingsChanged();
    }
}

void MainWindow::openFromCamera() {
    streamingProcess->setInputParameters("-f dshow");
    codecComparisonWindow->setInputParameters("-f dshow");

    cameraNameGetterProcess.kill();
    cameraNameGetterProcess.waitForFinished();
    cameraNameGetterProcess.start(FFMPEG +
                                  " -list_devices true -f dshow -i dummy");

     //when process is done parseCameraNameProbeOutput runs and opens camera
}


QString MainWindow::getStreamingParameters() {
    if (streamingProcess->getInputParameters().isEmpty()) {
        return "";
    }

    if (streamingProcess->getInputLocation().isEmpty()) {
        return "";
    }

    CodecParametersWidget *codecWidget =
        codecWidgets.at(ui->codecTabsWidget->currentIndex());
    QMap<QString, QString> *streamingParametersMap =
        codecWidget->getStreamingParameters();

    if (streamingParametersMap->isEmpty()) {
        return "";
    }

    QString streamingParameters =
        FFmpegCommand::parametersToString(streamingParametersMap) + " -an";
    qDebug() << "streamingParameters =" << streamingParameters;

    return streamingParameters;
}


void MainWindow::parseCameraNameProbeOutput(int a,
                                                 QProcess::ExitStatus b) {
    // silence warning
    (void)a;
    (void)b;

    QRegularExpression re("\"(.*?)\"");
    QRegularExpressionMatch match =
        re.globalMatch(cameraNameGetterProcess.readAllStandardError()).next();

    QString inputLocation =
        QString("video=") + QString(match.captured().toUtf8().constData());
    //settingsChanged();

    streamingProcess->setInputLocation(inputLocation);
    codecComparisonWindow->setInputLocation(inputLocation);

    settingsChanged();

    qDebug() << inputLocation;
}

void MainWindow::getSingleFrame() {
    QString address = ENCODED_VIDEO_PROTOCOL + "://" + ENCODED_VIDEO_HOST +
                             ":" + ENCODED_VIDEO_PORT;

    singleFrameProcess.start(FFMPEG + " -i " + address + " -t 1 -vframes 1 -f image2 singleframe.jpg -y");
    qDebug() << FFMPEG + " -i " + address + " -t 1 -vframes 1 -f image2 singleframe.jpg -y";
}

void MainWindow::onSingleFrameGotten(int a, QProcess::ExitStatus b) {
    (void)a;
    (void)b;

    qDebug() << "completed";

    scene = new QGraphicsScene();
    view = new QGraphicsView(scene);
    item = new QGraphicsPixmapItem(QPixmap("singleframe.jpg"));
    scene->addItem(item);
    view->show();
}
