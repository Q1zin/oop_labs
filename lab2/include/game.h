#ifndef GAME_H
#define GAME_H

#include <QWidget>
#include <QGraphicsScene>
#include <QKeyEvent>
#include "include/managers/uimanager.h"

QT_BEGIN_NAMESPACE
namespace Ui { class Game; }
QT_END_NAMESPACE

class Game : public QWidget
{
    Q_OBJECT

public:
    Game(QWidget *parent = nullptr);
    ~Game();

protected:
    void keyPressEvent(QKeyEvent *event);

private slots:
    void startGame();
    void exitGame();

private:
    Ui::Game* ui;
    QGraphicsScene* scene;
    UiManager* gameUi;
};

#endif // GAME_H
