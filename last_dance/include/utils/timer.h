#ifndef TIMER_H
#define TIMER_H

#include <QGraphicsTextItem>
#include <QTimer>
#include <QTime>

class Timer : public QGraphicsTextItem {
    Q_OBJECT

public:
    Timer(QGraphicsScene* scene, const QPoint& position);
    ~Timer();

    QTime getTime();
    void stop();
    void reset();
    void resume();

private slots:
    void updateTime();

private:
    void updateText();

    QGraphicsScene* scene;
    QTimer* timer;
    QTime elapsedTime;
};

#endif // TIMER_H
