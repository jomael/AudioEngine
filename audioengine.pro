TEMPLATE = app
CONFIG += c++14
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

LIBS += -lglfw3 -lGL -lGLEW -lm -lXrandr -lXi -lX11 -lXxf86vm -lpthread -lopenal

SOURCES += \
    util/Error.cpp \
    util/Log.cpp \
    util/StringUtils.cpp \
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
    util/Debug.hpp \
    util/Error.hpp \
    util/Exception.hpp \
    util/Log.hpp \
    util/NonCopyable.hpp \
    util/Singleton.hpp \
    util/StringUtils.hpp \
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
