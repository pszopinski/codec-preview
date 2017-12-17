#ifndef MACROBLOCKPICKERVIEW_H
#define MACROBLOCKPICKERVIEW_H

#include <QDebug>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QMouseEvent>

class MacroblockPickerView : public QGraphicsView {
  public:
    MacroblockPickerView();
    MacroblockPickerView(QGraphicsScene *scene);
    void mousePressEvent(QMouseEvent *event);
};

#endif // MACROBLOCKPICKERVIEW_H
