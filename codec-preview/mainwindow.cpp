#include "mainwindow.h"
#include "selectcodecs.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
    setWindowState(Qt::WindowMaximized);
    ui->setupUi(this);

    connect(ui->codecTabs, &CodecTabsWidget::settingsChanged, this,
            &MainWindow::broadcast);
    connect(ui->codecTabs, &CodecTabsWidget::currentTabChanged, this,
            &MainWindow::broadcast);
}

MainWindow::~MainWindow() { delete ui; }

void MainWindow::closeEvent(QCloseEvent *event) {
    (void)event; // silence annoying warning

    ui->codecTabs->stopStreaming();
    ui->videoInfo->stopProbe();
}

// void CodecComparisonWindow::on_crf_returnPressed()
//{
//    codecManagers.at(ui->tabWidget->currentIndex())->setCRF(ui->crf->text());
//    settingsChanged();
//}

// void CodecComparisonWindow::on_crf_editingFinished()
//{
//    codecManagers.at(ui->tabWidget->currentIndex())->setCRF(ui->crf->text());
//    settingsChanged();
//}

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

    SelectCodecs selectCodecs;
    selectCodecs.setMainWindowHandler(ui->codecTabs);
    selectCodecs.setModal(true);
    selectCodecs.exec();
}

void MainWindow::broadcast() {
    qDebug() << "Starting broadcast...";
    ui->codecTabs->getStreamingParameters();

    QString streamingParameters = ui->codecTabs->getStreamingParameters();

    resetPlayback();

    ui->codecTabs->startStreaming(streamingParameters);

    QString frameProbeCommand = ui->codecTabs->getProbeCommand();
    ui->videoInfo->startFrameProbe(frameProbeCommand);
    QString streamProbeCommand = ui->codecTabs->getStreamCommand();
    ui->videoInfo->startStreamProbe(streamProbeCommand);

    ui->videoPlayback->startPlayers();
    qDebug() << "Started broadcast";

}

void MainWindow::resetPlayback() {
    ui->videoInfo->clearFrameQueue();

    ui->videoPlayback->stopPlayers();

    ui->codecTabs->stopStreaming();

    ui->videoInfo->stopProbe();
}
