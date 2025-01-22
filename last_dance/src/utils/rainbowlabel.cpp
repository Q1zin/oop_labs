#include "include/utils/rainbowlabel.h"
#include <QWidget>
#include <QLabel>
#include <QTimer>
#include <QVector>
#include <QColor>
#include <QHBoxLayout>

RainbowLabel::RainbowLabel(QWidget *parent) : QWidget(parent) {
    title = new QLabel(this);
    title->setText("Last Dance!");
    title->setFont(QFont("Montserrat", 100));
    title->setAlignment(Qt::AlignCenter);

    QHBoxLayout *layout = new QHBoxLayout(this);
    layout->addWidget(title);
    setLayout(layout);

    rainbowColors = {
        QColor(255, 0, 0),
        QColor(255, 165, 0),
        QColor(255, 255, 0),
        QColor(0, 128, 0),
        QColor(0, 0, 255),
        QColor(75, 0, 130),
        QColor(238, 130, 238)
    };

    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &RainbowLabel::updateColors);
    timer->start(300);
    updateColors();
}

void RainbowLabel::updateColors() {
    rainbowColors.append(rainbowColors.takeFirst());

    QString coloredText;
    QString plainText = "Last Dance!";
    for (int i = 0; i < plainText.length(); ++i) {
        QColor color = rainbowColors.at(i % rainbowColors.size());
        coloredText += QString("<span style='color:%1;'>%2</span>").arg(color.name()).arg(plainText.at(i));
    }

    title->setText(coloredText);
}
