
TEMPLATE = app
TARGET = DQBIXEngine
DESTDIR = $$PWD/debug
CONFIG -= qt
CONFIG += c++11
DEFINES -= UNICODE QT_LARGEFILE_SUPPORT
DEFINES += _WINDOWS

INCLUDEPATH += $$PWD/depends/bass/src \
    $$PWD/depends/glm \
    $$PWD/depends/libdrawtext/src \
    $$PWD/depends/LuaBridge \
    $$PWD/depends/PhysFS \
    $$PWD/depends

unix:!macx: LIBS += -lpthread
LIBS += -L$$PWD/depends/libdrawtext/ -ldrawtext
unix:!maxx: LIBS += -lGL -lGLU -lGLEW -lSDL -llua5.2 -lfreetype -lSOIL -lX11 -lm
win32: LIBS += -lglu32 \
    -lopengl32 \
    -lgdi32 \
    -luser32 \
    -lshell32 \
    -ladvapi32
LIBS += -L$$PWD/depends/PhysFS/lib -lphysfs
LIBS += -L$$PWD/depends/bass -lbass -lbass_fx

DEPENDPATH += $$PWD/depends
MOC_DIR += $$PWD/GeneratedFiles/debug
OBJECTS_DIR += debug
UI_DIR += $$PWD/GeneratedFiles
RCC_DIR += $$PWD/GeneratedFiles
include(DQBIX Engine.pri)
