#include(../../../include.pri)
#include(../../../include_test.pri)
include(../include.pri)
TEMPLATE += app
CONFIG += testcase

TARGET = unit-tests

HEADERS += \
    ../models/tests/diagonal-model-test/diagonal_model_test.hpp \
    ../models/tests/em-algo-test/em_algo_test.hpp \
    ../utils/tests/utils-test/utils_test.hpp \
    ../features/tests/feature-readers-tests/feature_readers_test.hpp \
#    ../dao/tests/dao-test/dao_test.hpp
    ../models/tests/verificator-test/verificator_test.hpp \
    ../dao/tests/dao-test/dao_test.hpp \
    ../features/tests/mfcc_converter_tests/mfcc_converter_linux_test.hpp \
    ../models/tests/model-manager-test/model_manager_test.hpp

SOURCES += \
    main_test.cpp \
    ../models/tests/diagonal-model-test/diagonal_model_test.cpp \
    ../models/tests/em-algo-test/em_algo_test.cpp \
    ../utils/tests/utils-test/utils_test.cpp \
    ../features/tests/feature-readers-tests/feature_readers_test.cpp \
#    ../dao/tests/dao-test/dao_test.cpp
    ../models/tests/verificator-test/verificator_test.cpp \
    ../dao/tests/dao-test/dao_test.cpp \
    ../features/tests/mfcc_converter_tests/mfcc_converter_linux_test.cpp \
    ../models/tests/model-manager-test/model_manager_test.cpp
