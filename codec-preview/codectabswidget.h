#ifndef CODECTABSWIDGET_H
#define CODECTABSWIDGET_H

#include <QProcess>
#include <QRegularExpression>
#include <QVector>
#include <QWidget>

#include "codectabs/codecmanager.h"
#include "codectabs/h261manager.h"
#include "codectabs/h264manager.h"
#include "codectabs/mjpegmanager.h"
#include "codectabs/mpeg1manager.h"
#include "codectabs/mpeg2manager.h"

#include "codeccomparewindow.h"

namespace Ui {
class CodecTabsWidget;
}

class CodecTabsWidget : public QWidget {
    Q_OBJECT

  private:
    Ui::CodecTabsWidget *ui;
    QVector<CodecManager *> codecManagers;
    QProcess streamingProcess;
    QProcess cameraNameGetterProcess;
    QString inputParameters;
    QString inputLocation;
    bool selectedCodecs[6];
    CodecCompareWindow compareWindow;

  public:
    explicit CodecTabsWidget(QWidget *parent = 0);
    ~CodecTabsWidget();
    void setSelectedCodecs(int first, int second, int third);
    void stopStreaming();
    static QString buildStreamingCommand(QString inputParameters,
                                         QString inputLocation,
                                         QString outputPrameters,
                                         QString rawLocation,
                                         QString encodedLocation);

    static QString buildMultipleStreamingCommands(
        QString inputParameters, QString inputLocation,
        QVector<QString> outputPrameters, QVector<QString> outputLocations);

    static QString buildProbeCommand(QString location, QString params);
    static QString parametersToString(QMap<QString, QString> *parameters);
    void openFromFile(QString filePath);
    void openFromCamera();
    void selectMultipleCodecs();
    QString getStreamingParameters();
    void startStreaming(QString streamingParameters);
    QString getProbeCommand();
    QString getStreamCommand();
    void setCRF(QString value);
    void insertParameter(QVBoxLayout *layout);

  signals:
    void currentTabChanged();
    void settingsChanged();

  private slots:
    void onTabChange();
    void parseCameraNameProbeOutput(int a, QProcess::ExitStatus b);
};

#endif // CODECTABSWIDGET_H
