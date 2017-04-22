TARGET = schedule_bot

TEMPLATE = app

QT -= gui core

CONFIG += console
CONFIG -= qml_debug

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

SOURCES += src/main.cpp \
