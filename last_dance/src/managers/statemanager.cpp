#include "include/managers/statemanager.h"
#include <QDebug>
#include <QTimer>

StateManager::StateManager(QObject* parent)
    : QObject(parent), currentState(GameStates::MainMenu), currentLevel(1) {
}

void StateManager::changeState(GameStates newState) {
    if (currentState == newState) return;
    currentState = newState;
    emit stateChanged(newState);
}

GameStates StateManager::getCurrentState() const { return currentState; }

int StateManager::getCurrentLevel() const { return currentLevel; }
