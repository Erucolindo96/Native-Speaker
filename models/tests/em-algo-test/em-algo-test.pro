include(../../../include.pri)

TEMPLATE += app
CONFIG += testcase

TARGET = em-algo-test

SOURCES = em_algo_test.cpp
INCLUDEPATH += ../../..
LIBS += -L../../../common -lcommon
