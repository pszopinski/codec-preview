#ifndef MACROBLOCKSWINDOW_H
#define MACROBLOCKSWINDOW_H

#include <QGraphicsPixmapItem>
#include <QGraphicsScene>
#include <QPixmap>
#include <QWidget>

namespace Ui {
class MacroblocksWindow;
}

class MacroblocksWindow : public QWidget {
    Q_OBJECT

  public:
    explicit MacroblocksWindow(QPixmap *macroblockPixmap, QWidget *parent = 0);
    ~MacroblocksWindow();

  private:
    Ui::MacroblocksWindow *ui;

    QPixmap *macroblockPixmap;
    QGraphicsScene *scene;
    QGraphicsPixmapItem *item;
};

#endif // MACROBLOCKSWINDOW_H
