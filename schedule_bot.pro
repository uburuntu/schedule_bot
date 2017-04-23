TARGET = schedule_bot

TEMPLATE = app

QT -= gui core

CONFIG += debug_and_release
CONFIG += console
CONFIG -= qml_debug
CONFIG(release, debug|release) {
    CONFIG += optimize_full
}
QMAKE_LFLAGS_RELEASE += -Ofast
QMAKE_LFLAGS_RELEASE -= -Wl,-O1

QMAKE_CXXFLAGS += -std=c++1y -W -Wall -Wunused -Wcast-align -pedantic -fstack-protector-all \
                  -Wfloat-equal -Wpointer-arith -Wwrite-strings -Wcast-align -Wno-format \
                  -Wno-long-long -Wmissing-declarations
QMAKE_LIBS += -lTgBot -lboost_system -lboost_iostreams -lssl -lcrypto

INCLUDEPATH *= src config

CONFIG(debug, debug|release) {
    DESTDIR = build.dbg
} else {
    DESTDIR = build
}

OBJECTS_DIR = $$DESTDIR/obj

# Input
HEADERS += config/token.h \
    src/include/user.h \
    src/include/event.h \
    src/sch_bot.h

SOURCES += src/main.cpp \
    src/user.cpp \
    src/event.cpp \
    src/sch_bot.cpp

DISTFILES += \
    config/code_style.astylerc
