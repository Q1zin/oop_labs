#ifndef SOUNDMANAGER_H
#define SOUNDMANAGER_H

#include <QObject>
#include <QMediaPlayer>
#include <QAudioOutput>
#include <QMap>
#include <map>
#include <memory>

class SoundManager : public QObject
{
    Q_OBJECT
public:
    enum class SoundType {
        Menu,
        Game,
        Win,
        GameOver,
        CollectedCoin,
        Shot
    };

    explicit SoundManager(QObject *parent = nullptr);
    ~SoundManager() = default;

    void playSound(SoundType type);
    void setVolume(SoundType type, int volume);
    void stopAll();

private:
    struct SoundInfo {
        QUrl source;
        int loops;
    };

    std::map<SoundType, std::unique_ptr<QMediaPlayer>> players;
    std::map<SoundType, std::unique_ptr<QAudioOutput>> outputs;
    QMap<SoundType, SoundInfo> soundInfos;
    SoundType currentMusicType;

    void initializeSounds();
    void stopCurrentMusic();
};

#endif // SOUNDMANAGER_H
