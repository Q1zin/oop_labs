#ifndef SOUNDMANAGER_H
#define SOUNDMANAGER_H

#include <QMediaPlayer>
#include <QAudioOutput>

class SoundManager : public QObject
{
    Q_OBJECT
public:
    SoundManager();
    ~SoundManager();
    void setSound(const QString& sound);

public slots:
    void setSoundCoin();
    void setSoundShot();

private:
    QMediaPlayer *musicPlayer;
    QMediaPlayer *soundEffectPlayer;
    QMediaPlayer *soundEffectCoin;
    QMediaPlayer *soundEffectShot;
    QAudioOutput *musicOutput;
    QAudioOutput *soundEffectOutput;
    QAudioOutput *soundEffectOutputCoin;
    QAudioOutput *soundEffectOutputShot;
};

#endif // SOUNDMANAGER_H
