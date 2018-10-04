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
    feature_generator.cpp \
    utils/utils.cpp \
    models/diagonal_model.cpp \
    models/gmmmodel.cpp \
    models/learning_algo.cpp

HEADERS  += mainwindow.hpp \
    feature_generator.hpp \
    models/diagonal_model.hpp \
    models/gmmmodel.hpp \
    models/learning_algo.hpp \
    utils/utils.hpp

FORMS    += mainwindow.ui \
    wybormodelu.ui
