#ifndef MPEG2MANAGER_H
#define MPEG2MANAGER_H

#include <QWidget>

#include "codecmanager.h"

namespace Ui {
class MPEG2Manager;
}

class MPEG2Manager : public CodecManager {
    Q_OBJECT

  public:
    explicit MPEG2Manager(QWidget *parent = 0);
    ~MPEG2Manager();

  private:
    Ui::MPEG2Manager *ui;
};

#endif // MPEG2MANAGER_H
