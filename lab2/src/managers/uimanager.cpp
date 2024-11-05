#include <QWidget>
#include <QPushButton>
#include <QLabel>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPainter>
#include <QTimer>
#include <QGraphicsProxyWidget>
#include <QShortcut>

#include "include/managers/uimanager.h"
#include "include/entities/player.h"
#include "include/utils/timer.h"
#include "include/entities/enemy.h"
#include "include/textures/invisibletexture.h"
#include "include/levels/levelssettings.h"
#include "include/textures/itexture.h"
#include "include/managers/texturefactory.h"

UiManager::UiManager(QGraphicsScene* scene, SoundManager* soundManager)
    : scene(scene), soundManager(soundManager), victoryCheckTimer(nullptr), animationTimer(new QTimer(this)) {

    connect(animationTimer, &QTimer::timeout, scene, &QGraphicsScene::advance);
    animationTimer->start(1000 / 60); // Задаю 60 fps

    levelSettings = new LevelsSettings();
    lvl_count = levelSettings->getLevelsCount();

    showMainMenu();
}

UiManager::~UiManager() {}

void UiManager::showMainMenu() {
    clearUI();
    soundManager->setSound("menu");
    in_game = false;
    setUnpause();

    showLevelButtons();
}

void UiManager::showGameUI(int lvl) {

    clearUI();
    if (animationTimer)
        animationTimer->start();
    soundManager->setSound("game");
    lvl_now = lvl;

    in_game = true;
    setUnpause();

    showLevel();
}

void UiManager::startVictoryCheck() {
    if (victoryCheckTimer) {
        victoryCheckTimer->start(100);
    } else {
        victoryCheckTimer = new QTimer(this);
        connect(victoryCheckTimer, &QTimer::timeout, this, &UiManager::checkVictory);
        victoryCheckTimer->start(100);
    }
}

QPushButton *UiManager::createButton(const QString& text, const QPoint& position, const QSize& size) {
    QPushButton* button = new QPushButton(text);
    button->setFixedSize(size.width(), size.height());
    button->move(position.x(), position.y());
    return button;
}

QGraphicsTextItem *UiManager::createText(const QString &text, const QPoint &position, const int size) {
    QGraphicsTextItem* resultText = new QGraphicsTextItem(text);
    resultText->setDefaultTextColor(Qt::black);
    resultText->setFont(QFont("Montserrat", size));
    resultText->setPos(position.x(), position.y());
    scene->addItem(resultText);
    return resultText;
}

void UiManager::checkVictory() {
    if (levelElements.player->getCoins() == 3) {
        delete levelElements.closeFinish;
        levelElements.closeFinish = nullptr;
        levelElements.player->setCoins(0);
    }

    if (levelElements.player->collidesWithItem(levelElements.victoryZone)) {
        if (victoryCheckTimer) {
            victoryCheckTimer->stop();
        }

        if (levelElements.timer) {
            levelElements.timer->stop();
        }

        showGameWin();
    }
}

void UiManager::showGameWin() {
    levelSettings->pauseEnemySpawning(lvl_now);
    levelElements.timer->stop();
    animationTimer->stop();
    soundManager->setSound("win");

    setPause();

    showOverlay();
    showGameWinMenu();

    levelSettings->setBestTime(lvl_now, QTime(0, 0).secsTo(levelElements.timer->getTime()));
}

void UiManager::restartGame()
{
    clearUI();
    showGameUI(lvl_now);
}

void UiManager::nextLevel()
{
    if (lvl_now < lvl_count) {
        showGameUI(lvl_now + 1);
    }
}

void UiManager::pauseGame() {
    if (in_pause) return;

    levelSettings->pauseEnemySpawning(lvl_now);
    levelElements.timer->stop();
    animationTimer->stop();

    setPause();

    levelElements.player->clearFocus();

    showOverlay();
    showPauseMenu();
}

void UiManager::resumeGame() {
    hideOverlay();
    hidePauseMenu();
    in_game = true;
    setUnpause();
    levelElements.player->setFocus();
    animationTimer->start();
    levelElements.timer->resume();
    levelSettings->resumeEnemySpawning(lvl_now);
}

void UiManager::showOverlay() {
    if (overlay) {
        overlay->show();
    } else {
        overlay = new QGraphicsRectItem(0, 0, scene->width(), scene->height());
        overlay->setBrush(QBrush(QColor(0, 0, 0, 150)));
        overlay->setZValue(1000);
        scene->addItem(overlay);
    }
}

