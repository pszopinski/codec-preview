#ifndef CODECMANAGER_H
#define CODECMANAGER_H

#include <QWidget>

class CodecManager : public QWidget {
    Q_OBJECT

  protected:
    QString encoderParameter;
    QString pixelFormatParameter;
    QString crfParameter;
    QString filterParameter;
    QString presetParameter;
    QString formatParameter;

  public:
    explicit CodecManager(QWidget *parent = 0);

    QString getStreamingParameters();

  signals:

  public slots:
};

#endif // CODECMANAGER_H
