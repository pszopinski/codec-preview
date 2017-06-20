#include "codecmanager.h"
#include "ui_codecmanager.h"

CodecManager::CodecManager(QWidget *parent, QString encoder)
    : QWidget(parent), ui(new Ui::CodecManager),
      streamingParameters(new QMap<QString, QString>), layoutCounter(0) {
    ui->setupUi(this);

    streamingParameters->insert("c:v", encoder);
    streamingParameters->insert("f", "matroska");
    addParameter("FPS", "r", "30");
    addParameter("Scale", "s", "640:360");
}

CodecManager::~CodecManager() { delete ui; }

QMap<QString, QString> *CodecManager::getStreamingParameters() {
    // streamingParameters->
    return streamingParameters;
}

void CodecManager::addParameter(QString label, QString parameter,
                                QString value) {
    // Create a new layout for the parameter
    QVBoxLayout *layout = new QVBoxLayout(this);

    // Add a QLabel
    QLabel *labelWidget = new QLabel(label, this);
    layout->addWidget(labelWidget);

    // Add a QLineEdit
    QLineEdit *lineEdit = new QLineEdit(value, this);
    layout->addWidget(lineEdit);

    // Make the form interactive
    streamingParameters->insert(parameter, value);
    connect(lineEdit, &QLineEdit::editingFinished, [=] {
        QString newValue = lineEdit->text();
        streamingParameters->insert(parameter, newValue);
        emit parametersChanged();
    });

    // Calculate the position of the parameter's layout
    int row = layoutCounter;
    int column = 0;

    // Insert the new layout
    ui->mainLayout->addLayout(layout, row, column);
    layoutCounter++;
}
