#ifndef GAMECONTROLLER_H
#define GAMECONTROLLER_H

#include <QWidget>
#include <QGraphicsScene>
#include <QKeyEvent>

class GameController : public QWidget
{
    Q_OBJECT
public:
    GameController(QWidget *parent = nullptr);

    void keyPressEvent(QKeyEvent* event) override;
    void keyReleaseEvent(QKeyEvent* event) override;

signals:
    void keyLeftPress();
    void keyRightPress();
    void keyTopPress();
    void keySpacePress();
    void keyEscapePress();
    void keyLeftRelease();
    void keyRightRelease();

protected:
};

#endif // GAMECONTROLLER_H
