#ifndef CODECMANAGER_H
#define CODECMANAGER_H

#include "parammanager.h"
#include <QComboBox>
#include <QDebug>
#include <QLabel>
#include <QLineEdit>
#include <QList>
#include <QMap>
#include <QString>
#include <QVBoxLayout>
#include <QWidget>

#include "codecs/h261.h"
#include "codecs/h264.h"
#include "codecs/h265.h"
#include "codecs/mjpeg.h"
#include "codecs/mpeg1.h"
#include "codecs/mpeg2.h"
#include "codecs/allcodecs.h"


namespace Ui {
class CodecManager;
}

class CodecManager : public QWidget {
    Q_OBJECT

  private:
    Ui::CodecManager *ui;
    int layoutCounter;

    ParamManager paramManager;
    QString codecName;

  protected:
    QMap<QString, QString> *streamingParameters;

  public:
    //TEMPORARY CHANGE FROM COPY TO MJPEG

    explicit CodecManager(QWidget *parent = 0, QString encoder = "mjpeg");
    ~CodecManager();

    virtual QMap<QString, QString> *getStreamingParameters();
    void addParameter(QString label, QString parameter, QString value);
    void addParameter(QString label, QString parameter, QMap<QString, QString> values);
    void insertParameter(QVBoxLayout *layout);
    QString getCodecName();
    void setCodecName(QString codecName);


public:
    static Codec* getCodec(QString codecName);

  signals:
    void parametersChanged();
};

#endif // CODECMANAGER_H