void UiManager::showPauseMenu() {
    if (pauseMenu.resultBox) {
        pauseMenu.resultBox->show();
    } else {
        pauseMenu.resultBox = new QGraphicsRectItem(scene->width() / 2 - 150, scene->height() / 2 - 100, 300, 200);
        pauseMenu.resultBox->setBrush(QBrush(Qt::white));
        pauseMenu.resultBox->setZValue(1500);
        scene->addItem(pauseMenu.resultBox);
    }

    if (pauseMenu.resumeButton){
        pauseMenu.resumeButton->show();
    } else {
        pauseMenu.resumeButton = createButton("Вернуться к игре", QPoint(scene->width() / 2 - 100, scene->height() / 2 - 50));
        pauseMenu.resumeButtonProxy = scene->addWidget(pauseMenu.resumeButton);
        pauseMenu.resumeButtonProxy->setZValue(1501);
        connect(pauseMenu.resumeButton, &QPushButton::clicked, this, &UiManager::resumeGame);
    }

    if (pauseMenu.mainMenuButton){
        pauseMenu.mainMenuButton->show();
    } else {
        pauseMenu.mainMenuButton = createButton("Выйти в главное меню", QPoint(scene->width() / 2 - 100, scene->height() / 2 + 10));
        pauseMenu.mainMenuButtonProxy = scene->addWidget(pauseMenu.mainMenuButton);
        pauseMenu.mainMenuButtonProxy->setZValue(1501);
        connect(pauseMenu.mainMenuButton, &QPushButton::clicked, this, &UiManager::showMainMenu);
    }
}

void UiManager::showLevelButtons() {
    if (levelButtons.buttonsAndTimes.empty()) {
        for (int lvlIdx = 1; lvlIdx <= lvl_count; lvlIdx++) {
            int best_time = levelSettings->getBestTime(lvlIdx);
            QGraphicsTextItem* timeText = nullptr;
            if (best_time) {
                timeText = createText("Ваше лучшее время: " + QTime::fromMSecsSinceStartOfDay(best_time * 1000).toString("mm:ss"),
                                      QPoint(520, 100 * lvlIdx + 110));
            } else {
                timeText = createText("Вы ещё не играли, дак погнали!",
                                      QPoint(520, 100 * lvlIdx + 110));
            }
            timeText->setZValue(500);
            QPushButton* startButtonLvl = createButton(QString::number(lvlIdx) + " LVL",
                                                       QPoint(300, 100 + lvlIdx * 100));
            scene->addWidget(startButtonLvl);
            connect(startButtonLvl, &QPushButton::clicked, this, [this, lvlIdx]() {
                showGameUI(lvlIdx);
            });

            levelButtons.buttonsAndTimes.push_back(std::make_pair(startButtonLvl, timeText));
        }

        levelButtons.exitButton = createButton("Выйти", QPoint(300, 200 + lvl_count * 100));
        scene->addWidget(levelButtons.exitButton);
        connect(levelButtons.exitButton, &QPushButton::clicked, this, &UiManager::exitGame);
        scene->addWidget(levelButtons.exitButton);
    } else {
        levelButtons.exitButton->show();
        for (int lvlIdx = 1; lvlIdx <= lvl_count; lvlIdx++) {
            auto& pair = levelButtons.buttonsAndTimes[lvlIdx - 1];
            int best_time = levelSettings->getBestTime(lvlIdx);
            if (best_time) {
                pair.second->setPlainText("Ваше лучшее время: " + QTime::fromMSecsSinceStartOfDay(best_time * 1000).toString("mm:ss"));
            } else {
                pair.second->setPlainText("Вы ещё не играли, дак погнали!");
            }
            if (pair.first) pair.first->show();
            if (pair.second) pair.second->show();
        }
    }
}

