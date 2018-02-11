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
    al/ALBackend.cpp \
    al/ALBuffer.cpp \
    al/ALOggSample.cpp \
    al/ALWavSample.cpp \
    al/ALUtil.cpp \
    al/ALSource.cpp \
    al/ALSoundEmitter.cpp \
    al/ALListener.cpp \
    AudioSystem.cpp
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
    al/ALSoundBase.hpp \
    al/ALBackend.hpp \
    al/ALBuffer.hpp \
    al/ALOggSample.hpp \
    al/ALWavSample.hpp \
    al/ALUtil.hpp \
    al/ALSource.hpp \
    al/ALSoundEmitter.hpp \
    al/ALListener.hpp \
    openglbacked.hpp \
    AudioSystem.hpp
