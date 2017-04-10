#ifndef TCPRECEIVER_H
#define TCPRECEIVER_H

#include <QtCore>
#include <QtNetwork>
#include <QImage>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <iostream>


class TcpReceiver : public QObject {
    Q_OBJECT
public:
    explicit TcpReceiver(QObject *parent = 0);
    void start(int width, int height);

private slots:
    void newConnection();
    void disconnected();
    void readyRead();

private:
    QTcpServer *server;
    QHash<QTcpSocket*, QByteArray*> buffers;
    int width;
    int height;

signals:
    void imageReceived(QImage);

};

#endif // TCPRECEIVER_H
