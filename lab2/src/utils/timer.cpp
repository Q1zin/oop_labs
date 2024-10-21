#include <QGraphicsScene>
#include <QTimer>
#include "include/utils/timer.h"

Timer::Timer(QGraphicsScene* scene, int x, int y)
    : QGraphicsTextItem(0), scene(scene), timer(new QTimer(this)), elapsedTime(0, 0) {
    connect(timer, &QTimer::timeout, this, &Timer::updateTime);

    timer->start(1000);
    setPos(x, y);
    setDefaultTextColor(Qt::black);
    setFont(QFont("Montserrat", 40));
    scene->addItem(this);
    updateText();
}

Timer::~Timer() {
    stop();
}

void Timer::stop()
{
    timer->stop();
}

void Timer::resume()
{
    timer->start(1000);
    updateText();
}

void Timer::reset()
{
    timer->stop();
    elapsedTime = QTime(0, 0);
    timer->start(1000);
    updateText();
}

QTime Timer::getTime()
{
    return elapsedTime;
}

void Timer::updateTime() {
    elapsedTime = elapsedTime.addSecs(1);
    updateText();
}

void Timer::updateText() {
    setPlainText(elapsedTime.toString("mm:ss"));
}
