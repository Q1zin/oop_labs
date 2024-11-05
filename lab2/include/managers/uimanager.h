#ifndef UIMANAGER_H
#define UIMANAGER_H

#include <QWidget>
#include <QPushButton>
#include <QLabel>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPainter>
#include <QGraphicsScene>

#include "include/managers/soundmanager.h"
#include "include/entities/player.h"
#include "include/utils/timer.h"
#include "include/textures/invisibletexture.h"
#include "include/textures/texture.h"
#include "include/levels/levelssettings.h"

struct PauseMenu {
    QPushButton* resumeButton = nullptr;
    QGraphicsProxyWidget* resumeButtonProxy = nullptr;
    QPushButton* mainMenuButton = nullptr;
    QGraphicsProxyWidget* mainMenuButtonProxy = nullptr;
    QGraphicsRectItem* resultBox = nullptr;
};

struct LevelButtons {
    std::vector<std::pair<QPushButton*, QGraphicsTextItem*>> buttonsAndTimes;
    QPushButton* exitButton;
};

struct GameWinMenu {
    QGraphicsTextItem* resultText = nullptr;
    QGraphicsTextItem* timeText = nullptr;
    QPushButton* replayButton = nullptr;
    QGraphicsProxyWidget* replayButtonProxy = nullptr;
    QPushButton* mainMenuButton = nullptr;
    QGraphicsProxyWidget* mainMenuButtonProxy = nullptr;
    QPushButton* nextLevelButton = nullptr;
    QGraphicsProxyWidget* nextLevelButtonProxy = nullptr;
    QGraphicsRectItem* resultBox = nullptr;
};

struct GameLoseMenu {
    QGraphicsRectItem* resultBox = nullptr;
    QPushButton* restartButton = nullptr;
    QGraphicsProxyWidget* restartButtonProxy = nullptr;
    QPushButton* mainMenuButton = nullptr;
    QGraphicsProxyWidget* mainMenuButtonProxy = nullptr;
};

struct LevelElements {
    QPushButton* pauseButton = nullptr;
    Timer* timer = nullptr;
    Player* player = nullptr;
    std::vector<ITexture*> textures;
    ITexture* victoryZone = nullptr;
    ITexture* closeFinish = nullptr;
};

class UiManager : public QObject
{
    Q_OBJECT
public:
    UiManager(QGraphicsScene* scene, SoundManager* soundManager);
    ~UiManager();
public slots:
    void showMainMenu();
    void showGameUI(int lvl);
    void showGameWin();
    void restartGame();
    void nextLevel();
    void pauseGame();
    void gameOver();
    void resumeGame();

signals:
    void startGame();
    void exitGame();

private:
    void showOverlay();
    void showPauseMenu();
    void showLevelButtons();
    void showGameWinMenu();
    void showGameLoseMenu();
    void showLevel();

    void hideOverlay();
    void hidePauseMenu();
    void hideLevelButtons();
    void hideGameWinMenu();
    void hideGameLoseMenu();
    void hideLevel();

    void setPause();
    void setUnpause();


    PauseMenu pauseMenu;
    LevelButtons levelButtons;
    GameWinMenu gameWinMenu;
    GameLoseMenu gameLoseMenu;
    LevelElements levelElements;
    QGraphicsRectItem* overlay;

    void checkVictory();
    void startVictoryCheck();
    QPushButton* createButton(const QString& text, const QPoint& position, const QSize& size = QSize(200, 50));
    QGraphicsTextItem* createText(const QString& text, const QPoint& position, const int size = 20);
    QGraphicsScene* scene;
    SoundManager* soundManager;
    LevelsSettings* levelSettings;
    QTimer* victoryCheckTimer;
    QTimer* animationTimer;
    int remainingTime = 0;
    int lvl_now;
    int lvl_count;
    bool in_game;
    bool in_pause;
    void clearUI();



};

#endif // UIMANAGER_H
