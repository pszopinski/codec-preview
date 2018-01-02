#include "CodecParametersWidget.h"
#include "ui_CodecParametersWidget.h"

CodecParametersWidget::CodecParametersWidget(QWidget *parent, QString encoder)
    : QWidget(parent), ui(new Ui::CodecParametersWidget), layoutCounter(0),
      streamingParameters(new QMultiMap<QString, QString>) {
    ui->setupUi(this);

    streamingParameters->insert("c:v", encoder);

    loadCodecParameters("any");
}

CodecParametersWidget::CodecParametersWidget(QString codecName, QString optionName, QString codecContainer,
                                             QWidget *parent)
    : QWidget(parent), ui(new Ui::CodecParametersWidget), layoutCounter(0),
      streamingParameters(new QMultiMap<QString, QString>) {
    ui->setupUi(this);

    streamingParameters->insert("c:v", optionName);

    this->codecContainer = codecContainer;

    loadCodecParameters("any");
    loadCodecParameters(codecName);

    QVBoxLayout *layout = new QVBoxLayout();
    layout->addWidget(new QWidget());
    insertParameterWidget(layout);
}

CodecParametersWidget::~CodecParametersWidget() { delete ui; }

void CodecParametersWidget::addParameterWidget(QString label, QString parameter, QString value, int fixedWidth) {
    // create new layout for parameter
    QVBoxLayout *layout = new QVBoxLayout();

    // add QLabel
    QLabel *labelWidget = new QLabel(label, this);
    if (fixedWidth != 0)
        labelWidget->setFixedWidth(fixedWidth);
    layout->addWidget(labelWidget);

    // add QLineEdit
    QLineEdit *lineEdit = new QLineEdit(value, this);
    if (fixedWidth != 0)
        lineEdit->setFixedWidth(fixedWidth);

    // lineEdit->setMaximumWidth(30);

    // add tooltips
    QString tooltip = paramManager.getHint(label);
    labelWidget->setToolTip(tooltip);
    lineEdit->setToolTip(tooltip);

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

void CodecParametersWidget::addComboBoxWidget(QString label, QString parameter, QMap<QString, QString> comboMap,
                                              QString defaultValue) {
    // create new layout for parameter
    QVBoxLayout *layout = new QVBoxLayout();

    // add QLabel
    QLabel *labelWidget = new QLabel(label, this);
    layout->addWidget(labelWidget);

    // add QComboBox
    QComboBox *comboBox = new QComboBox(this);
    comboBox->insertItems(0, comboMap.keys());

    int index = comboBox->findText(defaultValue);
    if (index != -1) {
        comboBox->setCurrentIndex(index);
    }

    layout->addWidget(comboBox);

    // add tooltips
    QString tooltip = paramManager.getHint(label);
    labelWidget->setToolTip(tooltip);
    comboBox->setToolTip(tooltip);

    comboBox->setFixedWidth(100);

    connect(comboBox, &QComboBox::currentTextChanged, [=](const QString &newValue) {
        if (newValue != streamingParameters->value(parameter)) {
            streamingParameters->replace(parameter, comboMap.value(newValue));
            emit parametersChanged();
        }
    });

    insertParameterWidget(layout);

    streamingParameters->insert(parameter, comboMap.values().at(index));
}

void CodecParametersWidget::addCheckBoxWidget(QString label, QString command, bool value) {
    // create new layout for parameter
    QVBoxLayout *layout = new QVBoxLayout();

    // add QLabel
    QLabel *labelWidget = new QLabel(label, this);
    layout->addWidget(labelWidget);

    // add QCheckBox
    QCheckBox *checkBox = new QCheckBox(this);
    checkBox->setChecked(value);
    layout->addWidget(checkBox);

    // add tooltips
    QString tooltip = paramManager.getHint(label);
    labelWidget->setToolTip(tooltip);
    checkBox->setToolTip(tooltip);

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

void CodecParametersWidget::addSliderWidget(QString label, QString parameter, QString value, QString min, QString max) {
    // create new layout for parameter
    QVBoxLayout *layout = new QVBoxLayout();

    // add QLabel
    QLabel *labelWidget = new QLabel(label, this);
    layout->addWidget(labelWidget);

    // add QSlider
    QSlider *slider = new QSlider(Qt::Horizontal, this);
    slider->setValue(value.toInt());
    slider->setMinimum(min.toInt());
    slider->setMaximum(max.toInt());

    // add tooltips
    QString tooltip = paramManager.getHint(label);
    labelWidget->setToolTip(tooltip);
    slider->setToolTip(tooltip);

    slider->setFixedWidth(100);

    layout->addWidget(slider);

    // make form interactive
    streamingParameters->insert(parameter, QString(value));
    connect(slider, &QSlider::sliderReleased, [=] {
        QString newValue = QString::number(slider->value());
        if (newValue != streamingParameters->value(parameter)) {
            streamingParameters->insert(parameter, newValue);
            emit parametersChanged();
        }
    });

    insertParameterWidget(layout);
}

void CodecParametersWidget::insertParameterWidget(QVBoxLayout *layout) {
    // add stretch to bottom
    layout->addStretch();

    // calculate position
    int row = layoutCounter / 12;
    int column = layoutCounter % 12;

    // insert layout
    ui->mainLayout->addLayout(layout, row, column);
    layoutCounter++;
}

QString CodecParametersWidget::getCodecName() { return codecName; }

void CodecParametersWidget::setCodecName(QString codecName) { this->codecName = codecName; }

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
    QList<QString> sliderNames = codec->getSliderKeys();
    QList<QString> *parameterOrder = codec->getParameterOrder();

    for (int i = 0; i < sliderNames.size(); i++) {
        QString paramName = sliderNames.at(i);
        QMap<QString, QString> paramMap = codec->getSlider(paramName);

        addSliderWidget(paramName, paramMap.value("value"), paramMap.value("default"), paramMap.value("min"),
                        paramMap.value("max"));
    }

    for (int i = 0; i < parameterOrder->size(); i++) {
        QString paramName = parameterOrder->at(i);
        QMap<QString, QString> paramMap = codec->getParameter(paramName);

        addParameterWidget(paramName, paramMap.value("value"), paramMap.value("default"),
                           paramMap.value("width").toInt());
    }

    for (int i = 0; i < comboBoxNames.size(); i++) {
        QString paramName = comboBoxNames.at(i);
        QMap<QString, QString> paramMap = codec->getComboBox(paramName);
        QString paramValue = paramMap.value("value");
        QString defaultValue = paramMap.value("default");

        paramMap.remove("value");
        paramMap.remove("default");

        addComboBoxWidget(paramName, paramValue, paramMap, defaultValue);
    }

    for (int i = 0; i < checkBoxNames.size(); i++) {
        QString paramName = checkBoxNames.at(i);
        QMap<QString, QString> paramMap = codec->getCheckBox(paramName);
        QString command = paramMap.value("command");
        bool state = paramMap.value("state") != ""; // empty string for false, anything else for true

        addCheckBoxWidget(paramName, command, state);
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
