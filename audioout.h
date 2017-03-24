#ifndef AUDIOOUT_H
#define AUDIOOUT_H

#include <QObject>
#include <QAudioOutput>
#include <QDebug>
#include <QTimer>

#include <generator.h>
class AudioOut : public QObject
{
    Q_OBJECT
public:
    explicit AudioOut(int tone, double vol, QObject *parent = 0);

private:
    int ToneSampleRateHz;
    double m_volume;
    QAudioDeviceInfo device;
    QAudioOutput *m_audioOutput;
    QAudioFormat m_format;
    Generator *m_generator;

signals:

private slots:
    void checkOut();

public slots:
};

#endif // AUDIOOUT_H
