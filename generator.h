#ifndef GENERATOR_H
#define GENERATOR_H

//#include <math.h>
#include <qmath.h>
#include <qendian.h>

#include <QObject>
#include <QAudioOutput>
#include <QIODevice>

class Generator : public QIODevice
{
    Q_OBJECT

public:
    Generator(const QAudioFormat &format, qint64 durationUs, int sampleRate, QObject *parent = 0);
    ~Generator();

    void start();
    void stop();

    qint64 readData(char *data, qint64 maxlen);
    qint64 writeData(const char *data, qint64 len);
    qint64 bytesAvailable() const;

private:
    void generateData(const QAudioFormat &format, qint64 durationUs, int sampleRate);

private:
    qint64 m_pos;
    QByteArray m_buffer;
};

#endif // GENERATOR_H
