#ifndef CODECPARAMETERSWIDGET_H
#define CODECPARAMETERSWIDGET_H

#include "ParameterManager.h"
#include <QCheckBox>
#include <QComboBox>
#include <QDebug>
#include <QLabel>
#include <QLineEdit>
#include <QList>
#include <QMap>
#include <QMultiMap>
#include <QString>
#include <QVBoxLayout>
#include <QWidget>

#include "ParameterValidator.h"
#include "codecs/AnyCodec.h"
#include "codecs/H261Codec.h"
#include "codecs/H264Codec.h"
#include "codecs/H265Codec.h"
#include "codecs/MjpegCodec.h"
#include "codecs/Mpeg1Codec.h"
#include "codecs/Mpeg2Codec.h"

namespace Ui {
class CodecParametersWidget;
}

class CodecParametersWidget : public QWidget {
    Q_OBJECT

  private:
    Ui::CodecParametersWidget *ui;
    int layoutCounter;

    ParameterManager paramManager;
    QString codecName;
    ParameterValidator paramValidator;
    QString codecContainer;

  protected:
    QMultiMap<QString, QString> *streamingParameters;

  public:
    // TEMPORARY CHANGE FROM COPY TO MJPEG

    explicit CodecParametersWidget(QWidget *parent = 0, QString encoder = "mjpeg");
    CodecParametersWidget(QString codecName, QString optionName, QString codecContainer, QWidget *parent);
    ~CodecParametersWidget();

    virtual QMap<QString, QString> *getStreamingParameters();
    void addParameterWidget(QString label, QString parameter, QString value);
    void addParameterWidget(QString label, QString parameter, QMap<QString, QString> values);
    void addParameterWidget(QString label, QString command, bool value);
    void insertParameterWidget(QVBoxLayout *layout);
    QString getCodecName();
    void setCodecName(QString codecName);
    void loadCodecParameters(QString codecName);

  public:
    static Codec *getCodec(QString codecName);

  signals:
    void parametersChanged();
};

#endif // CODECPARAMETERSWIDGET_H
