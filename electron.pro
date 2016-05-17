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
#    components/electroniccomponent.cpp \
#    models/electroniccomponentsmodel.cpp \
#    models/appmodel.cpp \
    components/electron.cpp \
    components/electronelement.cpp \
    qlibs/qpreviewmodel.cpp \
    elemwidget.cpp \
    qlibs/qgraphicschip.cpp \
    components/electronimage.cpp \
    qschemeview.cpp \
    components/electronscheme.cpp \
    qlibs/qschememodel.cpp \
    components/electronwire.cpp \
    components/electroncontact.cpp \
    qlibs/qgraphicswire.cpp \
    qlibs/qgraphicsgrid.cpp

HEADERS  += mainwindow.h \
    qlibs/qtreemodel.h \
#    components/electroniccomponent.h \
#    models/electroniccomponentsmodel.h \
#    models/appmodel.h \
    components/electron.h \
#    libs/containers/_tree.h \
    libs/containers/tree.h \
    components/electronelement.h \
    qlibs/qpreviewmodel.h \
    elemwidget.h \
    qlibs/qgraphicschip.h \
    components/electronimage.h \
    qschemeview.h \
    components/electronscheme.h \
    qlibs/qschememodel.h \
    libs/containers/graph.h \
    components/electronwire.h \
    components/electroncontact.h \
    qlibs/qgraphicswire.h \
    qlibs/qgraphicsgrid.h \
    libs/containers/myallocator.h \
    libs/containers/myexception.h

RESOURCES += \
    images.qrc

