#ifndef MJPEGMANAGER_H
#define MJPEGMANAGER_H

#include <QWidget>

#include "codecmanager.h"

class MJPEGManager : public CodecManager {
    Q_OBJECT

  public:
    explicit MJPEGManager(QWidget *parent = 0);
    OrderedMap<QString, QString> *getStreamingParameters();
    ~MJPEGManager();
};

#endif // MJPEGMANAGER_H
