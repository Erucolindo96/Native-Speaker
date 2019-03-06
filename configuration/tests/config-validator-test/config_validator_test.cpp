#include "configuration/tests/config-validator-test/config_validator_test.hpp"
using namespace boost;
using namespace std;
using namespace alize;




BOOST_AUTO_TEST_SUITE( ConfigValidatorTest )

BOOST_AUTO_TEST_CASE( validateVectSize )
{
  ConfigValidator validator;
  std::string param_name = ConfigManager::VALID_PARAMS_.at(VECT_SIZE), param_val = "29";
  BOOST_CHECK_NO_THROW(validator.isParamValid(param_name, param_val));
  BOOST_CHECK_THROW(validator.isParamValid("VectSize", "89"), ParamNotValid);
  BOOST_CHECK_THROW(validator.isParamValid(param_name, "-12"), ParamNotValid);
  BOOST_CHECK_THROW(validator.isParamValid(param_name, "sks"), ParamNotValid);

}

BOOST_AUTO_TEST_CASE( validateUbmDir )
{
  ConfigValidator validator;
  std::string param_name = ConfigManager::VALID_PARAMS_.at(UBM_DIR), param_val = "/home";
  BOOST_CHECK_NO_THROW(validator.isParamValid(param_name, param_val));
  BOOST_CHECK_THROW(validator.isParamValid(param_name, "/fake_path"), ParamNotValid);
  BOOST_CHECK_THROW(validator.isParamValid("UbmDir", "/home"), ParamNotValid);
}

BOOST_AUTO_TEST_CASE( validateModelDir )
{
  ConfigValidator validator;
  std::string param_name = ConfigManager::VALID_PARAMS_.at(MODEL_DIR),
      param_val = "/home";
  BOOST_CHECK_NO_THROW(validator.isParamValid(param_name, param_val));
  BOOST_CHECK_THROW(validator.isParamValid(param_name, "/fake_path"), ParamNotValid);
  BOOST_CHECK_THROW(validator.isParamValid("MODELDir", "/home"), ParamNotValid);
}

BOOST_AUTO_TEST_CASE( validateFeatureFolder )
{
  ConfigValidator validator;
  std::string param_name = ConfigManager::VALID_PARAMS_.at(FEATURE_FOLDER),
      param_val = "/home";
  BOOST_CHECK_NO_THROW(validator.isParamValid(param_name, param_val));
  BOOST_CHECK_THROW(validator.isParamValid(param_name, "/fake_path"), ParamNotValid);
  BOOST_CHECK_THROW(validator.isParamValid("FEATUREDIR!!!", "/home"), ParamNotValid);
}

BOOST_AUTO_TEST_CASE( validateIsDebug )
{
  ConfigValidator validator;
  std::string param_name = ConfigManager::VALID_PARAMS_.at(IS_DEBUG);
  BOOST_CHECK_NO_THROW(validator.isParamValid(param_name, "true"));
  BOOST_CHECK_NO_THROW(validator.isParamValid(param_name, "false"));
  BOOST_CHECK_THROW(validator.isParamValid(param_name, "prawda"), ParamNotValid);
  BOOST_CHECK_THROW(validator.isParamValid("debud", "true"), ParamNotValid);
}


BOOST_AUTO_TEST_CASE( validateAllConfig )
{
  ConfigManager manager;
  ConfigValidator v;

  BOOST_REQUIRE_NO_THROW(manager.load("configs/valid_config"));
  BOOST_CHECK_NO_THROW(v.validateConfiguration(manager));

  BOOST_REQUIRE_NO_THROW(manager.load("configs/invalid_config"));
  BOOST_CHECK_THROW(v.validateConfiguration(manager), ParamNotValid);

}


BOOST_AUTO_TEST_SUITE_END()
