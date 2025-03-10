#ifndef GAMESTATE_H
#define GAMESTATE_H

#include <QObject>
#include <memory>
#include <vector>
#include "include/levels/levelssettings.h"
#include "include/entities/model/playermodel.h"
#include "include/entities/view/playerview.h"
#include "include/entities/model/enemymodel.h"
#include "include/structs/dataenemy.h"

class GameState : public QObject {
    Q_OBJECT
public:
    explicit GameState(QObject* parent = nullptr);
    ~GameState() = default;

    int getLevel() const;
    void setLevel(int level);

    int getLevelCount() const;
    void setLevelCount(int count);

    int getBestTime(int lvl) const;
    void updateBestTime(int time);

    std::vector<std::pair<QString, dataTexture>> getTexturesLevel(int lvl);
    std::vector<std::pair<EnemyType, dataEnemy>> getEnemysLevel(int lvl);

    void collectedСoin();

signals:
    void finishOpened();

private:
    std::unique_ptr<LevelsSettings> levelsSettings;
    int currentLevel;
    int lvl_count;
    int count_coins;
    bool finishIsOpen;
};

#endif // GAMESTATE_H
