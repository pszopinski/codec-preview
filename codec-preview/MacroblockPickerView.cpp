#include "MacroblockPickerView.h"

MacroblockPickerView::MacroblockPickerView() {}

MacroblockPickerView::MacroblockPickerView(QGraphicsScene *scene, QPixmap *pixmap) : QGraphicsView(scene) {
    this->pixmap = pixmap;
}

void MacroblockPickerView::mousePressEvent(QMouseEvent *event) {
    if (!zoomed) {
        QRect rect((event->x() - 50) - (event->x() - 50) % 16, (event->y() - 50) - (event->y() - 50) % 16, 128, 128);
        pixmap = new QPixmap(pixmap->copy(rect));
        QGraphicsScene *scene = new QGraphicsScene();
        scene->addItem(new QGraphicsPixmapItem(*pixmap));
        this->setScene(scene);

        // macroblocksWindow = new MacroblocksWindow(macroblockPixmap);
        this->scale(zoomScale, zoomScale);
        // macroblocksWindow->show();

        this->setFixedSize(128 * zoomScale, 128 * zoomScale);

        // qDebug() << pixmap->width() << " " << pixmap->height();

        zoomed = true;

    }

    else {
        QRect rect((event->x() / zoomScale) - (event->x() / zoomScale) % 16,
                   (event->y() / zoomScale) - (event->y() / zoomScale) % 16, 16, 16);
        // qDebug() << "rect: " << rect.x() << " " << rect.y() << " " << rect.width() << " " << rect.height();
        QPixmap *mbPixmap = new QPixmap(pixmap->copy(rect));
        macroblocksWindow = new MacroblocksWindow(mbPixmap);
        macroblocksWindow->show();
    }
}
