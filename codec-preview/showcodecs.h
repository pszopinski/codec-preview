#ifndef SHOWCODECS_H
#define SHOWCODECS_H

#include "constants.h"
#include <QDebug>
#include <QProcess>
#include <QString>
#include <QWidget>
#include <VLCQtCore/Audio.h>
#include <VLCQtCore/Common.h>
#include <VLCQtCore/Enums.h>
#include <VLCQtCore/Instance.h>
#include <VLCQtCore/Media.h>
#include <VLCQtCore/MediaPlayer.h>
#include <VLCQtCore/Stats.h>
#include <qlabel.h>

namespace Ui {
class ShowCodecs;
}

class ShowCodecs : public QWidget {
  Q_OBJECT

private:
  Ui::ShowCodecs *ui;
  VlcInstance *vlcInstance;
  VlcMedia *vlcMedia[4];
  VlcMediaPlayer *vlcMediaPlayers[4];
  QProcess streamingProcess;

public:
  explicit ShowCodecs(QWidget *parent = 0);
  ~ShowCodecs();
  void broadcast(QString streamingCommand);
  void closeEvent(QCloseEvent *event);
  QLabel *original;
  QLabel *label1;
  QLabel *label2;
  QLabel *label3;
};

#endif // SHOWCODECS_H
