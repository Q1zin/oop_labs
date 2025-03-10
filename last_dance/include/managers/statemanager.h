#ifndef STATEMANAGER_H
#define STATEMANAGER_H

#include <QObject>
#include "include/structs/gamestates.h"

class StateManager : public QObject {
    Q_OBJECT

public:
    explicit StateManager(QObject* parent = nullptr);

    void changeState(GameStates newState);
    GameStates getCurrentState() const;
    int getCurrentLevel() const;

signals:
    void stateChanged(GameStates newState);
    void levelStarted(int level);

private:
    GameStates currentState;
    int currentLevel;
};

#endif // STATEMANAGER_H
