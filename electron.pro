#-------------------------------------------------
#
# Project created by QtCreator 2016-04-12T19:18:56
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4) {
    QT += widgets
    CONFIG += c++11
} else {
    QMAKE_CXXFLAGS += -std=c++0x
    DEFINES +="'Q_UNREACHABLE()=(void)1'"
}

TARGET = electron
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    qlibs/qtreemodel.cpp \
    libs/containers/tree.cpp \
    components/electroniccomponent.cpp \
    models/electroniccomponentsmodel.cpp \
    models/appmodel.cpp

HEADERS  += mainwindow.h \
    qlibs/qtreemodel.h \
    libs/containers/tree.h \
    components/electroniccomponent.h \
    models/electroniccomponentsmodel.h \
    models/appmodel.h
