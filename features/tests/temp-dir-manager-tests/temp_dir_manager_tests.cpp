#include "temp_dir_manager_tests.hpp"


using namespace std;
using namespace alize;
using namespace boost;

BOOST_AUTO_TEST_SUITE( TempDirManagerTest )



BOOST_AUTO_TEST_CASE(setFeatureFolderIfFeatureFolderExists)
{
  const QString FEATURE_FOLDER_PATH("feature-folder-temp-dir-manager");
  BOOST_REQUIRE(QDir(FEATURE_FOLDER_PATH).exists());
  TempDirManager manager;
  BOOST_CHECK_NO_THROW(manager.setFeatureFolder(FEATURE_FOLDER_PATH));
}

BOOST_AUTO_TEST_CASE(throwDirNotFoundAdSettingFeatureFolderIfFeatureFolderDoesNotExists)
{
  const QString FEATURE_FOLDER_PATH("fake-folder");
  BOOST_REQUIRE(!QDir(FEATURE_FOLDER_PATH).exists());
  TempDirManager manager;
  BOOST_CHECK_THROW(manager.setFeatureFolder(FEATURE_FOLDER_PATH), FeatureFolderNotFound);
}

BOOST_AUTO_TEST_CASE(checkExistanceOfTempDirIfThisOneExists)
{
  const QString FEATURE_FOLDER_PATH("feature-folder-temp-dir-manager");
  BOOST_REQUIRE(QDir(FEATURE_FOLDER_PATH).exists());
  TempDirManager manager;
  BOOST_REQUIRE(QDir(FEATURE_FOLDER_PATH).mkdir(manager.TEMP_DIR_NAME));

  BOOST_CHECK_NO_THROW(manager.setFeatureFolder(FEATURE_FOLDER_PATH));

  BOOST_CHECK(manager.isDirExists());
  //sprzątanie
  if(QDir(FEATURE_FOLDER_PATH + "/" + manager.TEMP_DIR_NAME).exists())
  {
    BOOST_CHECK(QDir(FEATURE_FOLDER_PATH).rmdir(manager.TEMP_DIR_NAME));
  }
}

BOOST_AUTO_TEST_CASE(checkExistanceOfTempDirIfThisOneDoesNotExists)
{
  const QString FEATURE_FOLDER_PATH("feature-folder-temp-dir-manager");
  BOOST_REQUIRE(QDir(FEATURE_FOLDER_PATH).exists());
  TempDirManager manager;
  BOOST_REQUIRE(!QDir(FEATURE_FOLDER_PATH + "/" + manager.TEMP_DIR_NAME).exists());
  BOOST_REQUIRE_NO_THROW(manager.setFeatureFolder(FEATURE_FOLDER_PATH));

  BOOST_CHECK(!manager.isDirExists());
}

BOOST_AUTO_TEST_CASE(throwFeatureFolderNotFoundAtCheckingExistanceOfTempDirIfFeatureFolderWasNotSet)
{
  TempDirManager manager;
  BOOST_CHECK_THROW(manager.isDirExists(), FeatureFolderNotFound);
}

BOOST_AUTO_TEST_CASE(getCorrectlyTempDirIFeatureFolderWasSetAndTempDirDoesNotExists)
{
  const QString FEATURE_FOLDER_PATH("feature-folder-temp-dir-manager");
  BOOST_REQUIRE(QDir(FEATURE_FOLDER_PATH).exists());
  TempDirManager manager;
  BOOST_REQUIRE(!QDir(FEATURE_FOLDER_PATH + "/" + manager.TEMP_DIR_NAME).exists());

  manager.setFeatureFolder(FEATURE_FOLDER_PATH);

  BOOST_REQUIRE_NO_THROW(auto temp_dir = manager.getTempDir());
  BOOST_REQUIRE(QDir(FEATURE_FOLDER_PATH + "/" + manager.TEMP_DIR_NAME).exists());
  auto temp_dir = manager.getTempDir();
  BOOST_CHECK(temp_dir.exists());

  //sprzątanie
  BOOST_CHECK(QDir(FEATURE_FOLDER_PATH).rmdir(manager.TEMP_DIR_NAME));

}


