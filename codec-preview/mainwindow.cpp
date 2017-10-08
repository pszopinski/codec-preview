#include "mainwindow.h"
#include "codecselector.h"
#include "ui_mainwindow.h"

QString rawVideoHost = RAW_VIDEO_HOST;
QString encodedVideoHost = ENCODED_VIDEO_HOST;
QString rawVideoPort = RAW_VIDEO_PORT;
QString encodedVideoPort = ENCODED_VIDEO_PORT;


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
    setWindowState(Qt::WindowMaximized);
    ui->setupUi(this);

    // stream on settings changed
    connect(ui->codecTabs, &CodecTabsWidget::settingsChanged, this,
            &MainWindow::stream);
    // stream on tab changed
    connect(ui->codecTabs, &CodecTabsWidget::currentTabChanged, this,
            &MainWindow::stream);

    connect(ui->videoPlayback, &VideoPlaybackWidget::statsChanged, ui->videoInfo, &VideoInfoWidget::onStatsChange);
}

MainWindow::~MainWindow() { delete ui; }

void MainWindow::closeEvent(QCloseEvent *a) {
    (void)a;

    ui->codecTabs->stopStreaming();
    ui->videoInfo->stopProbe();
}

void MainWindow::on_actionOpen_file_triggered() {

    QString filePath = QFileDialog::getOpenFileName(
        this, tr("Open file"), QDir::homePath(), tr("Multimedia files (*)"),
        Q_NULLPTR, QFileDialog::DontUseNativeDialog);
    ui->codecTabs->openFromFile(filePath);
}

void MainWindow::on_actionOpen_from_camera_triggered() {
    ui->codecTabs->openFromCamera();
}

void MainWindow::on_actionCompare_multiple_codecs_triggered() {
    resetPlayback();

    CodecSelector codecSelector;
    codecSelector.setMainWindowHandler(ui->codecTabs);
    codecSelector.setModal(true);
    codecSelector.exec();
}

void MainWindow::stream() {
    qDebug() << "starting stream...";
    ui->codecTabs->getStreamingParameters();

    QString streamingParameters = ui->codecTabs->getStreamingParameters();

    resetPlayback();

    ui->codecTabs->startStreaming(streamingParameters);

    QString frameProbeCommand = ui->codecTabs->getProbeCommand();
    ui->videoInfo->startFrameProbe(frameProbeCommand);
    QString streamProbeCommand = ui->codecTabs->getStreamCommand();
    ui->videoInfo->startStreamProbe(streamProbeCommand);

    ui->videoPlayback->startPlayers();
    qDebug() << "started stream";
}

void MainWindow::resetPlayback() {
    ui->videoInfo->clearFrameQueue();

    ui->videoPlayback->stopPlayers();

    ui->codecTabs->stopStreaming();

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
