#include "h261manager.h"

H261Manager::H261Manager(QWidget *parent) : CodecManager(parent, "h261") {
    streamingParameters->insertMulti(
        "vf",
        "scale=352:288:force_original_aspect_ratio=decrease,pad=352:288:(ow-iw)/2:(oh-ih)/2");
    ;
}

H261Manager::~H261Manager() {}
