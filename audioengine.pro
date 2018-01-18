TEMPLATE = app
CONFIG += c++14
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

LIBS += -lglfw3 -lGL -lGLEW -lm -lXrandr -lXi -lX11 -lXxf86vm -lpthread -lopenal

SOURCES += \
    al2/OpenALBackend.cpp \
    utils/Error.cpp \
    utils/Log.cpp \
    utils/StringUtils.cpp \
    main.cpp \
    stb_vorbis.c \
    al2/AudioSystem.cpp
    main.cpp \

HEADERS += \
    stb_image.h \
    stb_vorbis.h \
    al2/OpenALBackend.hpp \
    utils/Debug.hpp \
    utils/Error.hpp \
    utils/Exception.hpp \
    utils/Log.hpp \
    utils/NonCopyable.hpp \
    utils/Singleton.hpp \
    utils/StringUtils.hpp \
    al2/AudioSystem.hpp
