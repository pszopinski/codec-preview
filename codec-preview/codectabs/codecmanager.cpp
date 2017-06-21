#include "codecmanager.h"
#include "ui_codecmanager.h"

CodecManager::CodecManager(QWidget *parent, QString encoder)
    : QWidget(parent), ui(new Ui::CodecManager),
      streamingParameters(new QMap<QString, QString>), layoutCounter(0) {
    ui->setupUi(this);

    streamingParameters->insert("c:v", encoder);
    addParameter("FPS", "r", "");

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

    insertParameter(layout);
}

void CodecManager::addParameter(QString label, QString parameter,
                                QList<QString> values) {
    // Create a new layout for the parameter
    QVBoxLayout *layout = new QVBoxLayout(this);

    // Add a QLabel
    QLabel *labelWidget = new QLabel(label, this);
    layout->addWidget(labelWidget);

    // Add a QComboBox
    QComboBox *comboBox = new QComboBox(this);
    comboBox->insertItems(0, values);
    layout->addWidget(comboBox);

    // Make the form interactive
    streamingParameters->insert(parameter, values[0]);
    connect(comboBox, &QComboBox::currentTextChanged,
            [=](const QString &newValue) {
                if (newValue != streamingParameters->value(parameter)) {
                    streamingParameters->insert(parameter, newValue);
                    emit parametersChanged();
                }
            });

    insertParameter(layout);
}

void CodecManager::insertParameter(QLayout *layout) {
    // Calculate position
    int row = layoutCounter / 5;
    int column = layoutCounter % 5;

    // Insert the layout
    ui->mainLayout->addLayout(layout, row, column);
    layoutCounter++;
}
