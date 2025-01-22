#include "include/screens/gamescreen.h"
#include "include/registertextures.h"
#include "include/textures/itexture.h"
#include "include/utils/timer.h"
#include "include/structs/datatexture.h"
#include "include/entities/controller/playercontroller.h"
#include "include/entities/model/playermodel.h"
#include "include/entities/view/playerview.h"
#include "include/managers/statemanager.h"
#include "include/structs/gamestates.h"
#include "include/entities/bullet.h"
#include <QPushButton>
#include <QGraphicsRectItem>
#include <QTimer>

GameScreen::GameScreen(GameState* gameState, StateManager* stateManager, SoundManager *soundManager, QWidget *parent)
    : QWidget(parent), gameState(gameState), stateManager(stateManager), soundManager(soundManager) {
    scene = new QGraphicsScene(this);

    view = new QGraphicsView(scene, this);
    view->setGeometry(0, 0, 1280, 720);
    view->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    view->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    registerTextures(textureFactory);
    registerEnemies(enemyFactory);

    initStartLevelElements();
    initPlayer();
    initOverlay();
    initPauseMenu();
    initGameWinMenu();
    initGameLoseMenu();

    startGameLoop();
}

GameScreen::~GameScreen() {
    delete playerModel;
    delete playerView;
    delete playerController;
}

void GameScreen::loadLevel(int lvl) {
    gameState->setLevel(lvl);
    stateManager->changeState(GameStates::Playing);
    soundManager->playSound(SoundManager::SoundType::Game);

    loadTextures(lvl);
    levelElements.timer->reset();

    playerModel->setPosition(QPointF(35, 720 - 100));

    hidePauseMenu();
    hideGameWinMenu();
    hideGameLoseMenu();
}

void GameScreen::startGameLoop() {
    QTimer* gameTimer = new QTimer(this);
    connect(gameTimer, &QTimer::timeout, this, &GameScreen::gameLoop);
    gameTimer->start(16); // ~60 FPS
}

void GameScreen::gameLoop() {
    if (stateManager->getCurrentState() != GameStates::Playing) return;
    scene->advance();
    playerController->update();
    for (const auto& enemyController : listEnemyController) {
        enemyController->update(playerController->getPosition());
    }
}

void GameScreen::loadTextures(int lvl) {
    clearTextures();
    clearEnemy();

    levelElements.closeFinish.get()->show();

    std::vector<std::pair<QString, dataTexture>> textures = gameState->getTexturesLevel(lvl);
    for (auto& pair : textures) {
        std::unique_ptr<ITexture> item(textureFactory.Create(pair.first, pair.second));
        item->setZValue(500);
        scene->addItem(item.get());
        levelElements.textures.push_back(std::move(item));
    }


    std::vector<std::pair<EnemyType, dataEnemy>> enemys = gameState->getEnemysLevel(lvl);
    for (auto& pair : enemys) {
        std::unique_ptr<EnemyController> enemyController(enemyFactory.Create(pair.first, pair.second));
        scene->addItem(enemyController->getView());

        listEnemyController.push_back(std::move(enemyController));
    }
}

void GameScreen::clearTextures() {
    for (const auto& texture : levelElements.textures) {
        scene->removeItem(texture.get());
    }

    levelElements.textures.clear();
}

void GameScreen::clearEnemy() {
    for (const auto& enemy : listEnemyController) {
        scene->removeItem(enemy.get()->getView());
    }

    listEnemyController.clear();
}

QPushButton* GameScreen::createButton(const QString& text, const QPoint& pos, const QSize& size) {
    QPushButton* button = new QPushButton(text);
    button->setFixedSize(size);
    button->move(pos);
    return button;
}

QGraphicsTextItem* GameScreen::createText(const QString &text, const QPoint &position, const int size) {
    QGraphicsTextItem* resultText = new QGraphicsTextItem(text);
    resultText->setDefaultTextColor(Qt::black);
    resultText->setFont(QFont("Montserrat", size));
    resultText->setPos(position.x(), position.y());
    scene->addItem(resultText);
    return resultText;
}

