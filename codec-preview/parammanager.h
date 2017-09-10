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
  const QString FPS = "Description\n Frames per second";
  const QString BITRATE = "Description\n Bits per second";
  const QString MINRATE = "Description\n minimum bit rate";
  const QString MAXRATE = "Description\n maximum bit rate";
  const QString ASPECTRATIO = "Description\n aspect ratio";
  const QString QSCALE =
      "Description\n quality scale\nformat: [integer]\nrange: 1-30";
  const QString RESOLUTION =
      "Description\n change resultion of video\ninput\n [width]:[height]";
  const QString BUFFERSIZE = "Description\n buffer size";
  const QString CONSTANTRATEFACTOR =
      "Descrption\n default quality (and rate control) "
      "setting\ninput\n [integer]\nrange\n"
      " 0-51\n 0-lossless 51-worst";
  const QString SCALE = "Description\n scale";
};

#endif // PARAMMANAGER_H
