#include "h265manager.h"

H265Manager::H265Manager(QWidget *parent) : CodecManager(parent, "libx265") {
    // addParameter(...);
}

H265Manager::~H265Manager() {}
