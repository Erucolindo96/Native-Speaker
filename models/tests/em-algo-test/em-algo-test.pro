include(../../../include.pri)

TEMPLATE += app
CONFIG += testcase

TARGET = em-algo-test

SOURCES = em_algo_test.cpp \

INCLUDEPATH += ../../.. \
            ../../../../../alize-core/include
LIBS += -L../../../common -lcommon

SOURCES += ../../diagonal_model.cpp \
    ../../gmmmodel.cpp \
    ../../learning_algo.cpp \
#    ../mainwindow.cpp

HEADERS  +=  ../../diagonal_model.hpp \

DISTFILES += \
    config \
    ../../../../../alize-core/src/Makefile \
    ../../../../../alize-core/src/Makefile.am \
    ../../../../../alize-core/src/Makefile.in
