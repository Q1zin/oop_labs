#include <QKeyEvent>
#include <QGraphicsScene>
#include <QPixmap>
#include <QPen>
#include <QApplication>
#include <QScreen>

#include "include/game.h"
#include "ui_game.h"
#include "include/managers/uimanager.h"

#define WINDOW_WIDTH 1280
#define WINDOW_HEIGHT 720

Game::Game(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Game)
{
    ui->setupUi(this);
    this->setFixedSize(WINDOW_WIDTH, WINDOW_HEIGHT);

    QScreen *screen = QGuiApplication::primaryScreen();
    QRect screenGeometry = screen->geometry();
    int x = (screenGeometry.width() - this->width()) / 2;
    this->move(x, 0);

    ui->graphicsView->setGeometry(0, 0, this->width(), this->height());

    QGraphicsScene* scene = new QGraphicsScene(this);
    ui->graphicsView->setScene(scene);
    scene->setSceneRect(0, 0, ui->graphicsView->width(), ui->graphicsView->height());

    ui->graphicsView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->graphicsView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    scene->setBackgroundBrush(QBrush("#ADE8FF"));

    gameUi = new UiManager(scene, new SoundManager);
    connect(gameUi, &UiManager::startGame, this, &Game::startGame);
    connect(gameUi, &UiManager::exitGame, this, &Game::exitGame);
}

Game::~Game()
{
    delete ui;
    delete gameUi;
}

void Game::startGame() {
    gameUi->showGameUI(1);
}

void Game::keyPressEvent(QKeyEvent *event)
{
    if (event->key() == Qt::Key_Escape) {
        gameUi->pauseGame();
        event->accept();
    } else {
        QWidget::keyPressEvent(event);
    }
}

void Game::exitGame() {
    QApplication::quit();
}
