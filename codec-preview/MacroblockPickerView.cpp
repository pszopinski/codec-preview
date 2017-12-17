#include "MacroblockPickerView.h"

MacroblockPickerView::MacroblockPickerView() {}

MacroblockPickerView::MacroblockPickerView(QGraphicsScene *scene, QPixmap *framePixmap) : QGraphicsView(scene) {
    this->framePixmap = framePixmap;
}

void MacroblockPickerView::mousePressEvent(QMouseEvent *event) {
    qDebug() << "clicked at " << event->x() << " " << event->y();

    QRect rect(event->x() - event->x() % 8, event->y() - event->y() % 8, 8, 8);
    macroblockPixmap = new QPixmap(framePixmap->copy(rect));
    macroblocksWindow = new MacroblocksWindow(macroblockPixmap);
    macroblocksWindow->show();
}
