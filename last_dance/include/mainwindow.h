#include <QMainWindow>
#include <QStackedWidget>
#include "include/managers/soundmanager.h"
#include "include/managers/gamestate.h"
#include "include/managers/statemanager.h"
#include "include/screens/mainmenu.h"
#include "include/screens/gamescreen.h"

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow() = default;

private:
    std::unique_ptr<SoundManager> soundManager;
    std::unique_ptr<GameState> gameState;
    std::unique_ptr<StateManager> stateManager;
    std::unique_ptr<MainMenu> mainMenu;
    std::unique_ptr<GameScreen> gameScreen;
    QStackedWidget* stackedWidget;
};
