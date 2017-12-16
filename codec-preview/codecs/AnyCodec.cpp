#include "AnyCodec.h"

AnyCodec::AnyCodec() {
    addParameter("FPS", "r", "");
    addParameter("Quantization", "q:v", "");

    QMap<QString, QString> crop_options;
    crop_options.insert("100%", "crop=in_w:in_h");
    crop_options.insert("75%", "crop=0.75*in_w:0.75*in_h");
    crop_options.insert("50%", "crop=0.50*in_w:0.50*in_h");
    crop_options.insert("25%", "crop=0.25*in_w:0.25*in_h");
    addComboBox("Crop", "vf", crop_options);

    addParameter("Bitrate", "b:v", "");
    addParameter("Minrate", "minrate", "");
    addParameter("Maxrate", "maxrate", "");
    addParameter("Buffer size", "bufsize", "");
}
