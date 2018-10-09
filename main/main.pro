include(../include.pri)

TEMPLATE = app
CONFIG += windows
TARGET = main
SOURCES = ../main.cpp
INCLUDEPATH += ../common ..
LIBS += -L../common -lcommon

SOURCES += ../mainwindow.cpp

HEADERS += ../mainwindow.hpp

FORMS    += ../mainwindow.ui \
    ../wybormodelu.ui

