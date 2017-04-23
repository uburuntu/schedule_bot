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
QMAKE_LIBS += -lTgBot -lssl -lcrypto
LIBS += -L/usr/local/lib -lboost_system -lboost_iostreams -lboost_date_time
PRE_TARGETDEPS += /usr/local/lib/libboost_system.a /usr/local/lib/libboost_iostreams.a /usr/local/lib/libboost_date_time.a

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
    src/include/sch_bot.h \
    src/include/utils.h

SOURCES += src/main.cpp \
    src/user.cpp \
    src/event.cpp \
    src/sch_bot.cpp

DISTFILES += \
    config/code_style.astylerc
