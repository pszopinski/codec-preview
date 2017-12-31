#ifndef MACROBLOCKPICKERVIEW_H
#define MACROBLOCKPICKERVIEW_H

#include <QDebug>
#include <QGraphicsPixmapItem>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QMouseEvent>

#include <MacroblocksWindow.h>

class MacroblockPickerView : public QGraphicsView {
  private:
    QGraphicsPixmapItem *item;
    QPixmap *pixmap;
    MacroblocksWindow *macroblocksWindow;
    bool zoomed = false;
    int zoomScale = 5;

  public:
    MacroblockPickerView();
    MacroblockPickerView(QGraphicsScene *scene, QPixmap *framePixmap);
    void mousePressEvent(QMouseEvent *event);
};

#endif // MACROBLOCKPICKERVIEW_H
