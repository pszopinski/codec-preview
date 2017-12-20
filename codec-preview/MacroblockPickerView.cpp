#include "MacroblockPickerView.h"

MacroblockPickerView::MacroblockPickerView() {}

MacroblockPickerView::MacroblockPickerView(QGraphicsScene *scene, QPixmap *framePixmap) : QGraphicsView(scene) {
    this->framePixmap = framePixmap;
}

void MacroblockPickerView::mousePressEvent(QMouseEvent *event) {
    QRect rect(event->x() - event->x() % 16, event->y() - event->y() % 16, 16, 16);
    macroblockPixmap = new QPixmap(framePixmap->copy(rect));
    macroblocksWindow = new MacroblocksWindow(macroblockPixmap);
    macroblocksWindow->show();
}
