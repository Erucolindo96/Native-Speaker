#include "record_dir_manager_test.hpp"


using namespace std;
using namespace alize;
using namespace boost;

BOOST_AUTO_TEST_SUITE( RecordDirManagerTests )

BOOST_AUTO_TEST_CASE(initialization)
{
  const QString FEATURE_FOLDER_PATH("feature-folder-record-dir-manager"),
      MODEL_1_NAME("model1"),
      MODEL_1_PATH(FEATURE_FOLDER_PATH + "/" + MODEL_1_NAME);

  BOOST_REQUIRE(QDir(FEATURE_FOLDER_PATH).exists());
  if(!QDir(MODEL_1_PATH).exists())
  {
    BOOST_CHECK(QDir(FEATURE_FOLDER_PATH).mkdir(MODEL_1_NAME));
  }
}

BOOST_AUTO_TEST_CASE(setFeatureFolderIfFeatureFolderExists)
{
  const QString FEATURE_FOLDER_PATH("feature-folder-record-dir-manager");
  BOOST_REQUIRE(QDir(FEATURE_FOLDER_PATH).exists());
  RecordDirManager manager;
  BOOST_CHECK_NO_THROW(manager.setFeatureFolder(FEATURE_FOLDER_PATH));
}

BOOST_AUTO_TEST_CASE(throwDirNotFoundAdSettingFeatureFolderIfFeatureFolderDoesNotExists)
{
  const QString FEATURE_FOLDER_PATH("fake-folder");
  BOOST_REQUIRE(!QDir(FEATURE_FOLDER_PATH).exists());
  RecordDirManager manager;
  BOOST_CHECK_THROW(manager.setFeatureFolder(FEATURE_FOLDER_PATH), FeatureFolderNotFound);
}

BOOST_AUTO_TEST_CASE(checkExistanceOfModelRecordDirIfThisOneExists)
{
  const QString FEATURE_FOLDER_PATH("feature-folder-record-dir-manager");
  const string DIR_NAME = "model1";
  BOOST_REQUIRE(QDir(FEATURE_FOLDER_PATH).exists());
  RecordDirManager manager;
  BOOST_REQUIRE_NO_THROW(manager.setFeatureFolder(FEATURE_FOLDER_PATH));

  BOOST_CHECK(manager.isDirExists(DIR_NAME));
}

BOOST_AUTO_TEST_CASE(checkExistanceOfModelRecordDirIfThisOneDoesNotExists)
{
  const QString FEATURE_FOLDER_PATH("feature-folder-record-dir-manager");
  const string DIR_NAME = "not-exists";
  BOOST_REQUIRE(QDir(FEATURE_FOLDER_PATH).exists());
  RecordDirManager manager;
  BOOST_REQUIRE_NO_THROW(manager.setFeatureFolder(FEATURE_FOLDER_PATH));

  BOOST_CHECK(!manager.isDirExists(DIR_NAME));
}

BOOST_AUTO_TEST_CASE(throwDirNotFoundAtCheckingExistanceOfModelDirIfFeatureFolderWasNotSet)
{
  const string DIR_NAME = "not-exists";
  RecordDirManager manager;
  BOOST_CHECK_THROW(manager.isDirExists(DIR_NAME), FeatureFolderNotFound);
}

BOOST_AUTO_TEST_CASE(createNewModelFolderIfFeatureFolderExists)
{
  const string DIR_NAME = "new-model";
  const QString FEATURE_FOLDER_PATH("feature-folder-record-dir-manager"), DIR_PATH = "feature-folder-record-dir-manager/new-model";

  BOOST_REQUIRE(QDir(FEATURE_FOLDER_PATH).exists());
  BOOST_REQUIRE(!QDir(DIR_PATH).exists());
  RecordDirManager manager;
  BOOST_REQUIRE_NO_THROW(manager.setFeatureFolder(FEATURE_FOLDER_PATH));

  BOOST_REQUIRE_NO_THROW(manager.getModelDir(DIR_NAME));
  BOOST_CHECK(QDir(DIR_PATH).exists());
  //sprzątanie
  BOOST_CHECK(QDir(FEATURE_FOLDER_PATH).rmdir(DIR_NAME.c_str()));
}

