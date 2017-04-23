#include "codeccomparisonwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    //VlcCommon::setPluginPath(app.applicationDirPath() + "/plugins");

    QApplication a(argc, argv);
    CodecComparisonWindow w;
    w.show();

    return a.exec();
}
