#ifndef MJPEGMANAGER_H
#define MJPEGMANAGER_H

#include <QWidget>

#include "codecmanager.h"

namespace Ui {
class MJPEGManager;
}

class MJPEGManager : public CodecManager {
    Q_OBJECT

  public:
    explicit MJPEGManager(QWidget *parent = 0);
    ~MJPEGManager();

  private:
    Ui::MJPEGManager *ui;
};

#endif // MJPEGMANAGER_H
