#include "record_dir_manager_test.hpp"

using namespace std;
using namespace alize;
using namespace boost;

BOOST_AUTO_TEST_SUITE( RecordDirManagerTest )

//BOOST_AUTO_TEST_CASE( checkExistanceOfModelFolderIfTheyExist )
//{
//  ConfigManager conf;
//  const string F_FOLDER = "feature-folder";
//  conf.setFeatureFolder(F_FOLDER);
//  RecordDirManager manager;
//  manager.setConfig(conf);
//  BOOST_CHECK(manager.isDirExist("model1"));
//}

//BOOST_AUTO_TEST_CASE( createModelFolderIfFeatureFolderExist )
//{
//  ConfigManager conf;
//  const string F_FOLDER = "feature-folder", M_NAME = "model_created";
//  conf.setFeatureFolder(F_FOLDER);
//  RecordDirManager manager(conf);
//  BOOST_CHECK_NO_THROW(manager.createModelDir(M_NAME));
//  QDir model_dir((F_FOLDER + "/" + M_NAME).c_str());
//  BOOST_REQUIRE(model_dir.exists());
//  BOOST_CHECK(QDir(F_FOLDER.c_str()).rmdir(M_NAME.c_str()));
//  BOOST_CHECK(!model_dir.exists());
//}

//BOOST_AUTO_TEST_CASE( throwDirNotFoundAtCreatingModelFolderIfFeatureFolderDoesNotExist )
//{
//  const string FAKE_FOLDER = "not-exist", M_NAME = "model_created";
//  BOOST_REQUIRE(!QDir((FAKE_FOLDER).c_str()).exists());
//  BOOST_REQUIRE(!QDir((FAKE_FOLDER + "/" + M_NAME).c_str()).exists());

//  ConfigManager conf;
//  conf.setFeatureFolder(FAKE_FOLDER);
//  RecordDirManager manager(conf);
//  BOOST_CHECK_THROW(manager.createModelDir(M_NAME), DirNotFound);
//  BOOST_CHECK(!QDir((FAKE_FOLDER + "/" + M_NAME).c_str()).exists());
//}
///*
//BOOST_AUTO_TEST_CASE( throwUnableCreateFolderAtCreatingModelFolderIfFeatureFolderIsReadOnly )
//{
//  const string F_FOLDER = "feature-folder/read-only-folder", M_NAME = "model_created";
//  BOOST_REQUIRE(!QDir((F_FOLDER + "/" + M_NAME).c_str()).exists());

//  ConfigManager conf;
//  conf.setFeatureFolder(F_FOLDER);
//  RecordDirManager manager(conf);
//  BOOST_CHECK_THROW(manager.createModelDir(M_NAME), UnableToCreateFolder);//folder istnieje, ale jest read-only. Mimo to exists nie może odczytać info o folderze i zwraca false.
//  //na razie nie mam pomysłu jak można napisać do tego test
//  BOOST_CHECK(!QDir((F_FOLDER + "/" + M_NAME).c_str()).exists());

//}
//*/
//BOOST_AUTO_TEST_CASE( removeModelFolderIfFeatureFolderExist )
//{
//  ConfigManager conf;
//  const string F_FOLDER = "feature-folder", M_NAME = "model_to_remove";
//  conf.setFeatureFolder(F_FOLDER);
//  RecordDirManager manager(conf);
//  BOOST_CHECK_NO_THROW(manager.removeModelDir(M_NAME));
//  QDir model_dir((F_FOLDER + "/" + M_NAME).c_str());
//  BOOST_REQUIRE(!model_dir.exists());
//  BOOST_CHECK(QDir(F_FOLDER.c_str()).mkdir(M_NAME.c_str()));
//  BOOST_CHECK(model_dir.exists());
//}

//BOOST_AUTO_TEST_CASE( throwDirNotFoundAtRemovingModelFolderIfFeatureFolderDoesNotExist )
//{
//  const string FAKE_FOLDER = "fake-folder", M_NAME = "model_to_remove";
//  BOOST_REQUIRE(!QDir((FAKE_FOLDER).c_str()).exists());

