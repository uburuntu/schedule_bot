TARGET = schedule_bot

TEMPLATE = app

QT -= gui core

CONFIG += debug_and_release
CONFIG += console
CONFIG -= qml_debug
CONFIG(release, debug|release) {
    CONFIG += optimize_full
}
QMAKE_LFLAGS_RELEASE += -O3
QMAKE_LFLAGS_RELEASE -= -Wl,-O1

QMAKE_CXXFLAGS += -std=c++11 -Wall -Wextra -W
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
    src/user.h

SOURCES += src/main.cpp \
    src/user.cpp
