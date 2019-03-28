#include "temp_dir_manager_tests.hpp"


using namespace std;
using namespace alize;
using namespace boost;

BOOST_AUTO_TEST_SUITE( TempDirManagerTest )


//BOOST_AUTO_TEST_CASE( throwUnableCreateFolderAtCreatingModelFolderIfModelFolderIsTempFolderName )
//{
//  const string F_FOLDER = "feature-folder";
//  BOOST_REQUIRE(QDir((F_FOLDER).c_str()).exists());

//  ConfigManager conf;
//  conf.setFeatureFolder(F_FOLDER);
//  TempDirManager manager(conf);
//  const string M_NAME = manager.TEMP_DIR_NAME;
//  BOOST_CHECK_THROW(manager.createModelDir(M_NAME), UnableToCreateFolder);
//  BOOST_REQUIRE(!QDir((F_FOLDER + "/" + M_NAME).c_str()).exists());
//  QDir((F_FOLDER).c_str()).rmdir(M_NAME.c_str());

//}

//BOOST_AUTO_TEST_CASE( throwUnableRemoveFolderAtRemovingModelFolderIfModelFolderIsTempFolderName )
//{
//  const string F_FOLDER = "feature-folder";
//  BOOST_REQUIRE(QDir((F_FOLDER).c_str()).exists());

//  ConfigManager conf;
//  conf.setFeatureFolder(F_FOLDER);
//  TempDirManager manager(conf);
//  const string M_NAME = manager.TEMP_DIR_NAME;
//  BOOST_CHECK(QDir((F_FOLDER).c_str()).mkdir(M_NAME.c_str()));
//  BOOST_CHECK_THROW(manager.removeModelDir(M_NAME), UnableToRemoveFolder);
//  BOOST_REQUIRE(QDir((F_FOLDER + "/" + M_NAME).c_str()).exists());
//  BOOST_CHECK(QDir((F_FOLDER).c_str()).rmdir(M_NAME.c_str()));

//}

//BOOST_AUTO_TEST_CASE( throwUnableCleanFolderAtCleaningModelFolderIfModelFolderIsTempFolderName )
//{
//  const string F_FOLDER = "feature-folder";
//  BOOST_REQUIRE(QDir((F_FOLDER).c_str()).exists());

//  ConfigManager conf;
//  conf.setFeatureFolder(F_FOLDER);
//  TempDirManager manager(conf);
//  const string M_NAME = manager.TEMP_DIR_NAME;
//  BOOST_CHECK(QDir((F_FOLDER).c_str()).mkdir(M_NAME.c_str()));
//  BOOST_CHECK_THROW(manager.cleanModelDir(M_NAME), UnableToCleanFolder);
//  BOOST_REQUIRE(QDir((F_FOLDER + "/" + M_NAME).c_str()).exists());
//  BOOST_CHECK(QDir((F_FOLDER).c_str()).rmdir(M_NAME.c_str()));

//}



BOOST_AUTO_TEST_SUITE_END()
