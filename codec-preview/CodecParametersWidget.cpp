#include "CodecParametersWidget.h"
#include "ui_CodecParametersWidget.h"


CodecParametersWidget::CodecParametersWidget(QWidget *parent, QString encoder)
    : QWidget(parent), ui(new Ui::CodecParametersWidget), layoutCounter(0),
      streamingParameters(new QMap<QString, QString>) {
    ui->setupUi(this);

    streamingParameters->insert("c:v", encoder);

    loadCodecParameters("any");
}

CodecParametersWidget::CodecParametersWidget(QString codecName, QString optionName, QString codecContainer, QWidget *parent)
    : QWidget(parent), ui(new Ui::CodecParametersWidget), layoutCounter(0),
      streamingParameters(new QMap<QString, QString>) {
    ui->setupUi(this);

    streamingParameters->insert("c:v", optionName);

    this->codecContainer = codecContainer;

    loadCodecParameters("any");
    loadCodecParameters(codecName);
}

CodecParametersWidget::~CodecParametersWidget() { delete ui; }

void CodecParametersWidget::addParameterWidget(QString label, QString parameter,
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

void CodecParametersWidget::addParameterWidget(QString label, QString parameter,
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
                    streamingParameters->insert(parameter,
                                                comboMap.value(newValue));
                    emit parametersChanged();
                }
            });

    insertParameterWidget(layout);

    streamingParameters->insert(parameter, comboMap.values().at(0));
}

void CodecParametersWidget::addParameterWidget(QString label, QString command,
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

void CodecParametersWidget::insertParameterWidget(QVBoxLayout *layout) {
    // add stretch to bottom
    layout->addStretch();

    // calculate position
    int row = layoutCounter / 7;
    int column = layoutCounter % 7;

    // insert layout
    ui->mainLayout->addLayout(layout, row, column);
    layoutCounter++;
}


QString CodecParametersWidget::getCodecName() { return codecName; }

void CodecParametersWidget::setCodecName(QString codecName) {
    this->codecName = codecName;
}

Codec *CodecParametersWidget::getCodec(QString codecName) {
    if (codecName == "h261") {
        return new H261Codec();
    }
    if (codecName == "h264") {
        return new H264Codec();
    }
    if (codecName == "h265") {
        return new H265Codec();
    }
    if (codecName == "mjpeg") {
        return new MjpegCodec();
    }
    if (codecName == "mpeg1") {
        return new Mpeg1Codec();
    }
    if (codecName == "mpeg2") {
        return new Mpeg2Codec();
    }
    if (codecName == "any") {
        return new AnyCodec();
    }
    return NULL;
}


void CodecParametersWidget::loadCodecParameters(QString codecName) {
    Codec *codec = CodecParametersWidget::getCodec(codecName);

    QList<QString> parameterNames = codec->getParameterKeys();
    QList<QString> comboBoxNames = codec->getComboBoxKeys();
    QList<QString> checkBoxNames = codec->getCheckBoxKeys();

    for (int i = 0; i < parameterNames.size(); i++) {
        QString paramName = parameterNames.at(i);
        QMap<QString, QString> paramMap = codec->getParameter(paramName);

        addParameterWidget(paramName, paramMap.value("value"),
                           paramMap.value("default"));
    }

    for (int i = 0; i < comboBoxNames.size(); i++) {
        QString paramName = comboBoxNames.at(i);
        QMap<QString, QString> paramMap = codec->getComboBox(paramName);
        QString paramValue = paramMap.value("value");

        paramMap.remove("value");

        addParameterWidget(paramName, paramValue, paramMap);
    }

    for (int i = 0; i < checkBoxNames.size(); i++) {
        QString paramName = checkBoxNames.at(i);
        QMap<QString, QString> paramMap = codec->getCheckBox(paramName);
        QString command = paramMap.value("command");
        bool state = paramMap.value("state") !=
                     ""; // empty string for false, anything else for true

        addParameterWidget(paramName, command, state);
    }
}

QMap<QString, QString> *CodecParametersWidget::getStreamingParameters() {
    QMap<QString, QString> *parameters(streamingParameters);
    // add final parameters
    // parameters->insert("preset", "ultrafast");
    parameters->insert("an", "");
    parameters->insert("f", codecContainer);
    return parameters;
}