#include "MacroblockPickerView.h"

MacroblockPickerView::MacroblockPickerView() {}

MacroblockPickerView::MacroblockPickerView(QGraphicsScene *scene) : QGraphicsView(scene) {}

void MacroblockPickerView::mousePressEvent(QMouseEvent *event) {
    qDebug() << "clicked at " << event->x() << " " << event->y();
}
