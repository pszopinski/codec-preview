#ifndef H261MANAGER_H
#define H261MANAGER_H

#include <QWidget>

#include "codecmanager.h"

namespace Ui {
class H261Manager;
}

class H261Manager : public CodecManager {
    Q_OBJECT

  public:
    explicit H261Manager(QWidget *parent = 0);
    ~H261Manager();

  private:
    Ui::H261Manager *ui;
};

#endif // H261MANAGER_H