//  ConfigManager conf;
//  conf.setFeatureFolder(FAKE_FOLDER);
//  RecordDirManager manager(conf);
//  BOOST_CHECK_THROW(manager.removeModelDir(M_NAME), DirNotFound);

//}

//BOOST_AUTO_TEST_CASE( throwUnableToRemoveFolderAtRemovingModelFolderIfModelFolderDoesNotExist )
//{
//  const string F_FOLDER = "feature-folder", FAKE_M_NAME = "model_not_exists";
//  BOOST_REQUIRE(!QDir((F_FOLDER + "/" + FAKE_M_NAME).c_str()).exists());

//  ConfigManager conf;
//  conf.setFeatureFolder(F_FOLDER);
//  RecordDirManager manager(conf);
//  BOOST_CHECK_THROW(manager.removeModelDir(FAKE_M_NAME), UnableToRemoveFolder);

//}
///*
//BOOST_AUTO_TEST_CASE( throwUnableRemoveFolderAtRemovingModelFolderIfFeatureFolderIsReadOnly )
//{
//  const string F_FOLDER = "feature-folder", M_NAME = "read-only-folder";
//  BOOST_REQUIRE(QDir((F_FOLDER + "/" + M_NAME).c_str()).exists());//exists zwraca false nawet wted gdy folder istnieje, ale nie ma do niego dostępu

//  ConfigManager conf;
//  conf.setFeatureFolder(F_FOLDER);
//  RecordDirManager manager(conf);
//  BOOST_CHECK_THROW(manager.removeModelDir(M_NAME), UnableToRemoveFolder);
//  BOOST_CHECK(QDir((F_FOLDER + "/" + M_NAME).c_str()).exists());

//}
//*/

//BOOST_AUTO_TEST_CASE( cleanModelFolderIfFeatureFolderExist )
//{
//  ConfigManager conf;
//  const string F_FOLDER = "feature-folder", M_NAME = "model_to_clean";
//  conf.setFeatureFolder(F_FOLDER);
//  RecordDirManager manager(conf);
//  BOOST_CHECK_NO_THROW(manager.cleanModelDir(M_NAME));
//  QDir model_dir((F_FOLDER + "/" + M_NAME).c_str());
//  BOOST_REQUIRE(model_dir.exists());
//  BOOST_REQUIRE(model_dir.entryList().size() == 2 ||
//                model_dir.entryList().contains(".") ||
//                model_dir.entryList().contains(".."));
//  BOOST_CHECK(QFile((F_FOLDER + "/" + M_NAME + "/" + string("record1.mp3")).c_str())
//              .open(QIODevice::ReadWrite));
//  BOOST_CHECK(QFile((F_FOLDER + "/" + M_NAME + "/" + string("record2.wav")).c_str())
//              .open(QIODevice::ReadWrite));
//  BOOST_CHECK(QFile((F_FOLDER + "/" + M_NAME + "/" + string("record3.txt")).c_str())
//              .open(QIODevice::ReadWrite));

//}

//BOOST_AUTO_TEST_CASE( throwDirNotFoundAtCleanModelFolderIfFeatureFolderDoesNotExist )
//{
//  const string FAKE_FOLDER = "fake-folder", M_NAME = "model_to_remove";
//  BOOST_REQUIRE(!QDir((FAKE_FOLDER).c_str()).exists());

//  ConfigManager conf;
//  conf.setFeatureFolder(FAKE_FOLDER);
//  RecordDirManager manager(conf);
//  BOOST_CHECK_THROW(manager.cleanModelDir(M_NAME), DirNotFound);

//}

//BOOST_AUTO_TEST_CASE( throwUnableToCleanFolderAtCleaningModelFolderIfModelFolderDoesNotExist )
//{
//  const string F_FOLDER = "feature-folder", FAKE_M_NAME = "model_not_exists";
//  BOOST_REQUIRE(!QDir((F_FOLDER + "/" + FAKE_M_NAME).c_str()).exists());

//  ConfigManager conf;
//  conf.setFeatureFolder(F_FOLDER);
//  RecordDirManager manager(conf);
//  BOOST_CHECK_THROW(manager.cleanModelDir(FAKE_M_NAME), UnableToCleanFolder);

//}










BOOST_AUTO_TEST_SUITE_END()
