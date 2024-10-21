#include "include/levels/level.h"

Level::Level() : bestTime(0) {}

QTimer *Level::getTimer() { return nullptr; }

int Level::getBestTime() const { return bestTime; }

void Level::setBestTime(int time) { bestTime = time; }
