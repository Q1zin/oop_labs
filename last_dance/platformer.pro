# platformer.pro
QT       += core gui widgets multimedia

TARGET = Platformer
TEMPLATE = app

DEFINES += QT_DEPRECATED_WARNINGS

HEADERS += \
    include/mainwindow.h \
    include/screens/mainmenu.h \
    include/screens/gamescreen.h \
    include/levels/level.h \
    include/levels/levelssettings.h \
    include/levels/firstlevel.h \
    include/levels/secondlevel.h \
    include/levels/thirdlevel.h \
    include/managers/scoremanager.h \
    include/managers/soundmanager.h \
    include/managers/universalfactory.h \
    include/textures/coinstexture.h \
    include/textures/invisibletexture.h \
    include/textures/itexture.h \
    include/textures/texture.h \
    include/registertextures.h \
    include/utils/timer.h \ 
    include/utils/rainbowlabel.h \
    include/structs/datatexture.h \
    include/structs/dataenemy.h \
    include/entities/controller/entitycontroller.h \
    include/entities/controller/enemycontroller.h \
    include/entities/controller/playercontroller.h \
    include/entities/model/enemymodel.h \
    include/entities/model/entitymodel.h \
    include/entities/model/playermodel.h \
    include/entities/view/enemyview.h \
    include/entities/view/entityview.h \
    include/entities/view/playerview.h \
    include/managers/gamestate.h \
    include/managers/statemanager.h \
    include/structs/gamestates.h \
    include/entities/bullet.h

SOURCES += \
    src/main.cpp \
    src/mainwindow.cpp \
    src/screens/mainmenu.cpp \
    src/screens/gamescreen.cpp \
    src/levels/level.cpp \
    src/levels/levelssettings.cpp \
    src/levels/firstlevel.cpp \
    src/levels/secondlevel.cpp \
    src/levels/thirdlevel.cpp \
    src/managers/scoremanager.cpp \
    src/managers/soundmanager.cpp \
    src/textures/itexture.cpp \
    src/textures/coinstexture.cpp \
    src/textures/invisibletexture.cpp \
    src/textures/texture.cpp \
    src/registertextures.cpp \
    src/utils/rainbowlabel.cpp \
    src/utils/timer.cpp \
    src/entities/controller/entitycontroller.cpp \
    src/entities/controller/enemycontroller.cpp \
    src/entities/controller/playercontroller.cpp \
    src/entities/model/enemymodel.cpp \
    src/entities/model/entitymodel.cpp \
    src/entities/model/playermodel.cpp \
    src/entities/view/enemyview.cpp \
    src/entities/view/entityview.cpp \
    src/entities/view/playerview.cpp \
    src/managers/gamestate.cpp \
    src/managers/statemanager.cpp \
    src/entities/bullet.cpp

FORMS += \
    mainwindow.ui \
    mainmenu.ui

RESOURCES += \
    assets/img/image.qrc \
    assets/music/music.qrc

# Настройки компилятора
CONFIG += c++11
# QMAKE_CXXFLAGS += -Wall -Wextra -Werror

# Оптимизация
win32: QMAKE_CXXFLAGS_RELEASE += -O2 -s
unix: QMAKE_CXXFLAGS_RELEASE += -O3