void UiManager::showGameWinMenu() {
    if (gameWinMenu.resultBox) {
        gameWinMenu.resultBox->show();
    } else {
        gameWinMenu.resultBox = new QGraphicsRectItem(scene->width() / 2 - 150, scene->height() / 2 - 150, 300, 400);
        gameWinMenu.resultBox->setBrush(QBrush(Qt::white));
        gameWinMenu.resultBox->setZValue(1500);
        scene->addItem(gameWinMenu.resultBox);
    }

    if (gameWinMenu.resultText) {
        gameWinMenu.resultText->show();
    } else {
        gameWinMenu.resultText = createText("Вы победили!", QPoint(scene->width() / 2 - 75, scene->height() / 2 - 90));
        gameWinMenu.resultText->setZValue(1501);
    }

    if (gameWinMenu.timeText) {
        gameWinMenu.timeText->setPlainText("Время: " + levelElements.timer->getTime().toString("mm:ss"));
        gameWinMenu.timeText->show();
    } else {
        gameWinMenu.timeText = createText("Время: " + levelElements.timer->getTime().toString("mm:ss"), QPoint(scene->width() / 2 - 60, scene->height() / 2 - 56));
        gameWinMenu.timeText->setZValue(1501);
    }

    if (gameWinMenu.replayButton) {
        gameWinMenu.replayButton->show();
    } else {
        gameWinMenu.replayButton = createButton("Ещё раз!", QPoint(scene->width() / 2 - 100, scene->height() / 2 + - 10));
        gameWinMenu.replayButtonProxy = scene->addWidget(gameWinMenu.replayButton);
        gameWinMenu.replayButtonProxy->setZValue(1501);
        connect(gameWinMenu.replayButton, &QPushButton::clicked, this, &UiManager::restartGame);
    }

    if (gameWinMenu.mainMenuButton) {
        gameWinMenu.mainMenuButton->show();
    } else {
        gameWinMenu.mainMenuButton = createButton("Главное меню", QPoint(scene->width() / 2 - 100, scene->height() / 2 + 110));
        gameWinMenu.mainMenuButtonProxy = scene->addWidget(gameWinMenu.mainMenuButton);
        gameWinMenu.mainMenuButtonProxy->setZValue(1501);
        connect(gameWinMenu.mainMenuButton, &QPushButton::clicked, this, &UiManager::showMainMenu);
    }

    if (lvl_now != lvl_count) {
        if (gameWinMenu.nextLevelButton) {
            gameWinMenu.nextLevelButton->show();
        } else {
            gameWinMenu.nextLevelButton = createButton("Следующий уровень", QPoint(scene->width() / 2 - 100, scene->height() / 2 + 50));
            gameWinMenu.nextLevelButtonProxy = scene->addWidget(gameWinMenu.nextLevelButton);
            gameWinMenu.nextLevelButtonProxy->setZValue(1501);
            connect(gameWinMenu.nextLevelButton, &QPushButton::clicked, this, &UiManager::nextLevel);
        }
    }
}


void UiManager::showGameLoseMenu() {
    if (gameLoseMenu.resultBox) {
        gameLoseMenu.resultBox->show();
    } else {
        gameLoseMenu.resultBox = new QGraphicsRectItem(scene->width() / 2 - 150, scene->height() / 2 - 100, 300, 200);
        gameLoseMenu.resultBox->setBrush(QBrush(Qt::white));
        gameLoseMenu.resultBox->setZValue(1500);
        scene->addItem(gameLoseMenu.resultBox);
    }

    if (gameLoseMenu.restartButton){
        gameLoseMenu.restartButton->show();
    } else {
        gameLoseMenu.restartButton = createButton("Начать сначала", QPoint(scene->width() / 2 - 100, scene->height() / 2 - 50));
        gameLoseMenu.restartButtonProxy = scene->addWidget(gameLoseMenu.restartButton);
        gameLoseMenu.restartButtonProxy->setZValue(1501);
        connect(gameLoseMenu.restartButton, &QPushButton::clicked, this, &UiManager::restartGame);
    }

    if (gameLoseMenu.mainMenuButton){
        gameLoseMenu.mainMenuButton->show();
    } else {
        gameLoseMenu.mainMenuButton = createButton("Выйти в главное меню", QPoint(scene->width() / 2 - 100, scene->height() / 2 + 10));
        gameLoseMenu.mainMenuButtonProxy = scene->addWidget(gameLoseMenu.mainMenuButton);
        gameLoseMenu.mainMenuButtonProxy->setZValue(1501);
        connect(gameLoseMenu.mainMenuButton, &QPushButton::clicked, this, &UiManager::showMainMenu);
    }
}

void UiManager::showLevel() {
    if (levelElements.pauseButton) {
        levelElements.pauseButton->show();
    } else {
        levelElements.pauseButton = createButton("| |", QPoint(10, 10), QSize(50, 50));
        scene->addWidget(levelElements.pauseButton);
        connect(levelElements.pauseButton, &QPushButton::clicked, this, &UiManager::pauseGame);
    }

    if (levelElements.timer) {
        levelElements.timer->reset();
        levelElements.timer->show();
    } else {
        levelElements.timer = new Timer(scene, QPoint(70, 8));
        levelElements.timer->setZValue(500);
    }

    if (!levelElements.player) {
        levelElements.player = new Player(scene, QPoint(35, scene->height() - 100), QSize(50, 50), ":/img/man.png");
        levelElements.player->setCoins(0);
        levelElements.player->setFlag(QGraphicsItem::ItemIsFocusable);
        levelElements.player->setFocus();
        levelElements.player->setZValue(500);
        scene->addItem(levelElements.player);

        connect(levelElements.player, &Player::takenCoin, soundManager, &SoundManager::setSoundCoin);
        connect(levelElements.player, &Player::takenShot, soundManager, &SoundManager::setSoundShot);
        connect(levelElements.player, &Player::heroDied, this, &UiManager::gameOver);
    }

    if (levelElements.victoryZone) {
        levelElements.victoryZone->show();
    } else {
        levelElements.victoryZone = TextureFactory::create("invisible", QPoint(scene->width() - 72, 6), QSize(64, 64), ":/img/invisible_finish_icon.png");
        levelElements.victoryZone->setZValue(500);
        scene->addItem(levelElements.victoryZone);
    }

    if (levelElements.closeFinish) {
        levelElements.closeFinish->show();
    } else {
        levelElements.closeFinish = TextureFactory::create("regular", QPoint(1180, 0), QSize(20, 76), ":/img/close_finish.png");
        levelElements.closeFinish->setZValue(500);
        scene->addItem(levelElements.closeFinish);
    }

    if (levelElements.textures.empty()) {
        levelElements.textures.push_back(TextureFactory::create("regular", QPoint(scene->width() - 100, 76), QSize(100, 20), ":/img/platform_finish100x20.png"));
        levelElements.textures.push_back(TextureFactory::create("regular", QPoint(0, scene->height() - 50), QSize(120, 50), ":/img/platform_start120x50.png"));
        for (ITexture* texture : levelElements.textures) {
            texture->setZValue(500);
            scene->addItem(texture);
        }
    }

    startVictoryCheck();

    levelSettings->loadLevel(lvl_now, scene, levelElements.player);
}

