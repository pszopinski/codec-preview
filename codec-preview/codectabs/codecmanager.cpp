#include "codecmanager.h"
#include "ui_codecmanager.h"

CodecManager::CodecManager(QWidget *parent, QString encoder)
    : QWidget(parent), ui(new Ui::CodecManager), layoutCounter(0),
      streamingParameters(new QMap<QString, QString>) {
    ui->setupUi(this);

    streamingParameters->insert("c:v", encoder);
    addParameter("FPS", "r", "");
    addParameter("Quantization", "qp", "");
}

CodecManager::~CodecManager() { delete ui; }

void CodecManager::addParameter(QString label, QString parameter,
                                QString value) {
    // create new layout for parameter
    QVBoxLayout *layout = new QVBoxLayout();

    // add QLabel
    QLabel *labelWidget = new QLabel(label, this);

    labelWidget->setToolTip(paramManager.getHint(label)); // add tooltip
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
                                QMap<QString, QString> comboMap) {
    // create new layout for parameter
    QVBoxLayout *layout = new QVBoxLayout();


    // add QLabel
    QLabel *labelWidget = new QLabel(label, this);

    labelWidget->setToolTip(paramManager.getHint(label)); // add tooltip

    layout->addWidget(labelWidget);

    // add QComboBox
    QComboBox *comboBox = new QComboBox(this);
    comboBox->insertItems(0, comboMap.keys());
    layout->addWidget(comboBox);

    connect(comboBox, &QComboBox::currentTextChanged,
            [=](const QString &newValue) {
                if (newValue != streamingParameters->value(parameter)) {
                    streamingParameters->insert(parameter, comboMap.value(newValue));
                    emit parametersChanged();
                }
            });

    insertParameter(layout);

    streamingParameters->insert(parameter, comboMap.values().at(0));

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

QMap<QString, QString> *CodecManager::getStreamingParameters() { return NULL; }

QString CodecManager::getCodecName() { return codecName; }

void CodecManager::setCodecName(QString codecName) {
    this->codecName = codecName;
}
