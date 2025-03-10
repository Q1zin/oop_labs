#ifndef REGISTERTEXTURES_H
#define REGISTERTEXTURES_H

#include "include/managers/universalfactory.h"
#include "include/textures/itexture.h"
#include "include/structs/datatexture.h"
#include "include/entities/controller/enemycontroller.h"
#include "include/structs/dataenemy.h"

void registerTextures(UniversalFactory<ITexture, QString, dataTexture>& factory);

void registerEnemies(UniversalFactory<EnemyController, EnemyType, dataEnemy>& factory);

#endif // REGISTERTEXTURES_H
