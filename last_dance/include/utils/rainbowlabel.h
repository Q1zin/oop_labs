#ifndef RAINBOWLABEL_H
#define RAINBOWLABEL_H

#include <QWidget>
#include <QLabel>
#include <QTimer>
#include <QVector>
#include <QColor>
#include <QHBoxLayout>

class RainbowLabel : public QWidget {
    Q_OBJECT
public:
    explicit RainbowLabel(QWidget *parent = nullptr);

private slots:
    void updateColors();

private:
    QLabel *title;
    QTimer *timer;
    QVector<QColor> rainbowColors;
};

#endif // RAINBOWLABEL_H
