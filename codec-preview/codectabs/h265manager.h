#ifndef H265MANAGER_H
#define H265MANAGER_H

#include <QWidget>

#include "codecmanager.h"

class H265Manager : public CodecManager {
    Q_OBJECT

  public:
    explicit H265Manager(QWidget *parent = 0);
    ~H265Manager();
};

#endif // H265MANAGER_H
