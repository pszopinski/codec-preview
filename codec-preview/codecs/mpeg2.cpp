#include "mpeg2.h"

Mpeg2::Mpeg2() {
    addParameter("Resolution", "s", "");

    OrderedMap<QString, QString> profiles;
    profiles.insert("422", "0");
    profiles.insert("HIGH", "1");
    profiles.insert("SS", "2");
    profiles.insert("SNR_SCALABLE", "3");
    profiles.insert("MAIN", "4");
    profiles.insert("SIMPLE", "5");
    addComboBox("Profile", "profile:v", profiles);

    OrderedMap<QString, QString> levels;
    levels.insert("422 main", "5");
    levels.insert("422 high", "2");
    levels.insert("main", "8");
    levels.insert("high 1440", "6");
    levels.insert("high", "4");
    addComboBox("Level", "level:v", levels);
}
