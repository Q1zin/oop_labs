#include "include/registertextures.h"
#include "include/managers/universalfactory.h"
#include "include/textures/itexture.h"
#include "include/textures/coinstexture.h"
#include "include/textures/invisibletexture.h"
#include "include/textures/texture.h"
#include "include/structs/datatexture.h"
#include "include/entities/controller/enemycontroller.h"
#include "include/entities/model/enemymodel.h"
#include "include/entities/view/enemyview.h"
#include "include/structs/dataenemy.h"

void registerTextures(UniversalFactory<ITexture, QString, dataTexture>& factory) {
    factory.Register("regular", [](const dataTexture& data) -> ITexture* {
        if (data.img.isEmpty()) {
            return new Texture(data.position, data.size);
        } else {
            return new Texture(data.position, data.size, data.img);
        }
    });

    factory.Register("invisible", [](const dataTexture& data) -> ITexture* {
        return new InvisibleTexture(data.position, data.size, data.img);
    });

    factory.Register("coin", [](const dataTexture& data) -> ITexture* {
        return new CoinsTexture(data.position);
    });
}

void registerEnemies(UniversalFactory<EnemyController, EnemyType, dataEnemy>& factory) {
    factory.Register(EASY, [](const dataEnemy& data) -> EnemyController* {
        EnemyModel* enemyModel = new EnemyModel(data.position);
        enemyModel->setHealth(5);
        EnemyView* enemyView = new EnemyView(QPixmap(":/image/enemy_type_1.png"));
        enemyView->setZValue(510);
        EnemyController* enemyController = new EnemyController(enemyModel, enemyView);

        return enemyController;
    });

    factory.Register(MEDIUM, [](const dataEnemy& data) -> EnemyController* {
        EnemyModel* enemyModel = new EnemyModel(data.position);
        enemyModel->setHealth(10);
        EnemyView* enemyView = new EnemyView(QPixmap(":/image/enemy_type_2.png"));
        enemyView->setZValue(510);
        EnemyController* enemyController = new EnemyController(enemyModel, enemyView);

        return enemyController;
    });

    factory.Register(HARD, [](const dataEnemy& data) -> EnemyController* {
        EnemyModel* enemyModel = new EnemyModel(data.position);
        enemyModel->setHealth(20);
        EnemyView* enemyView = new EnemyView(QPixmap(":/image/enemy_type_2.png"));
        enemyView->setZValue(510);
        EnemyController* enemyController = new EnemyController(enemyModel, enemyView);

        return enemyController;
    });
}