void GameScreen::initPauseMenu() {
    pauseMenu.resultBox.reset(new QGraphicsRectItem(1280 / 2 - 150, 720 / 2 - 100, 300, 200));
    pauseMenu.resultBox->setBrush(QBrush(Qt::white));
    pauseMenu.resultBox->setZValue(1500);
    scene->addItem(pauseMenu.resultBox.get());

    pauseMenu.resumeButton.reset(createButton("Вернуться к игре", QPoint(1280 / 2 - 100, 720 / 2 - 50)));
    pauseMenu.resumeButtonProxy.reset(scene->addWidget(pauseMenu.resumeButton.get()));
    pauseMenu.resumeButtonProxy->setZValue(1501);
    connect(pauseMenu.resumeButton.get(), &QPushButton::clicked, this, &GameScreen::hidePauseMenu);

    pauseMenu.mainMenuButton.reset(createButton("Выйти в главное меню", QPoint(1280 / 2 - 100, 720 / 2 + 10)));
    pauseMenu.mainMenuButtonProxy.reset(scene->addWidget(pauseMenu.mainMenuButton.get()));
    pauseMenu.mainMenuButtonProxy->setZValue(1501);
    connect(pauseMenu.mainMenuButton.get(), &QPushButton::clicked, this, &GameScreen::returnToMenu);

    pauseMenu.resultBox->hide();
    pauseMenu.resumeButton->hide();
    pauseMenu.mainMenuButton->hide();
}

void GameScreen::initOverlay() {
    overlay.reset(new QGraphicsRectItem(0, 0, 1280, 720));
    overlay->setBrush(QBrush(QColor(0, 0, 0, 150)));
    overlay->setZValue(1000);
    overlay->setPen(Qt::NoPen);
    scene->addItem(overlay.get());

    overlay->hide();
}

void GameScreen::initStartLevelElements() {
    levelElements.pauseButton.reset(createButton("| |", {10,10}, {50, 50}));
    levelElements.pauseButtonProxy.reset(scene->addWidget(levelElements.pauseButton.get()));
    levelElements.pauseButtonProxy->setZValue(500);
    connect(levelElements.pauseButton.get(), &QPushButton::clicked, this, &GameScreen::showPauseMenu);

    levelElements.closeFinish.reset(textureFactory.Create("regular", {QPoint(1180, 0), QSize(20, 76), ":/image/close_finish.png"}));
    levelElements.closeFinish->setZValue(500);
    scene->addItem(levelElements.closeFinish.get());

    levelElements.startTextures.push_back(std::unique_ptr<ITexture>(
        textureFactory.Create("regular", {QPoint(1280 - 100, 76), QSize(100, 20), ":/image/platform_finish100x20.png"})));
    levelElements.startTextures.push_back(std::unique_ptr<ITexture>(
        textureFactory.Create("regular", {QPoint(0, 720 - 50), QSize(120, 50), ":/image/platform_start120x50.png"})));
    levelElements.startTextures.push_back(std::unique_ptr<ITexture>(
        textureFactory.Create("invisible", {QPoint(1280 - 72, 6), QSize(64, 64), ":/image/invisible_finish_icon.png"})));

    for (auto& texture : levelElements.startTextures) {
        texture->setZValue(500);
        scene->addItem(texture.get());
    }

    levelElements.timer.reset(new Timer(scene, {70, 8}));
    levelElements.timer->setZValue(500);
    levelElements.timer->stop();
}

void GameScreen::initPlayer() {
    playerView = new PlayerView(QPixmap(":/image/man.png"));
    playerView->setZValue(510);
    playerModel = new PlayerModel(QPointF(35, 720 - 100), this);
    playerController = new PlayerController(playerModel, playerView, this);

    scene->addItem(playerView);

    connect(gameState, &GameState::finishOpened, this, &GameScreen::openFinish);
    connect(playerController, &PlayerController::playerTakeCoin, this, &GameScreen::onPlayerTakeCoin);
    connect(playerController, &PlayerController::playerFinished, this, &GameScreen::onPlayerFinished);
    connect(playerController, &PlayerController::playerDie, this, &GameScreen::onPlayerDie);
    connect(playerController, &PlayerController::playerShoot, this, &GameScreen::shootBullet);
}

