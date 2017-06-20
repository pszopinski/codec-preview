#include "codecmanager.h"
#include "ui_codecmanager.h"

CodecManager::CodecManager(QWidget *parent, QString encoder)
    : QWidget(parent), ui(new Ui::CodecManager),
      streamingParameters(new QMap<QString, QString>) {
    ui->setupUi(this);

    streamingParameters->insert("c:v", encoder);
    streamingParameters->insert("f", "matroska");
}

CodecManager::~CodecManager() { delete ui; }

QMap<QString, QString> *CodecManager::getStreamingParameters() {
    return streamingParameters;
}
