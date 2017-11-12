#ifndef PARAMMANAGER_H
#define PARAMMANAGER_H

#include <QMap>
#include <QString>

class ParamManager {
  public:
    ParamManager();
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
    const QString ASPECTRATIO =
        "The proportional relationship between its width and its height\n"
        "Format: integer:integer\n"
        "Example: 16:9";
    const QString QSCALE = "Quality scale\n"
                           "Format: integer\n"
                           "range: 1-30\n"
                           "Example: 15";
    const QString RESOLUTION = "Resultion of the video\n"
                               "Format: width:height\n"
                               "Example: 1920:1080";
    const QString BUFFERSIZE = "Buffer size";
    const QString CONSTANTRATEFACTOR = "Default quality (and rate control)\n"
                                       "Format: integer\n"
                                       "Range:\n"
                                       " 0-51\n 0-lossless 51-worst\n"
                                       "Example: 25";
    const QString SCALE = "Scale";
    const QString QUANTIZATION =
        "Quantization\n"
        "Format: integer\n"
        "Range:\n"
        "0-n\n lower values - better quality higher values - worse quality"
        "Example: 15";
};

#endif // PARAMMANAGER_H