void GameScreen::initGameLoseMenu() {
    gameLoseMenu.resultBox.reset(new QGraphicsRectItem(1280 / 2 - 150, 720 / 2 - 100, 300, 200));
    gameLoseMenu.resultBox->setBrush(QBrush(Qt::white));
    gameLoseMenu.resultBox->setZValue(1500);
    scene->addItem(gameLoseMenu.resultBox.get());

    gameLoseMenu.resultText.reset(createText("Вы проиграли!", QPoint(1280 / 2 - 75, 720 / 2 - 80)));
    gameLoseMenu.resultText->setZValue(1501);

    gameLoseMenu.restartButton.reset(createButton("Попробовать снова", QPoint(1280 / 2 - 100, 720 / 2 - 40)));
    gameLoseMenu.restartButtonProxy.reset(scene->addWidget(gameLoseMenu.restartButton.get()));
    gameLoseMenu.restartButtonProxy->setZValue(1501);
    connect(gameLoseMenu.restartButton.get(), &QPushButton::clicked, this, [this]() {
        loadLevel(gameState->getLevel());
    });

    gameLoseMenu.mainMenuButton.reset(createButton("Главное меню", QPoint(1280 / 2 - 100, 720 / 2 + 20)));
    gameLoseMenu.mainMenuButtonProxy.reset(scene->addWidget(gameLoseMenu.mainMenuButton.get()));
    gameLoseMenu.mainMenuButtonProxy->setZValue(1501);
    connect(gameLoseMenu.mainMenuButton.get(), &QPushButton::clicked, this, &GameScreen::returnToMenu);

    hideGameLoseMenu();
}

void GameScreen::initGameWinMenu() {
    gameWinMenu.resultBox.reset(new QGraphicsRectItem(1280 / 2 - 150, 720 / 2 - 150, 300, 400));
    gameWinMenu.resultBox->setBrush(QBrush(Qt::white));
    gameWinMenu.resultBox->setZValue(1500);
    scene->addItem(gameWinMenu.resultBox.get());

    gameWinMenu.resultText.reset(createText("Вы победили!", QPoint(1280 / 2 - 75, 720 / 2 - 90)));
    gameWinMenu.resultText->setZValue(1501);

    gameWinMenu.timeText.reset(createText("Время: " + levelElements.timer->getTime().toString("mm:ss"), QPoint(scene->width() / 2 - 60, scene->height() / 2 - 56)));
    gameWinMenu.timeText->setZValue(1501);

    gameWinMenu.replayButton.reset(createButton("Ещё раз!", QPoint(1280 / 2 - 100, 720 / 2 - 10)));
    gameWinMenu.replayButtonProxy.reset(scene->addWidget(gameWinMenu.replayButton.get()));
    gameWinMenu.replayButtonProxy->setZValue(1501);
    connect(gameWinMenu.replayButton.get(), &QPushButton::clicked, this, [this]() {
        loadLevel(gameState->getLevel());
    });

    gameWinMenu.mainMenuButton.reset(createButton("Главное меню", QPoint(1280 / 2 - 100, 720 / 2 + 110)));
    gameWinMenu.mainMenuButtonProxy.reset(scene->addWidget(gameWinMenu.mainMenuButton.get()));
    gameWinMenu.mainMenuButtonProxy->setZValue(1501);
    connect(gameWinMenu.mainMenuButton.get(), &QPushButton::clicked, this, &GameScreen::returnToMenu);

    gameWinMenu.nextLevelButton.reset(createButton("Следующий уровень", QPoint(1280 / 2 - 100, 720 / 2 + 50)));
    gameWinMenu.nextLevelButtonProxy.reset(scene->addWidget(gameWinMenu.nextLevelButton.get()));
    gameWinMenu.nextLevelButtonProxy->setZValue(1501);
    connect(gameWinMenu.nextLevelButton.get(), &QPushButton::clicked, this, [this]() {
            loadLevel(gameState->getLevel() + 1);
    });

    hideGameWinMenu();
}

void GameScreen::onPlayerTakeCoin(QGraphicsItem* coin) {
    gameState->collectedСoin();
    soundManager->playSound(SoundManager::SoundType::CollectedCoin);

    scene->removeItem(coin);

    auto it = std::remove_if(levelElements.textures.begin(), levelElements.textures.end(),
                             [coin](const std::unique_ptr<ITexture>& texture) { return texture.get() == coin; }
    );

    if (it != levelElements.textures.end()) {
        levelElements.textures.erase(it, levelElements.textures.end());
    }
}

