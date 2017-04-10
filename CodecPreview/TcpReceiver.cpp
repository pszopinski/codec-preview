#include "TcpReceiver.h"

TcpReceiver::TcpReceiver(QObject *parent) : QObject(parent) {

}

void TcpReceiver::start(int width, int height) {
    this->width = width;
    this->height = height;
    server = new QTcpServer(this);
    connect(server, SIGNAL(newConnection()), SLOT(newConnection()));
    qDebug() << "Listening:" << server->listen(QHostAddress::LocalHost, 2000);
}


void TcpReceiver::newConnection() {
    while (server->hasPendingConnections()) {
        QTcpSocket *socket = server->nextPendingConnection();
        connect(socket, SIGNAL(readyRead()), SLOT(readyRead()));
        connect(socket, SIGNAL(disconnected()), SLOT(disconnected()));
        QByteArray *buffer = new QByteArray();
        buffers.insert(socket, buffer);
    }
}

void TcpReceiver::disconnected() {
    QTcpSocket *socket = static_cast<QTcpSocket*>(sender());
    QByteArray *buffer = buffers.value(socket);
    socket->deleteLater();
    delete buffer;
}

void TcpReceiver::readyRead() {
    QTcpSocket *socket = static_cast<QTcpSocket*>(sender());
    QByteArray *buffer = buffers.value(socket);
    qint32 size = 3*width*height;
    while (socket->bytesAvailable() > 0) {
        buffer->append(socket->readAll());
        while (size > 0 && buffer->size() >= size) {
            if (buffer->size() >= size) {
                QByteArray data = buffer->mid(0, size);
                buffer->remove(0, size);

                QImage img((const uchar*)data.data(),width,height,QImage::Format_RGB888);
                emit imageReceived(img);
            }
        }
    }
}

