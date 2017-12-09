#ifndef PARAMMANAGER_H
#define PARAMMANAGER_H

#include <qt-ordered-map/orderedmap.h>
#include <QString>

class ParamManager {
  public:
    ParamManager();
    QString getHint(QString paramName);
    void setHint(QString paramName, QString tooltip);

  private:
    OrderedMap<QString, QString> *paramHints;
    void initTooltips();

    // tooltips
    const QString FPS = "Frames per second\n"
                        "Format: integer\n"
                        "Example: 30";
    const QString QUALITY = "Quality scale\n"
                           "Format: integer\n"
                           "range: 1-30\n"
                           "Example: 15";
    const QString RESOLUTION = "Resultion of the video\n"
                               "Format: width:height\n"
                               "Example: 1920:1080";
    const QString MOTION_VECTORS = "Draw motion vectors on the encoded video\n"
                                   "This has no effect for camera input.";
    const QString GOP_SIZE = "Group of frames size.\n"
                             "The distance between I frames. Defaults to 12.";
    const QString B_FRAMES_LIMIT = "The maximum number of consecutive B frames.\n"
                                   "Enter 0 to disable B frames altogether.";

};

#endif // PARAMMANAGER_H