void UiManager::hideLevel() {
    if (victoryCheckTimer) {
        victoryCheckTimer->stop();
    }
    if (levelElements.timer) {
        levelElements.timer->stop();
        levelElements.timer->hide();
    }
    if (animationTimer) animationTimer->stop();
    if (levelElements.pauseButton) levelElements.pauseButton->hide();
    for (ITexture* texture : levelElements.textures) {
        if (texture) {
            delete texture;
            texture = nullptr;
        }
    }
    levelElements.textures.resize(0);
    levelSettings->deleteUi(lvl_now);
    if (levelElements.victoryZone) levelElements.victoryZone->hide();
    if (levelElements.closeFinish) levelElements.closeFinish->hide();
    if (levelElements.player) {
        disconnect(levelElements.player, &Player::takenCoin, soundManager, &SoundManager::setSoundCoin);
        disconnect(levelElements.player, &Player::takenShot, soundManager, &SoundManager::setSoundShot);
        disconnect(levelElements.player, &Player::heroDied, this, &UiManager::gameOver);
        delete levelElements.player;
        levelElements.player = nullptr;
    };
}

void UiManager::setPause() {
    if (in_game && !in_pause) {
        in_game = false;
        in_pause = true;
    }
}

void UiManager::setUnpause() {
    if (in_pause) {
        in_pause = false;
    }
}

void UiManager::hideGameLoseMenu() {
    if (gameLoseMenu.resultBox) gameLoseMenu.resultBox->hide();
    if (gameLoseMenu.restartButton) gameLoseMenu.restartButton->hide();
    if (gameLoseMenu.mainMenuButton) gameLoseMenu.mainMenuButton->hide();
}

void UiManager::hideOverlay() {
    if (overlay) overlay->hide();
}

void UiManager::hidePauseMenu() {
    if (pauseMenu.resultBox) pauseMenu.resultBox->hide();
    if (pauseMenu.resumeButton) pauseMenu.resumeButton->hide();
    if (pauseMenu.mainMenuButton) pauseMenu.mainMenuButton->hide();
}

void UiManager::hideLevelButtons() {
    if (levelButtons.exitButton) levelButtons.exitButton->hide();
    for (auto& pair : levelButtons.buttonsAndTimes) {
        if (pair.first) pair.first->hide();
        if (pair.second) pair.second->hide();
    }
}

void UiManager::hideGameWinMenu() {
    if (gameWinMenu.resultText) gameWinMenu.resultText->hide();
    if (gameWinMenu.timeText) gameWinMenu.timeText->hide();
    if (gameWinMenu.replayButton) gameWinMenu.replayButton->hide();
    if (gameWinMenu.mainMenuButton) gameWinMenu.mainMenuButton->hide();
    if (gameWinMenu.nextLevelButton) gameWinMenu.nextLevelButton->hide();
    if (gameWinMenu.resultBox) gameWinMenu.resultBox->hide();
}

void UiManager::gameOver() {
    if (!in_game) return;
    levelSettings->pauseEnemySpawning(lvl_now);
    levelElements.timer->stop();
    animationTimer->stop();
    levelElements.player->clearFocus();
    soundManager->setSound("game_over");

    in_game = false;
    in_pause = true;

    showOverlay();
    showGameLoseMenu();
}

void UiManager::clearUI() {
    hideLevelButtons();
    hideLevel();
    hideGameWinMenu();
    hideGameLoseMenu();
    hidePauseMenu();
    hideOverlay();
}

