#include "server.h"

static inline qint32 ArrayToInt(QByteArray source);

cv::Mat qImage2Mat(const QImage& src)
{

    cv::Mat tmp(src.height(),src.width(), CV_8UC3,(uchar*)src.bits(),src.bytesPerLine());
    cv::Mat res;
    cvtColor(tmp, res,CV_RGB2GRAY);
    return res;
}

Server::Server(QObject *parent) : QObject(parent)
{
    server = new QTcpServer(this);
    connect(server, SIGNAL(newConnection()), SLOT(newConnection()));
    qDebug() << "Listening:" << server->listen(QHostAddress::LocalHost, 2000);
}

void Server::newConnection()
{
    while (server->hasPendingConnections())
    {
        QTcpSocket *socket = server->nextPendingConnection();
        connect(socket, SIGNAL(readyRead()), SLOT(readyRead()));
        connect(socket, SIGNAL(disconnected()), SLOT(disconnected()));
        QByteArray *buffer = new QByteArray();
        qint32 *s = new qint32(0);
        buffers.insert(socket, buffer);
        sizes.insert(socket, s);
    }
}

void Server::disconnected()
{
    QTcpSocket *socket = static_cast<QTcpSocket*>(sender());
    QByteArray *buffer = buffers.value(socket);
    qint32 *s = sizes.value(socket);
    socket->deleteLater();
    delete buffer;
    delete s;
}

void Server::readyRead()
{
    qDebug() << "Reading some data";
    QTcpSocket *socket = static_cast<QTcpSocket*>(sender());
    QByteArray *buffer = buffers.value(socket);
    //qint32 *s = sizes.value(socket);
    qint32 size = 3*720*480;
    while (socket->bytesAvailable() > 0)
    {
        buffer->append(socket->readAll());
        while (/*(size == 0 && buffer->size() >= 4) ||*/ (size > 0 && buffer->size() >= size)) //While can process data, process it
        {
            //if (size == 0 && buffer->size() >= 4) //if size of data has received completely, then store it on our global variable
            //{
            //    size = ArrayToInt(buffer->mid(0, 4));
            //    *s = size;
            //    buffer->remove(0, 4);
            //}
            if (/*size > 0 && */buffer->size() >= size) // If data has received completely, then emit our SIGNAL with the data
            {
                QByteArray data = buffer->mid(0, size);
                buffer->remove(0, size);
                //size = 0;
                //*s = size;

                qDebug() << "Filled data array";
                qDebug() << data.size();


                cv::Mat image;
                QImage img((const uchar*)data.data(),720,480,QImage::Format_RGB888);

                //create mat image from qimage
                image = qImage2Mat(img);

                namedWindow( "Display window", cv::WINDOW_AUTOSIZE );// Create a window for display.
                imshow( "Display window", image );


                //emit dataReceived(data);
            }
        }
    }
}

qint32 ArrayToInt(QByteArray source)
{
    qint32 temp;
    QDataStream data(&source, QIODevice::ReadWrite);
    data >> temp;
    return temp;
}



