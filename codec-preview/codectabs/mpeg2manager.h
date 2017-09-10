#ifndef MPEG2MANAGER_H
#define MPEG2MANAGER_H

#include <QWidget>

#include "codecmanager.h"

class MPEG2Manager : public CodecManager {
    Q_OBJECT

  public:
    explicit MPEG2Manager(QWidget *parent = 0);
    QMap<QString, QString> *getStreamingParameters();
    ~MPEG2Manager();
};

#endif // MPEG2MANAGER_H
