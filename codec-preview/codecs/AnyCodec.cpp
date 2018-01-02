#include "AnyCodec.h"

AnyCodec::AnyCodec() {
    addSlider("Quantization", "q:v", "24", "1", "51");

    addParameter("FPS", "r", "", "50");

    QMap<QString, QString> crop_options;
    crop_options.insert("100%", "crop=in_w:in_h");
    crop_options.insert("75%", "crop=0.75*in_w:0.75*in_h");
    crop_options.insert("50%", "crop=0.50*in_w:0.50*in_h");
    crop_options.insert("25%", "crop=0.25*in_w:0.25*in_h");
    addComboBox("Crop", "vf", crop_options, "100%");

    addParameter("Bitrate", "b:v", "", "50");
    addParameter("Minrate", "minrate", "", "50");
    addParameter("Maxrate", "maxrate", "", "50");
    addParameter("Buffer size", "bufsize", "", "50");
}