void GameScreen::openFinish() {
    levelElements.closeFinish.get()->hide();
}

void GameScreen::onPlayerFinished() {
    stateManager->changeState(GameStates::Win);
    gameState->updateBestTime(QTime(0, 0).secsTo(levelElements.timer->getTime()));
    levelElements.timer->stop();
    showOverlay();
    showGameWinMenu();
    soundManager->playSound(SoundManager::SoundType::Win);
}

void GameScreen::onPlayerDie() {
    stateManager->changeState(GameStates::Lose);
    levelElements.timer->stop();
    showOverlay();
    showGameLoseMenu();
    soundManager->playSound(SoundManager::SoundType::GameOver);
}

void GameScreen::showOverlay() {
    overlay->show();
}

void GameScreen::hideOverlay() {
    overlay->hide();
}

void GameScreen::showPauseMenu() {
    stateManager->changeState(GameStates::Paused);
    levelElements.timer->stop();
    showOverlay();
    pauseMenu.resultBox->show();
    pauseMenu.resumeButton->show();
    pauseMenu.mainMenuButton->show();
}

void GameScreen::hidePauseMenu() {
    stateManager->changeState(GameStates::Playing);
    levelElements.timer->resume();
    hideOverlay();
    pauseMenu.resultBox->hide();
    pauseMenu.resumeButton->hide();
    pauseMenu.mainMenuButton->hide();
}

void GameScreen::showGameWinMenu() {
    gameWinMenu.resultBox->show();
    gameWinMenu.resultText->show();
    gameWinMenu.timeText->setPlainText("Время: " + levelElements.timer->getTime().toString("mm:ss"));
    gameWinMenu.timeText->show();
    gameWinMenu.replayButton->show();
    gameWinMenu.mainMenuButton->show();
    if (gameState->getLevel() < gameState->getLevelCount())
        gameWinMenu.nextLevelButton->show();
}

void GameScreen::hideGameWinMenu() {
    gameWinMenu.resultBox->hide();
    gameWinMenu.resultText->hide();
    gameWinMenu.timeText->hide();
    gameWinMenu.replayButton->hide();
    gameWinMenu.mainMenuButton->hide();
    gameWinMenu.nextLevelButton->hide();
}

void GameScreen::showGameLoseMenu() {
    gameLoseMenu.resultBox->show();
    gameLoseMenu.resultText->show();
    gameLoseMenu.restartButton->show();
    gameLoseMenu.mainMenuButton->show();
}

void GameScreen::hideGameLoseMenu() {
    gameLoseMenu.resultBox->hide();
    gameLoseMenu.resultText->hide();
    gameLoseMenu.restartButton->hide();
    gameLoseMenu.mainMenuButton->hide();
}

void GameScreen::keyPressEvent(QKeyEvent *event) {
    if (playerController) playerController->handleKeyPress(event);
    event->accept();
}

void GameScreen::keyReleaseEvent(QKeyEvent *event) {
    if (playerController) playerController->handleKeyRelease(event);
}

void GameScreen::shootBullet() {
    int direction = playerModel->getDirection();
    QPointF bulletPos = playerModel->getPosition() + QPointF(25, 25);
    Bullet* bullet = new Bullet(bulletPos, direction);
    scene->addItem(bullet);
    soundManager->playSound(SoundManager::SoundType::Shot);

    connect(bullet, &Bullet::collided, this, &GameScreen::handleBulletCollision);
}

void GameScreen::handleBulletCollision(QGraphicsItem* item) {
    Bullet* bullet = qobject_cast<Bullet*>(sender());
    if (!bullet) return;

    scene->removeItem(bullet);
    delete bullet;

    if (item->type() == EnemyView::Type) {
        EnemyView* enemyView = dynamic_cast<EnemyView*>(item);
        for (auto& enemyController : listEnemyController) {
            if (enemyController->getView() == enemyView) {
                enemyController->takeDamage(1);
                if (!enemyController->isAlive()) {
                    scene->removeItem(enemyView);
                    listEnemyController.erase(std::remove_if(listEnemyController.begin(), listEnemyController.end(),
                                                             [&](const auto& item) { return item.get() == enemyController.get(); }), listEnemyController.end());
                }
                break;
            }
        }
    }
}