BOOST_AUTO_TEST_CASE(getRecordDirOfExistingDirIfFeatureFolderExists)
{
  const string DIR_NAME = "model1";
  const QString FEATURE_FOLDER_PATH("feature-folder-record-dir-manager"),
      DIR_PATH = "feature-folder-record-dir-manager/model1";

  BOOST_REQUIRE(QDir(FEATURE_FOLDER_PATH).exists());
  BOOST_REQUIRE(QDir(DIR_PATH).exists());
  RecordDirManager manager;
  BOOST_REQUIRE_NO_THROW(manager.setFeatureFolder(FEATURE_FOLDER_PATH));

  BOOST_REQUIRE_NO_THROW(manager.getModelDir(DIR_NAME));

  RecordDir dir = manager.getModelDir(DIR_NAME);
}

BOOST_AUTO_TEST_CASE(throwFeatureFolderNotFoundAtCreatingNewModelIfFeatureFolderWasNotSetAndNewDirDoesNotExists)
{
  const string DIR_NAME = "new-model";
  const QString DIR_PATH = "feature-folder-record-dir-manager/new-model";

  BOOST_REQUIRE(!QDir(DIR_PATH).exists());
  RecordDirManager manager;
  BOOST_REQUIRE_THROW(manager.getModelDir(DIR_NAME), FeatureFolderNotFound);
}


BOOST_AUTO_TEST_CASE(getRecordDirOfExistingDirIfFeatureFolderExistsAndRecordDirManagerIsConst)
{
  const string DIR_NAME = "model1";
  const QString FEATURE_FOLDER_PATH("feature-folder-record-dir-manager"),
      DIR_PATH = "feature-folder-record-dir-manager/model1";

  BOOST_REQUIRE(QDir(FEATURE_FOLDER_PATH).exists());
  BOOST_REQUIRE(QDir(DIR_PATH).exists());

  RecordDirManager manager;
  BOOST_REQUIRE_NO_THROW(manager.setFeatureFolder(FEATURE_FOLDER_PATH));

  BOOST_CHECK_NO_THROW(static_cast<const RecordDirManager>(manager).getModelDir(DIR_NAME));

  RecordDir dir = manager.getModelDir(DIR_NAME);
}

BOOST_AUTO_TEST_CASE(throwDirNotFoundIfFeatureFolderExistsAndRecordDirManagerIsConstAndModelDirDoesNotExists)
{
  const string DIR_NAME = "new-model";
  const QString FEATURE_FOLDER_PATH("feature-folder-record-dir-manager"),
      DIR_PATH = "feature-folder-record-dir-manager/new-model";

  BOOST_REQUIRE(QDir(FEATURE_FOLDER_PATH).exists());
  BOOST_REQUIRE(!QDir(DIR_PATH).exists());

  RecordDirManager manager;
  BOOST_REQUIRE_NO_THROW(manager.setFeatureFolder(FEATURE_FOLDER_PATH));

  BOOST_CHECK_THROW(static_cast<const RecordDirManager>(manager).getModelDir(DIR_NAME), DirNotFound);
}

BOOST_AUTO_TEST_CASE(throwFeatureFolderNotFoundAtGettingModelIfFeatureFolderWasNotSetAndNewDirDoesNotExistsAndManagerIsConst)
{
  const string DIR_NAME = "new-model";
  const QString DIR_PATH = "feature-folder-record-dir-manager/new-model";

  BOOST_REQUIRE(!QDir(DIR_PATH).exists());
  const RecordDirManager manager;
  BOOST_REQUIRE_THROW(manager.getModelDir(DIR_NAME), FeatureFolderNotFound);
}

