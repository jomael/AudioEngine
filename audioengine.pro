TEMPLATE = app
CONFIG += c++14
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

LIBS += -lglfw3 -lGL -lGLEW -lm -lXrandr -lXi -lX11 -lXxf86vm -lpthread -lopenal

SOURCES += \
    utils/Error.cpp \
    utils/Log.cpp \
    utils/StringUtils.cpp \
    main.cpp \
    stb_vorbis.c \
    al2/AudioSystem.cpp \
    al2/ALBackend.cpp \
    al2/ALBuffer.cpp \
    al2/ALOggSample.cpp \
    al2/ALWavSample.cpp \
    al2/ALUtil.cpp \
    al2/ALSource.cpp \
    al2/ALSoundEmitter.cpp
    main.cpp \

HEADERS += \
    stb_image.h \
    stb_vorbis.h \
    utils/Debug.hpp \
    utils/Error.hpp \
    utils/Exception.hpp \
    utils/Log.hpp \
    utils/NonCopyable.hpp \
    utils/Singleton.hpp \
    utils/StringUtils.hpp \
    al2/AudioSystem.hpp \
    al2/ALSoundBase.hpp \
    al2/ALBackend.hpp \
    al2/ALBuffer.hpp \
    al2/ALOggSample.hpp \
    al2/ALWavSample.hpp \
    al2/ALUtil.hpp \
    al2/ALSource.hpp \
    al2/ALSoundEmitter.hpp
