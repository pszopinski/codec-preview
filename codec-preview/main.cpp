#include "codeccomparisonwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    //VlcCommon::setPluginPath(app.applicationDirPath() + "/plugins");

    // Print default camera info
    qDebug() << "Default camera info:";
    QCameraInfo defaultCameraInfo = QCameraInfo::defaultCamera();
    if (defaultCameraInfo.isNull()) {
        qDebug() << "YOU AIN'T HAVE ONE!!";
    } else {
        qDebug() << "\tFile: " << defaultCameraInfo.deviceName();
        qDebug() << "\tDescription: " << defaultCameraInfo.description();
    }

    QApplication a(argc, argv);
    CodecComparisonWindow w;
    w.show();


    return a.exec();
}
