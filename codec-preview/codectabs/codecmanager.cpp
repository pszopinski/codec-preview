#include "codecmanager.h"
#include "ui_codecmanager.h"

CodecManager::CodecManager(QWidget *parent, QString encoder)
    : QWidget(parent), ui(new Ui::CodecManager), layoutCounter(0),
      streamingParameters(new OrderedMap<QString, QString>) {
    ui->setupUi(this);

    streamingParameters->insert("c:v", encoder);

    QString codecName = "all";

    Codec *codec = CodecManager::getCodec(codecName);

    QList<QString> parameterNames = codec->getParameterKeys();
    QList<QString> comboBoxNames = codec->getComboBoxKeys();
    QList<QString> checkBoxNames = codec->getCheckBoxKeys();

    for (int i = 0; i < parameterNames.size(); i++) {
        QString paramName = parameterNames.at(i);
        OrderedMap<QString, QString> paramMap = codec->getParameter(paramName);

        addParameterWidget(paramName, paramMap.value("value"),
                           paramMap.value("default"));
    }

    for (int i = 0; i < comboBoxNames.size(); i++) {
        QString paramName = comboBoxNames.at(i);
        OrderedMap<QString, QString> paramMap = codec->getComboBox(paramName);
        QString paramValue = paramMap.value("value");

        paramMap.remove("value");

        addParameterWidget(paramName, paramValue, paramMap);
    }

    for (int i = 0; i < checkBoxNames.size(); i++) {
        QString paramName = checkBoxNames.at(i);
        OrderedMap<QString, QString> paramMap = codec->getCheckBox(paramName);
        QString command = paramMap.value("command");
        bool state = paramMap.value("state") !=
                     ""; // empty string for false, anything else for true

        addParameterWidget(paramName, command, state);
    }
}

CodecManager::~CodecManager() { delete ui; }

void CodecManager::addParameterWidget(QString label, QString parameter,
                                      QString value) {
    // create new layout for parameter
    QVBoxLayout *layout = new QVBoxLayout();

    // add QLabel
    QLabel *labelWidget = new QLabel(label, this);
    // labelWidget->setMaximumWidth(30);

    // add tooltip
    labelWidget->setToolTip(paramManager.getHint(label));
    layout->addWidget(labelWidget);

    // add QLineEdit
    QLineEdit *lineEdit = new QLineEdit(value, this);
    // lineEdit->setMaximumWidth(30);

    // PP: validation
    paramValidator.addValidation(lineEdit, parameter);
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

    insertParameterWidget(layout);
}

void CodecManager::addParameterWidget(QString label, QString parameter,
                                      OrderedMap<QString, QString> comboMap) {
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
                    streamingParameters->insert(parameter,
                                                comboMap.value(newValue));
                    emit parametersChanged();
                }
            });

    insertParameterWidget(layout);

    streamingParameters->insert(parameter, comboMap.values().at(0));
}

void CodecManager::addParameterWidget(QString label, QString command,
                                      bool value) {
    // create new layout for parameter
    QVBoxLayout *layout = new QVBoxLayout();

    // add QLabel
    QLabel *labelWidget = new QLabel(label, this);
    labelWidget->setToolTip(paramManager.getHint(label));
    layout->addWidget(labelWidget);

    // add QCheckBox
    QCheckBox *checkBox = new QCheckBox(this);
    checkBox->setChecked(value);
    layout->addWidget(checkBox);

    // The command is stored as the key with an empty value in
    // streamingParameters

    connect(checkBox, &QCheckBox::toggled, [=](bool checked) {
        if (checked) {
            streamingParameters->insert(command, "");
        } else {
            streamingParameters->remove(command);
        }
        emit parametersChanged();
    });

    insertParameterWidget(layout);

    if (value) {
        streamingParameters->insert(command, "");
    }
}

void CodecManager::insertParameterWidget(QVBoxLayout *layout) {
    // add stretch to bottom
    layout->addStretch();

    // calculate position
    int row = layoutCounter / 7;
    int column = layoutCounter % 7;

    // insert layout
    ui->mainLayout->addLayout(layout, row, column);
    layoutCounter++;
}

OrderedMap<QString, QString> *CodecManager::getStreamingParameters() {
    return NULL;
}

QString CodecManager::getCodecName() { return codecName; }

void CodecManager::setCodecName(QString codecName) {
    this->codecName = codecName;
}

Codec *CodecManager::getCodec(QString codecName) {
    if (codecName == "h261") {
        return new H261();
    }
    if (codecName == "h264") {
        return new H264();
    }
    if (codecName == "h265") {
        return new H265();
    }
    if (codecName == "mjpeg") {
        return new Mjpeg();
    }
    if (codecName == "mpeg1") {
        return new Mpeg1();
    }
    if (codecName == "mpeg2") {
        return new Mpeg2();
    }
    if (codecName == "all") {
        return new AllCodecs();
    }
    return NULL;
}
