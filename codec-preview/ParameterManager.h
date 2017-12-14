#ifndef PARAMMANAGER_H
#define PARAMMANAGER_H

#include <QMap>
#include <QString>

class ParameterManager {
  public:
    ParameterManager();
    QString getHint(QString paramName);
    void setHint(QString paramName, QString tooltip);

  private:
    QMap<QString, QString> *paramHints;
    void initTooltips();

    // tooltips
    const QString FPS = "Frames per second\n"
                        "Format: integer\n"
                        "Example: 30";

    const QString BITRATE = "Bits per second\n"
                            "Format: integer\n"
                            "Example: 500";
    const QString MINRATE = "Minimum bit rate\n"
                            "Format: integer\n"
                            "Example: 300";
    const QString MAXRATE = "Maximum bit rate\n"
                            "Format: integer\n"
                            "Example: 600";
    const QString RESOLUTION = "Resultion of the video\n"
                               "Format: width:height\n"
                               "Example: 1920:1080";
    const QString BUFFERSIZE = "Buffer size";
    const QString QUANTIZATION = "Quantization factor\n"
                                 "Format: integer\n"
                                 "Range: 1-31 (the lower the better quality)\n"
                                 "Example: 15";
    const QString MOTION_VECTORS = "Draw motion vectors on the encoded video\n"
                                   "This has no effect for camera input.";
    const QString GOP_SIZE = "Group of frames size.\n"
                             "The distance between I frames. Defaults to 12.";
    const QString B_FRAMES_LIMIT = "The maximum number of consecutive B frames.\n"
                                   "Enter 0 to disable B frames altogether.";
};

#endif // PARAMMANAGER_H
