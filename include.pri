QT += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

LIBS += -L/usr/local/lib/libalize -lalize -lboost_unit_test_framework
QMAKE_CXXFLAGS += -std=c++14

DISTFILES += \
    $$PWD/config


