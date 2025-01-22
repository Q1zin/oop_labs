#ifndef GAMESCREEN_H
#define GAMESCREEN_H

#include <QWidget>
#include <QGraphicsView>
#include <QTimer>
#include <QPushButton>
#include <QGraphicsRectItem>
#include <QGraphicsProxyWidget>
#include <memory>
#include "include/managers/soundmanager.h"
#include "include/managers/universalfactory.h"
#include "include/levels/levelssettings.h"
#include "include/utils/timer.h"
#include "include/structs/datatexture.h"
#include "include/entities/model/playermodel.h"
#include "include/entities/view/playerview.h"
#include "include/entities/controller/playercontroller.h"
#include "include/entities/model/enemymodel.h"
#include "include/entities/controller/enemycontroller.h"
#include "include/entities/view/enemyview.h"
#include "include/structs/dataenemy.h"
#include "include/managers/gamestate.h"
#include "include/managers/statemanager.h"
#include "include/entities/bullet.h"


struct PauseMenu {
    QScopedPointer<QGraphicsRectItem> resultBox;
    QScopedPointer<QPushButton> resumeButton;
    QScopedPointer<QGraphicsProxyWidget> resumeButtonProxy;
    QScopedPointer<QPushButton> mainMenuButton;
    QScopedPointer<QGraphicsProxyWidget> mainMenuButtonProxy;
};

struct LevelElements {
    QScopedPointer<QPushButton> pauseButton;
    QScopedPointer<QGraphicsProxyWidget> pauseButtonProxy;
    QScopedPointer<Timer> timer;
    QScopedPointer<ITexture> closeFinish;
    std::vector<std::unique_ptr<ITexture>> startTextures;
    std::vector<std::unique_ptr<ITexture>> textures;
};

struct GameWinMenu {
    QScopedPointer<QGraphicsRectItem> resultBox;
    QScopedPointer<QGraphicsTextItem> resultText;
    QScopedPointer<QGraphicsTextItem> timeText;
    QScopedPointer<QPushButton> replayButton;
    QScopedPointer<QGraphicsProxyWidget> replayButtonProxy;
    QScopedPointer<QPushButton> mainMenuButton;
    QScopedPointer<QGraphicsProxyWidget> mainMenuButtonProxy;
    QScopedPointer<QPushButton> nextLevelButton;
    QScopedPointer<QGraphicsProxyWidget> nextLevelButtonProxy;
};

struct GameLoseMenu {
    QScopedPointer<QGraphicsRectItem> resultBox;
    QScopedPointer<QGraphicsTextItem> resultText;
    QScopedPointer<QPushButton> restartButton;
    QScopedPointer<QGraphicsProxyWidget> restartButtonProxy;
    QScopedPointer<QPushButton> mainMenuButton;
    QScopedPointer<QGraphicsProxyWidget> mainMenuButtonProxy;
};

class GameScreen : public QWidget {
    Q_OBJECT

public:
    explicit GameScreen(GameState* gameState, StateManager* stateManager, SoundManager* soundManager, QWidget *parent = nullptr);
    ~GameScreen();

    void loadLevel(int lvl);

signals:
    void returnToMenu();

private slots:
    void shootBullet();

private:
    QGraphicsScene* scene;
    QGraphicsView* view;
    GameState* gameState;
    StateManager* stateManager;
    SoundManager* soundManager;
    PauseMenu pauseMenu;
    LevelElements levelElements;
    GameWinMenu gameWinMenu;
    GameLoseMenu gameLoseMenu;
    QScopedPointer<QGraphicsRectItem> overlay;
    UniversalFactory<ITexture, QString, dataTexture> textureFactory;
    UniversalFactory<EnemyController, EnemyType, dataEnemy> enemyFactory;

    PlayerModel* playerModel;
    PlayerView* playerView;
    PlayerController* playerController;

    std::vector<std::unique_ptr<EnemyController>> listEnemyController;

    void loadTextures(int lvl);
    void startGameLoop();
    void gameLoop();
    void clearTextures();
    void clearEnemy();
    void initPauseMenu();
    void showPauseMenu();
    void hidePauseMenu();
    QPushButton* createButton(const QString& text, const QPoint& pos, const QSize& size = QSize(200, 50));
    QGraphicsTextItem *createText(const QString &text, const QPoint &position, const int size = 20);
    void initOverlay();
    void showOverlay();
    void hideOverlay();
    void initStartLevelElements();
    void initPlayer();
    void initGameWinMenu();
    void showGameWinMenu();
    void hideGameWinMenu();
    void onPlayerTakeCoin(QGraphicsItem* coin);
    void openFinish();
    void onPlayerFinished();
    void onPlayerDie();
    void initGameLoseMenu();
    void showGameLoseMenu();
    void hideGameLoseMenu();

    void keyPressEvent(QKeyEvent* event) override;
    void keyReleaseEvent(QKeyEvent* event) override;

    void handleBulletCollision(QGraphicsItem* item);
};

#endif // GAMESCREEN_H
