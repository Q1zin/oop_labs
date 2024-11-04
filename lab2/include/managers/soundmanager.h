#ifndef SOUNDMANAGER_H
#define SOUNDMANAGER_H

#include <QMediaPlayer>
#include <QAudioOutput>
#include <memory>

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
    std::unique_ptr<QMediaPlayer> musicPlayer;
    std::unique_ptr<QMediaPlayer> soundEffectPlayer;
    std::unique_ptr<QMediaPlayer> soundEffectCoin;
    std::unique_ptr<QMediaPlayer> soundEffectShot;
    std::unique_ptr<QAudioOutput> musicOutput;
    std::unique_ptr<QAudioOutput> soundEffectOutput;
    std::unique_ptr<QAudioOutput> soundEffectOutputCoin;
    std::unique_ptr<QAudioOutput> soundEffectOutputShot;
};

#endif // SOUNDMANAGER_H
