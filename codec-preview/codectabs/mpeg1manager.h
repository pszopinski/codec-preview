#ifndef MPEG1MANAGER_H
#define MPEG1MANAGER_H

#include <QWidget>

#include "codecmanager.h"

class MPEG1Manager : public CodecManager {
    Q_OBJECT

  public:
    explicit MPEG1Manager(QWidget *parent = 0);
    ~MPEG1Manager();
};

#endif // MPEG1MANAGER_H
