
TEMPLATE = app
TARGET = DQBIX Engine
DESTDIR = $$PWD/debug
CONFIG += debug
CONFIG -= qt
CONFIG -= windows
CONFIG += console
CONFIG += c++11
DEFINES -= UNICODE QT_LARGEFILE_SUPPORT
DEFINES += _WINDOWS

INCLUDEPATH += $$PWD/depends/bass/src \
    $$PWD/depends/freeglut/include \
    $$PWD/depends/glew/include \
    $$PWD/depends/glm \
    $$PWD/depends/libdrawtext/include \
    $$PWD/depends/Lua52/include \
    $$PWD/depends/LuaBridge \
    $$PWD/depends/SDL12/include \
    $$PWD/depends

LIBS += -lglu32 \
    -lopengl32 \
    -lgdi32 \
    -luser32 \
    -lshell32

DEPENDPATH += $$PWD/depends
MOC_DIR += $$PWD/GeneratedFiles/debug
OBJECTS_DIR += debug
UI_DIR += $$PWD/GeneratedFiles
RCC_DIR += $$PWD/GeneratedFiles
include(DQBIX Engine.pri)

LIBS += -L$$PWD/depends/bass/src/ -lbass
LIBS += -L$$PWD/depends/bass/src/ -lbass_fx
LIBS += -L$$PWD/depends/freeglut/lib/ -lfreeglut
LIBS += -L$$PWD/depends/libdrawtext/lib/ -llibdrawtext
LIBS += -L$$PWD/depends/glew/lib/ -lglew32s
LIBS += -L$$PWD/depends/Lua52/ -llua52
LIBS += -L$$PWD/depends/SDL12/lib/ -lSDL -lSDLmain

PRE_TARGETDEPS += $$PWD/depends/freeglut/lib/freeglut.lib
PRE_TARGETDEPS += $$PWD/depends/glew/lib/glew32s.lib
PRE_TARGETDEPS += $$PWD/depends/libdrawtext/lib/libdrawtext.lib

DISTFILES +=
