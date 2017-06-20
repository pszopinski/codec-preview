#ifndef H261MANAGER_H
#define H261MANAGER_H

#include <QWidget>

#include "codecmanager.h"

class H261Manager : public CodecManager {
    Q_OBJECT

  public:
    explicit H261Manager(QWidget *parent = 0);
    ~H261Manager();
};

#endif // H261MANAGER_H
