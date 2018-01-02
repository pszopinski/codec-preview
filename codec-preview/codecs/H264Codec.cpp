#include "H264Codec.h"

H264Codec::H264Codec() {
    addCheckBox("Motion vectors", "-vf codecview=mv=pf+bf+bb", false);
    addParameter("GOP size", "g", "", "50");
    addParameter("B frames limit", "bf", "", "50");
    addSlider("Quantization", "qp", "24", "1", "51");

    QMap<QString, QString> profiles;
    profiles.insert("baseline", "baseline");
    profiles.insert("main", "main");
    profiles.insert("high", "high");
    profiles.insert("high10", "high10");
    profiles.insert("high422", "high422");
    profiles.insert("high444", "high444");
    addComboBox("Profile", "profile:v", profiles, "high422");

    QMap<QString, QString> levels;
    levels.insert("3.0", "3.0");
    levels.insert("3.1", "3.1");
    levels.insert("4.0", "4.0");
    levels.insert("4.1", "4.1");
    levels.insert("4.2", "4.2");
    addComboBox("Level", "level", levels, "3.0");
}
