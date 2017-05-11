#ifndef CODEC_H
#define CODEC_H

#include <QProcess>


class Codec
{
public:
    virtual void start(QProcess &process, QString file) = 0;
};

#endif // CODEC_H
