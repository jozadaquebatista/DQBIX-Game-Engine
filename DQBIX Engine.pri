HEADERS += ./include/AnimatedSprite.h \
    ./include/audio.h \
    ./include/audio_backend.h \
    ./include/collisiondetection.h \
    ./include/color.h \
    ./include/Dummies.h \
    ./include/GameWindow.h \
    ./include/graphics.h \
    ./include/Helpers.hpp \
    ./include/imageResource.h \
    ./include/Input.h \
    ./include/light.h \
    ./include/lua.hpp \
    ./include/LuaEngine.hpp \
    ./include/Material.h \
    ./include/mesh.h \
    ./include/Node.h \
    ./include/occluder.h \
    ./include/point.hpp \
    ./include/RenderUtil.h \
    ./include/SceneTree.h \
    ./include/Script.h \
    ./include/sdl_backend.h \
    ./include/shader.h \
    ./include/shaders.h \
    ./include/Sprite.h \
    ./include/stb_image.h \
    ./include/Stopwatch.h \
    ./include/Text.h \
    ./include/Texture.h \
    ./include/Time.h \
    ./include/Transform.h \
    ./include/vertex.h \
    $$PWD/include/control.h \
    $$PWD/include/component.h \
    $$PWD/include/assetpackage.h \
    $$PWD/include/imageloader.h \
    $$PWD/include/font.h \
    $$PWD/include/shaderresource.h \
    $$PWD/include/tilemap.h \
    $$PWD/include/image_io.h
SOURCES += ./src/AnimatedSprite.cpp \
    ./src/audio.cpp \
    ./src/collisiondetection.cpp \
    ./src/color.cpp \
    ./src/Dummies.cpp \
    ./src/GameWindow.cpp \
    ./src/Helpers.cpp \
    ./src/imageResource.cpp \
    ./src/Input.cpp \
    ./src/light.cpp \
    ./src/LuaEngine.cpp \
    ./src/main.cpp \
    ./src/Material.cpp \
    ./src/mesh.cpp \
    ./src/Node.cpp \
    ./src/occluder.cpp \
    ./src/RenderUtil.cpp \
    ./src/SceneTree.cpp \
    ./src/Script.cpp \
    ./src/shader.cpp \
    ./src/Sprite.cpp \
    ./src/Stopwatch.cpp \
    ./src/Text.cpp \
    ./src/Texture.cpp \
    ./src/Time.cpp \
    ./src/Transform.cpp \
    ./src/vertex.cpp \
    $$PWD/src/component.cpp \
    $$PWD/src/assetpackage.cpp \
    $$PWD/src/imageloader.cpp \
    $$PWD/src/font.cpp \
    $$PWD/src/shaderresource.cpp \
    $$PWD/src/tilemap.cpp

DISTFILES += \
    $$PWD/res/dfont.ttf
