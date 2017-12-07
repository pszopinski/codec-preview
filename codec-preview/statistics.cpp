#include "statistics.h"

Statistics::Statistics() {
    frameSize.setWidth(0);
    frameSize.setHeight(0);
}

QSize Statistics::getFrameSize() { return frameSize; }

void Statistics::setFrameSize(QSize frameSize) {
    // PP: tez XD
    if (frameSize.width() > 0)
        this->frameSize.setWidth(frameSize.width());
    if (frameSize.height() > 0)
        this->frameSize.setHeight(frameSize.height());
}
