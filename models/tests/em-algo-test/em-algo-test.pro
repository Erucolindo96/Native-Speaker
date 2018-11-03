include(../../../include.pri)

TEMPLATE += app
CONFIG += testcase

TARGET = em-algo-test

SOURCES = em_algo_test.cpp
INCLUDEPATH += ../../..
LIBS += -L../../../common -lcommon

SOURCES += ../../diagonal_model.cpp \
    ../../gmmmodel.cpp \
    ../../learning_algo.cpp \
#    ../mainwindow.cpp

HEADERS  +=  ../../diagonal_model.hpp \
    ../../gmmmodel.hpp \
    ../../learning_algo.hpp \

DISTFILES += \
    config
