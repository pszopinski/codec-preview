#ifndef MPEG1MANAGER_H
#define MPEG1MANAGER_H

#include <QWidget>

#include "codecmanager.h"

namespace Ui {
class MPEG1Manager;
}

class MPEG1Manager : public CodecManager {
    Q_OBJECT

  public:
    explicit MPEG1Manager(QWidget *parent = 0);
    ~MPEG1Manager();

  private:
    Ui::MPEG1Manager *ui;
};

#endif // MPEG1MANAGER_H
