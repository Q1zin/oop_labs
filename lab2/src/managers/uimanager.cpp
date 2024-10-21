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
    animationTimer->start(1000 / 60);

    levelSettings = new LevelsSettings();
    lvl_count = levelSettings->getLevelsCount();

    showMainMenu();
}

UiManager::~UiManager()
{
    delete timer;
    if (victoryCheckTimer) {
        delete victoryCheckTimer;
    }
}

void UiManager::showMainMenu()
{
    clearUI();
    soundManager->setSound("menu");
    in_game = false;
    in_pause = false;

    QGraphicsTextItem* timeText;
    for (int i = 1; i <= lvl_count; i++) {
        int best_time = levelSettings->getBestTime(i);
        if (best_time) {
            timeText = new QGraphicsTextItem("Ваше лучшее время: " + QTime::fromMSecsSinceStartOfDay(best_time * 1000).toString("mm:ss"));
        } else {
            timeText = new QGraphicsTextItem("Вы ещё не играли, дак погнали!");
        }
        timeText->setDefaultTextColor(Qt::black);
        timeText->setFont(QFont("Montserrat", 16));
        timeText->setPos(520, 100 * i + 110);
        scene->addItem(timeText);

        QPushButton* startButtonLvl = createButton(300, 100 + i * 100, QString::number(i) + " LVL");
        connect(startButtonLvl, &QPushButton::clicked, this, [this, i]() { showGameUI(i); });
    }

    QPushButton* exitButton = createButton(300, 200 + lvl_count * 100, "Выйти");
    connect(exitButton, &QPushButton::clicked, this, &UiManager::exitGame);
}

void UiManager::showGameUI(int lvl)
{
    clearUI();
    animationTimer->start();
    soundManager->setSound("game");
    lvl_now = lvl;

    in_game = true;
    in_pause = false;

    QPushButton* pauseButton = createButton(10, 10, "| |", 50, 50);
    connect(pauseButton, &QPushButton::clicked, this, &UiManager::pauseGame);

    timer = new Timer(scene, 70, 8);

    player = new Player(scene, 35, scene->height() - 100, 50, 50, "/Users/mir/Realm_of_Rebirth/assets/img/man.png");
    player->setCoins(0);
    player->setFlag(QGraphicsItem::ItemIsFocusable);
    player->setFocus();
    scene->addItem(player);

    connect(player, &Player::takeCoin, soundManager, &SoundManager::setSoundCoin);
    connect(player, &Player::takeShot, soundManager, &SoundManager::setSoundShot);
    connect(player, &Player::heroDied, this, &UiManager::gameOver);

    ITexture* victoryZone = TextureFactory::create("invisible", 64, 64, scene->width() - 72, 6, "/Users/mir/Realm_of_Rebirth/assets/img/invisible_finish_icon.png");
    ITexture* closeFinish = TextureFactory::create("regular", 20, 76, 1180, 0, "/Users/mir/Realm_of_Rebirth/assets/img/close_finish.png");

    scene->addItem(TextureFactory::create("regular", 100, 20, scene->width() - 100, 76, "/Users/mir/Realm_of_Rebirth/assets/img/platform_finish100x20.png"));
    scene->addItem(TextureFactory::create("regular", 120, 50, 0, scene->height() - 50, "/Users/mir/Realm_of_Rebirth/assets/img/platform_start120x50.png"));
    scene->addItem(closeFinish);
    scene->addItem(victoryZone);

    startVictoryCheck(victoryZone, closeFinish);

    levelSettings->loadLevel(lvl_now, scene, player);
}

void UiManager::startVictoryCheck(ITexture* victoryZone, ITexture* closeFinish) {
    if (victoryCheckTimer) {
        delete victoryCheckTimer;
    }

    victoryCheckTimer = new QTimer(this);
    connect(victoryCheckTimer, &QTimer::timeout, [this, victoryZone, closeFinish]() {
        checkVictory(player, victoryZone, closeFinish);
    });

    victoryCheckTimer->start(100);
}

QPushButton *UiManager::createButton(int x, int y, const QString& text, int width, int height)
{
    QPushButton* button = new QPushButton(text);
    button->setFixedSize(width, height);
    button->move(x, y);
    scene->addWidget(button);
    return button;
}

void UiManager::checkVictory(Player* player, ITexture* victoryZone, ITexture* closeFinish) {
    if (player->getCoins() == 3) {
        delete closeFinish;
        player->setCoins(0);
    }
    if (player->collidesWithItem(victoryZone)) {
        if (victoryCheckTimer) {
            victoryCheckTimer->stop();
            delete victoryCheckTimer;
            victoryCheckTimer = nullptr;
        }

        if (timer) {
            timer->stop();
        }

        showGameWin();
    }
}

