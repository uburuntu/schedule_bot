TARGET = schedule_bot

TEMPLATE = app

QT -= gui core

CONFIG += console
CONFIG -= qml_debug

QMAKE_CXXFLAGS += -std=c++11 -Wall -Wextra -W
QMAKE_LIBS += -lTgBot -lboost_system -lboost_iostreams -lssl -lcrypto

INCLUDEPATH *= src config

OBJECTS_DIR = build

# Input
HEADERS += config/token.h \

SOURCES += src/main.cpp \
