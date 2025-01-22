#include "include/levels/level.h"

Level::Level() : bestTime(0) {}

int Level::getBestTime() const { return bestTime; }

void Level::setBestTime(int time) { bestTime = time; }
