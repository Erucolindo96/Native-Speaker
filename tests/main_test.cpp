#define BOOST_TEST_MODULE unit-tests
#define BOOST_TEST_DYN_LINK

#include "models/tests/diagonal-model-test/diagonal_model_test.hpp"
#include"models/tests/em-algo-test/em_algo_test.hpp"
#include"utils/tests/utils-test/utils_test.hpp"
#include"features/tests/feature-readers-tests/feature_readers_test.hpp"
#include"dao/tests/dao-test/dao_test.hpp"
#include"models/tests/verificator-test/verificator_test.hpp"
#include"features/tests/mfcc_converter_tests/mfcc_converter_test.hpp"
#include"configuration/tests/config-manager-test/config_manager_test.hpp"
#include"configuration/tests/config-validator-test/config_validator_test.hpp"
#include<QApplication>

int argc = 1;
char *argv[] = {"unit-tests",};
QApplication app(argc, argv);
