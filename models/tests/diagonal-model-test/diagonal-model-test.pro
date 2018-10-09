include(../../../include.pri)

TEMPLATE += app
CONFIG += testcase

TARGET = diagonal-model-test

SOURCES = diagonal_model_test.cpp
INCLUDEPATH += ../../..
LIBS += -L../../../common -lcommon
