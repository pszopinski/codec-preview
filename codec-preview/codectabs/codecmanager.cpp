#include "codecmanager.h"
#include "ui_codecmanager.h"

CodecManager::CodecManager(QWidget *parent, QString encoder)
    : QWidget(parent), ui(new Ui::CodecManager), layoutCounter(0),
      streamingParameters(new QMap<QString, QString>) {
    ui->setupUi(this);

    streamingParameters->insert("c:v", encoder);
    addParameter("FPS", "r", "");
}

CodecManager::~CodecManager() { delete ui; }

QMap<QString, QString> *CodecManager::getStreamingParameters() {
    QMap<QString, QString> *parameters(streamingParameters);
    // add final parameters
    parameters->insert("f", "matroska");
    parameters->insert("preset", "ultrafast");
    parameters->insert("an", "");
    return parameters;
}

void CodecManager::addParameter(QString label, QString parameter,
                                QString value) {
    // create new layout for parameter
    QVBoxLayout *layout = new QVBoxLayout();

    // add QLabel
    QLabel *labelWidget = new QLabel(label, this);
    layout->addWidget(labelWidget);

    // add QLineEdit
    QLineEdit *lineEdit = new QLineEdit(value, this);
    layout->addWidget(lineEdit);

    // make form interactive
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
    // create new layout for parameter
    QVBoxLayout *layout = new QVBoxLayout();

    // add QLabel
    QLabel *labelWidget = new QLabel(label, this);
    layout->addWidget(labelWidget);

    // add QComboBox
    QComboBox *comboBox = new QComboBox(this);
    comboBox->insertItems(0, values);
    layout->addWidget(comboBox);

    // make form interactive
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

void CodecManager::insertParameter(QVBoxLayout *layout) {
    // add stretch to bottom
    layout->addStretch();

    // calculate position
    int row = layoutCounter / 7;
    int column = layoutCounter % 7;

    // insert layout
    ui->mainLayout->addLayout(layout, row, column);
    layoutCounter++;
}
