#ifndef CODECMANAGER_H
#define CODECMANAGER_H

#include <QWidget>
#include <QMap>

class CodecManager : public QWidget {
    Q_OBJECT

  protected:
    QString encoderParameter;
    QString pixelFormatParameter;
    QString crfParameter;
    QString filterParameter;
    QString presetParameter;
    QString formatParameter;
    QMap<QString, QString> parameters;

  public:
    explicit CodecManager(QWidget *parent = 0);

    QMap<QString, QString> getStreamingParameters();
    void setCRF(QString value);
    QString getCRF();

  signals:
//    void parametersChanged();
  public slots:
};

#endif // CODECMANAGER_H
