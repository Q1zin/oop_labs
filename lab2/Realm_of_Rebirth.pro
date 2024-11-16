QT       += core gui multimedia

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    src/managers/enemyfactory.cpp \
    src/managers/gamecontroller.cpp \
    src/main.cpp \
    src/game.cpp \
    src/managers/uimanager.cpp \
    src/managers/soundmanager.cpp \
    src/managers/scoremanager.cpp \
    src/managers/texturefactory.cpp \
    src/textures/itexture.cpp \
    src/textures/coinstexture.cpp \
    src/textures/invisibletexture.cpp \
    src/textures/texture.cpp \
    src/entities/bullet.cpp \
    src/entities/enemy.cpp \
    src/entities/entity.cpp \
    src/entities/player.cpp \
    src/levels/firstlevel.cpp \
    src/levels/level.cpp \
    src/levels/levelssettings.cpp \
    src/levels/secondlevel.cpp \
    src/levels/thirdlevel.cpp \
    src/utils/timer.cpp


HEADERS += \
    include/managers/enemyfactory.h \
    include/managers/gamecontroller.h \
    include/game.h \
    include/managers/soundmanager.h \
    include/managers/uimanager.h \
    include/managers/texturefactory.h \
    include/managers/scoremanager.h \
    include/textures/coinstexture.h \
    include/textures/invisibletexture.h \
    include/textures/itexture.h \
    include/textures/texture.h \
    include/entities/enemy.h \
    include/entities/entity.h \
    include/entities/bullet.h \
    include/entities/player.h \
    include/levels/firstlevel.h \
    include/levels/level.h \
    include/levels/levelssettings.h \
    include/levels/secondlevel.h \
    include/levels/thirdlevel.h \
    include/utils/timer.h


FORMS += \
    game.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    assets/img/image.qrc \
    assets/music/music.qrc \
    save.qrc
