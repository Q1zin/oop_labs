#include "include/mainwindow.h"
#include "include/screens/mainmenu.h"
#include "include/screens/gamescreen.h"
#include "include/managers/gamestate.h"
#include "include/managers/statemanager.h"
#include <memory>

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent) {
    soundManager = std::make_unique<SoundManager>();
    gameState = std::make_unique<GameState>();
    stateManager = std::make_unique<StateManager>();

    stackedWidget = new QStackedWidget(this);
    setCentralWidget(stackedWidget);

    mainMenu = std::make_unique<MainMenu>(gameState.get(), stateManager.get(), soundManager.get(), this);
    gameScreen = std::make_unique<GameScreen>(gameState.get(), stateManager.get(), soundManager.get(), this);

    stackedWidget->addWidget(mainMenu.get());
    stackedWidget->addWidget(gameScreen.get());

    connect(mainMenu.get(), &MainMenu::levelSelected, this, [this](int level) {
        soundManager->playSound(SoundManager::SoundType::Game);
        gameScreen->loadLevel(level);
        stackedWidget->setCurrentWidget(gameScreen.get());
    });

    connect(gameScreen.get(), &GameScreen::returnToMenu, this, [this]() {
        soundManager->playSound(SoundManager::SoundType::Menu);
        stackedWidget->setCurrentWidget(mainMenu.get());
        mainMenu->updateTime();
    });
}
