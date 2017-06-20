#ifndef CODECMANAGER_H
#define CODECMANAGER_H

#include <QDebug>
#include <QLabel>
#include <QLineEdit>
#include <QMap>
#include <QString>
#include <QVBoxLayout>
#include <QWidget>

namespace Ui {
class CodecManager;
}

class CodecManager : public QWidget {
    Q_OBJECT

  private:
    Ui::CodecManager *ui;
    int layoutCounter;

  protected:
    QMap<QString, QString> *streamingParameters;

  public:
    explicit CodecManager(QWidget *parent = 0, QString encoder = "copy");
    ~CodecManager();
    QMap<QString, QString> *getStreamingParameters();
    void addParameter(QString label, QString parameter, QString value);

  signals:
    void parametersChanged();
};

#endif // CODECMANAGER_H
