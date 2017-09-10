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
  const QString FPS = "Frames per second";
  const QString BITRATE = "Bits per second";
  const QString MINRATE = "minimum bit rate";
  const QString MAXRATE = "maximum bir rate";
  const QString ASPECTRATIO = "aspect ratio";
  const QString QSCALE = "quality scale\nformat: [integer]\nrange: 1-30";
  const QString RESOLUTION =
      "change resultion of video\ninput: [width]:[height]";
  const QString BUFFERSIZE = "buffer size";
  const QString CONSTANTRATEFACTOR = "default quality (and rate control) "
                                     "setting\ninput: [integer]\nrange: "
                                     "0-51\n0-lossless 51-worst";
  const QString SCALE = "scale";
};

#endif // PARAMMANAGER_H