BOOST_AUTO_TEST_CASE(removeEmptyModelDirIfFeatureFolderExists)
{
  const string DIR_TO_REMOVE = "model1";
  const QString FEATURE_FOLDER_PATH("feature-folder-record-dir-manager"),
      DIR_TO_REMOVE_PATH = "feature-folder-record-dir-manager/model1";

  BOOST_REQUIRE(QDir(FEATURE_FOLDER_PATH).exists());
  BOOST_REQUIRE(QDir(DIR_TO_REMOVE_PATH).exists());

  RecordDirManager manager;
  BOOST_REQUIRE_NO_THROW(manager.setFeatureFolder(FEATURE_FOLDER_PATH));

  BOOST_REQUIRE_NO_THROW(manager.removeModelDir(DIR_TO_REMOVE));
  BOOST_REQUIRE(!QDir(DIR_TO_REMOVE.c_str()).exists());
  //sprzątanie
  BOOST_CHECK(QDir(FEATURE_FOLDER_PATH).mkdir(DIR_TO_REMOVE.c_str()));
}

BOOST_AUTO_TEST_CASE(removeNotEmptyModelDirIfFeatureFolderExists)
{
  const string DIR_TO_REMOVE = "model1";
  const QString FEATURE_FOLDER_PATH("feature-folder-record-dir-manager"),
      DIR_TO_REMOVE_PATH = "feature-folder-record-dir-manager/model1",
      FILE_IN_REMOVE_DIR = "record1.mp3",
      FILE_IN_REMOVE_DIR_PATH = DIR_TO_REMOVE_PATH + "/" + FILE_IN_REMOVE_DIR;

  BOOST_REQUIRE(QDir(FEATURE_FOLDER_PATH).exists());
  BOOST_REQUIRE(QDir(DIR_TO_REMOVE_PATH).exists());
  BOOST_REQUIRE(QFile(FILE_IN_REMOVE_DIR_PATH).open(QFile::ReadWrite));

  RecordDirManager manager;
  BOOST_REQUIRE_NO_THROW(manager.setFeatureFolder(FEATURE_FOLDER_PATH));

  BOOST_REQUIRE_NO_THROW(manager.removeModelDir(DIR_TO_REMOVE));
  BOOST_REQUIRE(!QDir(DIR_TO_REMOVE_PATH).exists());
  //sprzątanie
  BOOST_CHECK(QDir(FEATURE_FOLDER_PATH).mkdir(DIR_TO_REMOVE.c_str()));
}

BOOST_AUTO_TEST_CASE(throwFeatureFolderNotFoundAtRemovingIfFeatureFolderWasNotSet)
{
  const string DIR_TO_REMOVE = "model1";
  RecordDirManager manager;
  BOOST_REQUIRE_THROW(manager.removeModelDir(DIR_TO_REMOVE), FeatureFolderNotFound);
}

BOOST_AUTO_TEST_CASE(getAllRecordDirsIfFeatureFolderExists)
{
  const QString FEATURE_FOLDER_PATH("feature-folder-record-dir-manager"),
      DIR_TO_REMOVE_PATH = "feature-folder-record-dir-manager/model1";
  const uint32_t DIRS_CNT = 2;
  BOOST_REQUIRE(QDir(FEATURE_FOLDER_PATH).exists());

  RecordDirManager manager;
  BOOST_REQUIRE_NO_THROW(manager.setFeatureFolder(FEATURE_FOLDER_PATH));
  vector<RecordDir> dirs;
  BOOST_REQUIRE_NO_THROW(dirs = manager.getAllDirs());
  BOOST_REQUIRE_EQUAL(dirs.size(), DIRS_CNT);
  BOOST_CHECK((dirs[0]).exists());
  BOOST_CHECK((dirs[1]).exists());
}

BOOST_AUTO_TEST_CASE(throwFeatureFolderNotFoundAtGettingAllDirsIfFeatureFolderWasNotSet)
{

  RecordDirManager manager;
  BOOST_REQUIRE_THROW(manager.getAllDirs(), FeatureFolderNotFound);
}





BOOST_AUTO_TEST_SUITE_END()
