#include "mainwindow.h"
#include "codecselector.h"
#include "ui_mainwindow.h"

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
