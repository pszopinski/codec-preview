#ifndef H264MANAGER_H
#define H264MANAGER_H

#include <QWidget>

#include "codecmanager.h"

class H264Manager : public CodecManager {
    Q_OBJECT

  public:
    explicit H264Manager(QWidget *parent = 0);
    ~H264Manager();
};

#endif // H264MANAGER_H
