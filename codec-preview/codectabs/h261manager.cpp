#include "h261manager.h"

H261Manager::H261Manager(QWidget *parent) : CodecManager(parent, "h261") {
    QList<QString> resolutions({"176:144", "352:288"});
    addParameter("Resolution", "s", resolutions);
    addParameter("Bitrate", "b:v", "");
    addParameter("Minrate", "minrate", "");
    addParameter("Maxrate", "maxrate", "");
    addParameter("Aspect ratio", "aspect", "");
    addParameter("Qscale", "qscale:v", "");
}

H261Manager::~H261Manager() {}
