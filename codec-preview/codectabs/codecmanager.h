#ifndef CODECMANAGER_H
#define CODECMANAGER_H

#include <QMap>
#include <QString>
#include <QWidget>

namespace Ui {
class CodecManager;
}

class CodecManager : public QWidget {
    Q_OBJECT

  private:
    Ui::CodecManager *ui;

  protected:
    QMap<QString, QString> *streamingParameters;

  public:
    explicit CodecManager(QWidget *parent = 0, QString encoder = "copy");
    ~CodecManager();
    QMap<QString, QString> *getStreamingParameters();
};

#endif // CODECMANAGER_H
