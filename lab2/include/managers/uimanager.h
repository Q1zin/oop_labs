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
    void checkVictory(Player *player, ITexture *victoryZone, ITexture* closeFinish);
    void startVictoryCheck(ITexture *victoryZone, ITexture* closeFinish);
    QPushButton* createButton(const QString& text, const QPoint& position, const QSize& size = QSize(200, 50));
    QGraphicsTextItem* createText(const QString& text, const QPoint& position, const int size = 20);
    QGraphicsScene* scene;
    SoundManager* soundManager;
    LevelsSettings* levelSettings;
    Player* player;
    QTimer* victoryCheckTimer;
    QTimer* animationTimer;
    Timer* timer;
    int remainingTime = 0;
    int lvl_now;
    int lvl_count;
    bool in_game;
    bool in_pause;
    void clearUI();

    QGraphicsRectItem* pauseOverlay;
    QGraphicsRectItem* resultBox;
    QPushButton* resumeButton;
    QPushButton* mainMenuButton;
};

#endif // UIMANAGER_H
