#include "codeccomparisonwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    CodecComparisonWindow w;
    w.show();

    w.broadcast("-c:v libx265 -preset ultrafast -q 10 -an -f matroska");

    return a.exec();
}
