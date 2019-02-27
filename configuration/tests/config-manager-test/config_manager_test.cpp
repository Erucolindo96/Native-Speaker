﻿#include"configuration/tests/config-manager-test/config_manager_test.hpp"
using namespace boost;
using namespace std;
using namespace alize;



BOOST_AUTO_TEST_SUITE( ConfigManagerTest )

BOOST_AUTO_TEST_CASE( getCorrectVectSizeIfThatWasSetInSetter )
{
  cout<<"Test działa"<<endl;
  ConfigManager manager;
  uint32_t vec_size = 20;
  BOOST_REQUIRE_NO_THROW(manager.setVectSize(vec_size));
  BOOST_CHECK_EQUAL(manager.getVectSize(), vec_size);
}

BOOST_AUTO_TEST_CASE( getCorrectModelFolderIfThatWasSetInSetter )
{
  ConfigManager manager;
  string model_folder = "/users/modele/";
  BOOST_REQUIRE_NO_THROW(manager.setModelFolder(model_folder));
  BOOST_CHECK_EQUAL(manager.getModelFolder(), model_folder);
}

BOOST_AUTO_TEST_CASE( getCorrectFeatureFolderIfThatWasSetInSetter )
{
  ConfigManager manager;
  string feature_folder = "/users/features/";
  BOOST_REQUIRE_NO_THROW(manager.setFeatureFolder(feature_folder));
  BOOST_CHECK_EQUAL(manager.getFeatureFolder(), feature_folder);
}


BOOST_AUTO_TEST_CASE( getCorrectUbmFolderIfThatWasSetInSetter )
{
  ConfigManager manager;
  string ubm_folder = "/users/features/";
  BOOST_REQUIRE_NO_THROW(manager.setUbmFolder(ubm_folder));
  BOOST_CHECK_EQUAL(manager.getUbmFolder(), ubm_folder);
}

BOOST_AUTO_TEST_CASE( throwParamNotFoundExceptionIfParamDoesntExist )
{
  ConfigManager manager;
  BOOST_CHECK_THROW(manager.getVectSize(), ParamNotFoundInConfigException);
  BOOST_CHECK_THROW(manager.getFeatureFolder(), ParamNotFoundInConfigException);
  BOOST_CHECK_THROW(manager.getUbmFolder(), ParamNotFoundInConfigException);
  BOOST_CHECK_THROW(manager.getModelFolder(), ParamNotFoundInConfigException);

}

BOOST_AUTO_TEST_CASE( correctlySaveAndLoadConfigToFileIfDirWhereIsSavedExist )
{
  ConfigManager manager, manager2;
  string file_path = "configs/config.cnf", ubm_folder = "/folder";
  uint32_t vect_size = 20;

  BOOST_REQUIRE_NO_THROW(manager.setVectSize(vect_size));
  BOOST_REQUIRE_NO_THROW(manager.setUbmFolder(ubm_folder));
  BOOST_REQUIRE_NO_THROW(manager.save(file_path.c_str()));
  QFile conf_file(file_path.c_str());
  BOOST_CHECK(conf_file.exists());

  BOOST_REQUIRE_NO_THROW(manager2.load(file_path.c_str()));

  BOOST_CHECK_EQUAL(manager2.getVectSize(), vect_size);
  BOOST_CHECK_EQUAL(manager2.getUbmFolder(), ubm_folder);
  BOOST_CHECK_THROW(manager2.getFeatureFolder(), ParamNotFoundInConfigException);


}






BOOST_AUTO_TEST_SUITE_END()