BOOST_AUTO_TEST_CASE(getCorrectlyTempDirIFeatureFolderWasSetAndTempDirExists)
{
  const QString FEATURE_FOLDER_PATH("feature-folder-temp-dir-manager");
  BOOST_REQUIRE(QDir(FEATURE_FOLDER_PATH).exists());
  TempDirManager manager;
  BOOST_REQUIRE(QDir(FEATURE_FOLDER_PATH).mkdir(manager.TEMP_DIR_NAME));

  manager.setFeatureFolder(FEATURE_FOLDER_PATH);

  BOOST_REQUIRE_NO_THROW(auto temp_dir = manager.getTempDir());
  BOOST_REQUIRE(QDir(FEATURE_FOLDER_PATH + "/" + manager.TEMP_DIR_NAME).exists());
  auto temp_dir = manager.getTempDir();
  BOOST_CHECK(temp_dir.exists());

  //sprzątanie
  BOOST_CHECK(QDir(FEATURE_FOLDER_PATH).rmdir(manager.TEMP_DIR_NAME));

}

BOOST_AUTO_TEST_CASE(throwFeatureFolderNotFoundAtgettingTempDirIfFeatureFolderWasNotSet)
{
  TempDirManager manager;
  BOOST_REQUIRE_THROW(auto temp_dir = manager.getTempDir(), FeatureFolderNotFound);
}

BOOST_AUTO_TEST_CASE(getCorrectlyTempDirIFeatureFolderWasSetAndTempDirExistsAndManagerIsConst)
{
  const QString FEATURE_FOLDER_PATH("feature-folder-temp-dir-manager");
  BOOST_REQUIRE(QDir(FEATURE_FOLDER_PATH).exists());
  TempDirManager manager;
  BOOST_REQUIRE(QDir(FEATURE_FOLDER_PATH).mkdir(manager.TEMP_DIR_NAME));

  manager.setFeatureFolder(FEATURE_FOLDER_PATH);

  BOOST_REQUIRE_NO_THROW(auto temp_dir = static_cast<const TempDirManager>(manager).getTempDir());
  BOOST_REQUIRE(QDir(FEATURE_FOLDER_PATH + "/" + manager.TEMP_DIR_NAME).exists());
  auto temp_dir = static_cast<const TempDirManager>(manager).getTempDir();
  BOOST_CHECK(temp_dir.exists());

  //sprzątanie
  BOOST_CHECK(QDir(FEATURE_FOLDER_PATH).rmdir(manager.TEMP_DIR_NAME));

}

BOOST_AUTO_TEST_CASE(throwDirNotFoundAtGettingTempDirIfManagerIsConstAndFeatureFolderWasSetAndTempDirDoesNotExists)
{
  const QString FEATURE_FOLDER_PATH("feature-folder-temp-dir-manager");
  BOOST_REQUIRE(QDir(FEATURE_FOLDER_PATH).exists());
  TempDirManager manager;
  BOOST_REQUIRE(!QDir(FEATURE_FOLDER_PATH + "/" + manager.TEMP_DIR_NAME).exists());

  manager.setFeatureFolder(FEATURE_FOLDER_PATH);

  BOOST_REQUIRE_THROW(auto temp_dir = static_cast<const TempDirManager>(manager).getTempDir(), DirNotFound);
  if(QDir(FEATURE_FOLDER_PATH + "/" + manager.TEMP_DIR_NAME).exists())
  {
    //sprzątanie
    BOOST_CHECK(QDir(FEATURE_FOLDER_PATH).rmdir(manager.TEMP_DIR_NAME));
  }


}

BOOST_AUTO_TEST_CASE(throwFeatureFolderNotFoundAtgettingTempDirIfFeatureFolderWasNotSetAndManagerIsConst)
{
  const TempDirManager manager;
  BOOST_REQUIRE_THROW(auto temp_dir = manager.getTempDir(), FeatureFolderNotFound);
}



BOOST_AUTO_TEST_SUITE_END()
