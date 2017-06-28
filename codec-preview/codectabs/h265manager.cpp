#include "h265manager.h"

H265Manager::H265Manager(QWidget *parent) : CodecManager(parent, "libx265") {
    addParameter("Bitrate", "b:v", "");
    addParameter("Minrate", "minrate", "");
    addParameter("Maxrate", "maxrate", "");
    addParameter("Buffer size", "bufsize", "");
    addParameter("Aspect ratio", "aspect", "");
    addParameter("Costant Rate Factor", "crf", "");
    addParameter("Resolution", "s", "");
}

H265Manager::~H265Manager() {}