void UiManager::showGameWin() {
    levelSettings->pauseEnemySpawning(lvl_now);
    timer->stop();
    animationTimer->stop();
    soundManager->setSound("win");

    in_game = false;
    in_pause = true;

    QString elapsedTime = timer->getTime().toString("mm:ss");

    QGraphicsRectItem* overlay = new QGraphicsRectItem(0, 0, scene->width(), scene->height());
    overlay->setBrush(QBrush(QColor(0, 0, 0, 150)));
    scene->addItem(overlay);

    QGraphicsRectItem* resultBox = new QGraphicsRectItem(scene->width() / 2 - 150, scene->height() / 2 - 150, 300, 400);
    resultBox->setBrush(QBrush(Qt::white));
    scene->addItem(resultBox);

    QGraphicsTextItem* resultText = new QGraphicsTextItem("Вы победили!");
    resultText->setDefaultTextColor(Qt::black);
    resultText->setFont(QFont("Montserrat", 20));
    resultText->setPos(scene->width() / 2 - 75, scene->height() / 2 - 90);
    scene->addItem(resultText);

    QGraphicsTextItem* timeText = new QGraphicsTextItem("Время: " + elapsedTime);
    timeText->setDefaultTextColor(Qt::black);
    timeText->setFont(QFont("Montserrat", 16));
    timeText->setPos(scene->width() / 2 - 60, scene->height() / 2 - 56);
    scene->addItem(timeText);

    QPushButton* replayButton = createButton(scene->width() / 2 - 100, scene->height() / 2 + - 10, "Ещё раз!");
    QPushButton* mainMenuButton = createButton(scene->width() / 2 - 100, scene->height() / 2 + 110, "Главное меню");

    if (lvl_now != lvl_count) {
        QPushButton* nextLevelButton = createButton(scene->width() / 2 - 100, scene->height() / 2 + 50, "Следующий уровень");
        connect(nextLevelButton, &QPushButton::clicked, this, &UiManager::nextLevel);
    }

    connect(replayButton, &QPushButton::clicked, this, &UiManager::restartGame);
    connect(mainMenuButton, &QPushButton::clicked, this, &UiManager::showMainMenu);

    levelSettings->updateBestTime(lvl_now, QTime(0, 0).secsTo(timer->getTime()));
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

void UiManager::pauseGame()
{
    if (in_pause) return;

    levelSettings->pauseEnemySpawning(lvl_now);
    timer->stop();
    animationTimer->stop();

    in_game = false;
    in_pause = true;

    player->clearFocus();

    QGraphicsRectItem* pauseOverlay = new QGraphicsRectItem(0, 0, scene->width(), scene->height());
    pauseOverlay->setBrush(QBrush(QColor(0, 0, 0, 150)));
    scene->addItem(pauseOverlay);

    QGraphicsRectItem* resultBox = new QGraphicsRectItem(scene->width() / 2 - 150, scene->height() / 2 - 100, 300, 200);
    resultBox->setBrush(QBrush(Qt::white));
    scene->addItem(resultBox);

    QPushButton* resumeButton = createButton(scene->width() / 2 - 100, scene->height() / 2 - 50, "Вернуться к игре");
    QPushButton* mainMenuButton = createButton(scene->width() / 2 - 100, scene->height() / 2 + 10, "Выйти в главное меню");

    connect(resumeButton, &QPushButton::clicked, [this, pauseOverlay, resultBox, resumeButton, mainMenuButton]() {
        scene->removeItem(pauseOverlay);
        scene->removeItem(resultBox);
        resumeButton->hide();
        mainMenuButton->hide();
        in_game = true;
        in_pause = false;
        player->setFocus();
        animationTimer->start();
        timer->resume();
        levelSettings->resumeEnemySpawning(lvl_now);
    });

    connect(mainMenuButton, &QPushButton::clicked, [this, pauseOverlay, resultBox, resumeButton, mainMenuButton]() {
        scene->removeItem(pauseOverlay);
        scene->removeItem(resultBox);
        resumeButton->hide();
        mainMenuButton->hide();
        showMainMenu();
    });
}

void UiManager::gameOver()
{
    if (!in_game) return;
    levelSettings->pauseEnemySpawning(lvl_now);
    timer->stop();
    animationTimer->stop();
    player->clearFocus();
    soundManager->setSound("game_over");

    in_game = false;
    in_pause = true;

    QGraphicsRectItem* pauseOverlay = new QGraphicsRectItem(0, 0, scene->width(), scene->height());
    pauseOverlay->setBrush(QBrush(QColor(0, 0, 0, 150)));
    scene->addItem(pauseOverlay);

    QGraphicsRectItem* resultBox = new QGraphicsRectItem(scene->width() / 2 - 150, scene->height() / 2 - 100, 300, 200);
    resultBox->setBrush(QBrush(Qt::white));
    scene->addItem(resultBox);

    QPushButton* restartButton = createButton(scene->width() / 2 - 100, scene->height() / 2 - 50, "Начать сначала");
    QPushButton* mainMenuButton = createButton(scene->width() / 2 - 100, scene->height() / 2 + 10, "Выйти в главное меню");

    connect(restartButton, &QPushButton::clicked, [this, pauseOverlay, resultBox, restartButton, mainMenuButton]() {
        scene->removeItem(pauseOverlay);
        scene->removeItem(resultBox);
        restartButton->hide();
        mainMenuButton->hide();
        in_game = true;
        in_pause = false;
        player->setFocus();
        timer->reset();
        showGameUI(lvl_now);
    });

    connect(mainMenuButton, &QPushButton::clicked, [this, pauseOverlay, resultBox, restartButton, mainMenuButton]() {
        scene->removeItem(pauseOverlay);
        scene->removeItem(resultBox);
        restartButton->hide();
        mainMenuButton->hide();
        showMainMenu();
    });
}

void UiManager::clearUI()
{
    QList<QGraphicsItem*> items = scene->items();

    for (QGraphicsItem* item : items) {
        scene->removeItem(item);
        item->setVisible(false);
    }
}

