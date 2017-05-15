#ifndef CODECMANAGER_H
#define CODECMANAGER_H

#include <QWidget>

class CodecManager : public QWidget {
    Q_OBJECT

  protected:
    QString streamingParameters;

  public:
    explicit CodecManager(QWidget *parent = 0);

    QString getStreamingParameters();

  signals:

  public slots:
};

#endif // CODECMANAGER_H
