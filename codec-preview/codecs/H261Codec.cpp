#include "H261Codec.h"

H261Codec::H261Codec() {
    addSlider("Quantization", "q:v", "24", "1", "51");
    addCheckBox("Motion vectors", "-vf codecview=mv=pf+bf+bb", false);
    addParameter("GOP size", "g", "", "50");
    addParameter("B frames limit", "bf", "", "50");
    addCheckBox("Aspect ratio correction", "-vf setdar=r=a", true);

    QMap<QString, QString> resolutions;
    resolutions.insert("176:144", "176x144");
    resolutions.insert("352:288", "352x288");
    addComboBox("Resolution", "s", resolutions, "176:144");
}
