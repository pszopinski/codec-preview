#include "codeccomparisonwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    CodecComparisonWindow w;
    w.show();

    //w.broadcast("ffmpeg -i /dev/video0 -vf scale=352:288 -vcodec h261 -f matroska udp://localhost:3000");

    return a.exec();
}
