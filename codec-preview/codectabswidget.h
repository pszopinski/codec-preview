#ifndef CODECTABSWIDGET_H
#define CODECTABSWIDGET_H

#include <QProcess>
#include <QVector>
#include <QWidget>

#include "codectabs/codecmanager.h"
#include "codectabs/h261manager.h"
#include "codectabs/h264manager.h"
#include "codectabs/mjpegmanager.h"
#include "codectabs/mpeg1manager.h"
#include "codectabs/mpeg2manager.h"

#include "showcodecs.h"
//#include "commonparameterswidget.h"

namespace Ui {
class CodecTabsWidget;
}

class CodecTabsWidget : public QWidget {
    Q_OBJECT

  private:
    QVector<CodecManager *> codecManagers;
    // QVector<CommonParametersWidget *> commonParamsWidgets;

    QProcess streamingProcess;
    QString inputParameters;
    QString inputLocation;
    bool selectedCodecs[6];
    ShowCodecs showCodecs;

  public:
    explicit CodecTabsWidget(QWidget *parent = 0);
    ~CodecTabsWidget();
    void setSelectedCodecs(int first, int second, int third);
    void stopStreaming();

    static QString buildStreamingCommand(QString inputParameters,
                                         QString inputLocation,
                                         QVector<QString> outputPrameters,
                                         QVector<QString> outputLocations);
    static QString buildProbeCommand(QString location, QString params);

    static QString parametersToString(QMap<QString, QString> *parameters);

    // QVector<CodecManager *> getCodecManagers();

    void openFromFile(QString filePath);
    void openFromCamera();
    void selectMultipleCodecs();

    QString getStreamingParameters();
    void startStreaming(QString streamingParameters);

    QString getProbeCommand();
    QString getStreamCommand();

    void setCRF(QString value);

  private slots:
    void onTabChange();

  signals:
    void currentTabChanged();
    void settingsChanged();

  private:
    Ui::CodecTabsWidget *ui;
};

#endif // CODECTABSWIDGET_H
