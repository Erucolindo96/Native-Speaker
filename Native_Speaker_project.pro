#-------------------------------------------------
#
# Project created by QtCreator 2018-07-07T23:13:06
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Native_Speaker_project
TEMPLATE = app

CONFIG += c++14
LIBS += -L/usr/local/lib/libalize -lalize
QMAKE_CXXFLAGS += -std=c++14

SOURCES += main.cpp\
        mainwindow.cpp \
    record.cpp \
    speakermodel.cpp \
    gmmmodel.cpp \
    UbmModel.cpp \
    feature_generator.cpp \
    learning_algo.cpp

HEADERS  += mainwindow.hpp \
    speaker.hpp \
    record.hpp \
    speakermodel.hpp \
    gmmmodel.hpp \
    DataAccessObjects.hpp \
    UbmModel.hpp \
    learning_algo.hpp \
    feature_generator.hpp

FORMS    += mainwindow.ui \
    wybormodelu.ui
