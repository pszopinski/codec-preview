#ifndef CODEC_H
#define CODEC_H

#include <QProcess>

class CodecManager {
  protected:
    QString streamingParameters;

  public:
    CodecManager();

    QString getStreamingParameters();
};

#endif // CODEC_H
