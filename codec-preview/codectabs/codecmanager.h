#ifndef CODECMANAGER_H
#define CODECMANAGER_H

#include <QComboBox>
#include <QDebug>
#include <QLabel>
#include <QLineEdit>
#include <QList>
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

    ParamManager paramManager;
    QString codecName;

  protected:
    QMap<QString, QString> *streamingParameters;

  public:
    explicit CodecManager(QWidget *parent = 0, QString encoder = "copy");
    ~CodecManager();

    virtual QMap<QString, QString> *getStreamingParameters();
    void addParameter(QString label, QString parameter, QString value);
    void addParameter(QString label, QString parameter, QList<QString> values);
    void insertParameter(QVBoxLayout *layout);
    QString getCodecName();
    void setCodecName(QString codecName);

  signals:
    void parametersChanged();
};

#endif // CODECMANAGER_H
