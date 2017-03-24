#include "audioout.h"

const int DurationSeconds = 1;
const int DataSampleRateHz = 44100;

AudioOut::AudioOut(int tone, double vol, QObject *parent) : QObject(parent)
{
    ToneSampleRateHz = tone==0?20:tone;
    m_volume = vol==0?0.02:vol;
    qDebug()<<m_volume<<ToneSampleRateHz;
    m_format.setSampleRate(DataSampleRateHz);
    m_format.setChannelCount(1);
    m_format.setSampleSize(16);
    m_format.setCodec("audio/pcm");
    m_format.setByteOrder(QAudioFormat::LittleEndian);
    m_format.setSampleType(QAudioFormat::SignedInt);

    m_generator = new Generator(m_format, DurationSeconds*1000000, ToneSampleRateHz, this);
    m_generator->start();

    checkOut();

    QTimer *timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), SLOT(checkOut()));
    timer->start(5000);
}

void AudioOut::checkOut()
{
    if (device != QAudioDeviceInfo::defaultOutputDevice()) {
        qDebug()<<device.deviceName();
        device = QAudioDeviceInfo::defaultOutputDevice();
        qDebug()<<device.deviceName();

        if (!device.isFormatSupported(m_format))
        {
            m_format = device.nearestFormat(m_format);
            m_generator->stop();
            m_generator->deleteLater();
            m_generator = new Generator(m_format, DurationSeconds*1000000, ToneSampleRateHz, this);
            m_generator->start();
        }

        if (!m_audioOutput) {
            m_audioOutput->stop();
            m_audioOutput->deleteLater();
        }

        m_audioOutput = new QAudioOutput(device, m_format, this);
        m_audioOutput->start(m_generator);
        m_audioOutput->setVolume(m_volume);
    }
}
