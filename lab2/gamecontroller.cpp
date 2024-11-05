#include "gamecontroller.h"

GameController::GameController(QWidget *parent)
    : QWidget{parent} {
}

void GameController::keyPressEvent(QKeyEvent* event) {
    switch (event->key()) {
    case Qt::Key_Left:
        emit keyLeftPress();
        break;
    case Qt::Key_Right:
        emit keyRightPress();
        break;
    case Qt::Key_Up:
        emit keyTopPress();
        break;
    case Qt::Key_Space:
        emit keySpacePress();
        break;
    case Qt::Key_Escape:
        emit keyEscapePress();
        break;
    }
}

void GameController::keyReleaseEvent(QKeyEvent *event) {
    if (event->key() == Qt::Key_Left) {
        emit keyLeftRelease();
    } else if (event->key() == Qt::Key_Right) {
        emit keyRightRelease();
    }
}
