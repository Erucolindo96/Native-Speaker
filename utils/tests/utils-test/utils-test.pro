include(../../../include.pri)

TEMPLATE += app
CONFIG += testcase

TARGET = utils-test

SOURCES = utils_test.cpp \

INCLUDEPATH += ../../..
LIBS += -L../../../common -lcommon

SOURCES += ../../utils.cpp \


HEADERS  +=  ../../utils.hpp \

