#ifndef CODEC_H
#define CODEC_H

#include <QProcess>


class Codec
{
protected:
    QString file;
public:
    virtual void start(QProcess &process) = 0;
    virtual QString getFile();
    virtual void setFile(QString file);
};

#endif // CODEC_H
