#ifndef TRANSCODINGPROCESS_H
#define TRANSCODINGPROCESS_H


#include <QProcess>
#include <QDebug>

#include "constants.h"

class StreamingProcess : public QProcess
{
private:
    QString inputLocation;
    QString inputParameters;


public:
    StreamingProcess();
    static QString buildStreamingCommand(QString inputParameters,
                                         QString inputLocation,
                                         QString outputPrameters,
                                         QString rawLocation,
                                         QString encodedLocation);
    void startStreaming(QString streamingParameters);
    void stopStreaming();
    void setInputLocation(QString location);
    void setInputParameters(QString parameters);
    QString getInputLocation();
    QString getInputParameters();

};



#endif // TRANSCODINGPROCESS_H
