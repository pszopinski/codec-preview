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
#include <QString>
#include <QVBoxLayout>
#include <QWidget>

#include "codecs/allcodecs.h"
#include "codecs/h261.h"
#include "codecs/h264.h"
#include "codecs/h265.h"
#include "codecs/mjpeg.h"
#include "codecs/mpeg1.h"
#include "codecs/mpeg2.h"
#include "ParameterValidator.h"

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
    QMap<QString, QString> *streamingParameters;

  public:
    // TEMPORARY CHANGE FROM COPY TO MJPEG

    explicit CodecParametersWidget(QWidget *parent = 0, QString encoder = "mjpeg");
    CodecParametersWidget(QString codecName, QString optionName, QString codecContainer, QWidget *parent);
    ~CodecParametersWidget();

    virtual QMap<QString, QString> *getStreamingParameters();
    void addParameterWidget(QString label, QString parameter, QString value);
    void addParameterWidget(QString label, QString parameter,
                            QMap<QString, QString> values);
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
