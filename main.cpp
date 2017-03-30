#include "camwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    CamWindow w;
    w.show();

    return a.exec();
}
