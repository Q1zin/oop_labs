#ifndef MAINMENU_H
#define MAINMENU_H

#include <QWidget>
#include <QPushButton>
#include <QVBoxLayout>
#include "include/managers/soundmanager.h"
#include "include/managers/gamestate.h"
#include "include/managers/statemanager.h"

struct MenuButtons {
    QList<QPushButton*> buttonsLevel;
    QPushButton* exitButton = nullptr;
};

class MainMenu : public QWidget {
    Q_OBJECT
public:
    explicit MainMenu(GameState* gameState, StateManager* stateManager, SoundManager* soundManager, QWidget* parent = nullptr);
    ~MainMenu() = default;

    void updateTime();

signals:
    void levelSelected(int level);

private:
    GameState* gameState;
    StateManager* stateManager;
    SoundManager* soundManager;
    MenuButtons menuButtons;

    void createLevelButtons();
};

#endif // MAINMENU_H
