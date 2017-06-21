#include "codecmanager.h"
#include "ui_codecmanager.h"

CodecManager::CodecManager(QWidget *parent, QString encoder)
    : QWidget(parent), ui(new Ui::CodecManager),
      streamingParameters(new QMap<QString, QString>), layoutCounter(0) {
    ui->setupUi(this);

    streamingParameters->insert("c:v", encoder);
    addParameter("FPS", "r", "");
    addParameter("Bitrate", "b:v", "");
    addParameter("Minrate", "minrate", "");
    addParameter("Maxrate", "maxrate", "");
    addParameter("Buffer size", "bufsize", "");
    addParameter("Aspect ratio", "aspect", "");
    addParameter("Qscale", "qscale:v", "");
    addParameter("Costant Rate Factor", "crf", "");
}

CodecManager::~CodecManager() { delete ui; }

QMap<QString, QString> *CodecManager::getStreamingParameters() {
    QMap<QString, QString> *parameters(streamingParameters);
    // Add final parameters
    parameters->insert("f", "matroska");
    parameters->insert("an", "");
    return parameters;
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
        if (newValue != streamingParameters->value(parameter)) {
            streamingParameters->insert(parameter, newValue);
            emit parametersChanged();
        }
    });

    // Calculate the position of the parameter's layout
    int row = layoutCounter / 5;
    int column = layoutCounter % 5;

    // Insert the new layout
    ui->mainLayout->addLayout(layout, row, column);
    layoutCounter++;
}
