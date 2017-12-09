#include "h261.h"

H261::H261() {
    OrderedMap<QString, QString> resolutions;
    resolutions.insert("176:144", "176x144");
    resolutions.insert("352:288", "352x288");
    addComboBox("Resolution", "s", resolutions);
}
