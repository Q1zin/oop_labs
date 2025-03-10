#include "include/screens/mainmenu.h"
#include "include/utils/rainbowlabel.h"
#include <QLabel>
#include <QApplication>
#include <QVBoxLayout>
#include <QTime>

MainMenu::MainMenu(GameState* gameState, StateManager* stateManager, SoundManager* soundManager, QWidget* parent)
    : QWidget(parent), gameState(gameState), stateManager(stateManager), soundManager(soundManager)
{
    soundManager->playSound(SoundManager::SoundType::Menu);

    QVBoxLayout* layout = new QVBoxLayout(this);
    RainbowLabel* title = new RainbowLabel(this);
    layout->addWidget(title);

    createLevelButtons();

    menuButtons.exitButton = new QPushButton("Exit", this);
    connect(menuButtons.exitButton, &QPushButton::clicked, qApp, &QApplication::quit);
    layout->addWidget(menuButtons.exitButton);
}

void MainMenu::createLevelButtons() {
    int lvl_count = gameState->getLevelCount();
    for (int i = 1; i <= lvl_count; ++i) {
        int best_time = gameState->getBestTime(i);
        QString buttonText = QString("Level %1\n").arg(i);

        if (best_time > 0) {
            buttonText += "Ваше лучшее время: " + QTime::fromMSecsSinceStartOfDay(best_time * 1000).toString("mm:ss");
        } else {
            buttonText += "Вы ещё не играли, дак погнали!";
        }

        QPushButton* levelBtn = new QPushButton(buttonText, this);
        connect(levelBtn, &QPushButton::clicked, this, [this, i]() {
            emit levelSelected(i);
        });

        layout()->addWidget(levelBtn);
        menuButtons.buttonsLevel.append(levelBtn);
    }
}

void MainMenu::updateTime() {
    for (int i = 0; i < menuButtons.buttonsLevel.size(); ++i) {
        int level = i + 1;
        int best_time = gameState->getBestTime(level);
        QString buttonText = QString("Level %1\n").arg(level);

        if (best_time > 0) {
            buttonText += "Ваше лучшее время: " + QTime::fromMSecsSinceStartOfDay(best_time * 1000).toString("mm:ss");
        } else {
            buttonText += "Вы ещё не играли, дак погнали!";
        }

        menuButtons.buttonsLevel[i]->setText(buttonText);
    }
}
