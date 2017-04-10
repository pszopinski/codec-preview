#include <QCoreApplication>
#include <QTcpSocket>

#include "server.h"

//FFMPEG COMMAND TO STREAM THE VIDEO:
//ffmpeg -y -i hmm.mp4 -s 720x480 -vcodec mjpeg -f nut - | ffmpeg -f nut -i - -vcodec rawvideo -vf format=pix_fmts=rgb24 -pixel_format rgb24 -f rawvideo tcp://localhost:2000

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    Server server;

    return a.exec();
}
