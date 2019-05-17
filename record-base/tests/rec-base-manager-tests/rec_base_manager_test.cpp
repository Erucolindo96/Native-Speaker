#include "rec_base_manager_test.hpp"

using namespace std;
using namespace alize;
using namespace boost;

BOOST_AUTO_TEST_SUITE( RecBaseManagerTests )

BOOST_AUTO_TEST_CASE(correctlySetFeatureFolderPathIfPathPointToRealDir)
{
  const QString FEATURE_FOLDER_PATH = "feature-folder-rec-base-manager";
  BOOST_REQUIRE(QDir(FEATURE_FOLDER_PATH).exists());
  RecBaseManager manager;
  BOOST_CHECK_NO_THROW(manager.setFeatureFolderPath(FEATURE_FOLDER_PATH));
  BOOST_CHECK_EQUAL(manager.getFeatureFolderPath().toStdString(),
                    FEATURE_FOLDER_PATH.toStdString());
}

BOOST_AUTO_TEST_CASE(throwFeatureFolderNotFoundAtSettingPathIfPathDoesNotPointToRealDir)
{
  const QString FEATURE_FOLDER_PATH = "fake-folder";
  BOOST_REQUIRE(!QDir(FEATURE_FOLDER_PATH).exists());
  RecBaseManager manager;
  BOOST_CHECK_THROW(manager.setFeatureFolderPath(FEATURE_FOLDER_PATH), FeatureFolderNotFound);
  BOOST_CHECK_EQUAL(manager.getFeatureFolderPath().toStdString(),
                    FEATURE_FOLDER_PATH.toStdString());
}

BOOST_AUTO_TEST_CASE(getAllRecordsOfModelIfModelDirExistsAndContainSomeFiles)
{
  const QString FEATURE_FOLDER_PATH = "feature-folder-rec-base-manager";
  const string MODEL_NAME = "model2", MODEL_PATH =
      FEATURE_FOLDER_PATH.toStdString() + "/" + MODEL_NAME;
  QDir model_dir(MODEL_PATH.c_str());
  model_dir.setFilter(QDir::NoDotAndDotDot|QDir::Files);
  int32_t RECS_CNT = 3;

  BOOST_REQUIRE(QDir(FEATURE_FOLDER_PATH).exists());
  BOOST_REQUIRE(model_dir.exists());
  BOOST_REQUIRE(model_dir.entryInfoList().size() == RECS_CNT);

  RecBaseManager manager;
  BOOST_REQUIRE_NO_THROW(manager.setFeatureFolderPath(FEATURE_FOLDER_PATH));

  BOOST_REQUIRE_NO_THROW(manager.getRecordsOfModel(MODEL_NAME));
  auto records = manager.getRecordsOfModel(MODEL_NAME);
  BOOST_REQUIRE_EQUAL(records.size(), RECS_CNT);
  BOOST_CHECK_EQUAL(records.at(0).getRecordInfo().fileName().toStdString(), "record1.mp3");
  BOOST_CHECK_EQUAL(records.at(1).getRecordInfo().fileName().toStdString(), "record2.wav");
  BOOST_CHECK_EQUAL(records.at(2).getRecordInfo().fileName().toStdString(), "record3.txt");
  //BOOST_CHECK_EQUAL(records.at(3).getRecordInfo().fileName().toStdString(), "record4");

}

BOOST_AUTO_TEST_CASE(throwFeatureFolderNotFoundAtListingModelRecordsIfFeatureFolderPathWasNotSet)
{
  RecBaseManager manager;
  BOOST_REQUIRE_THROW(manager.getRecordsOfModel("model1"), FeatureFolderNotFound);
}

BOOST_AUTO_TEST_CASE(setRecordToModelDirIfModelDirExistsAndNotContainSomeFiles)
{
  const QString FEATURE_FOLDER_PATH = "feature-folder-rec-base-manager",
      RECORD_NAME = "record1.mp3",
      RECORD_PATH = FEATURE_FOLDER_PATH + "/" + RECORD_NAME;
  const string MODEL_NAME = "model1", MODEL_PATH =
      FEATURE_FOLDER_PATH.toStdString() + "/" + MODEL_NAME;
  QDir model_dir(MODEL_PATH.c_str());
  model_dir.setFilter(QDir::NoDotAndDotDot|QDir::Files);

  BOOST_REQUIRE(QDir(FEATURE_FOLDER_PATH).exists());
  BOOST_REQUIRE(model_dir.exists());
  BOOST_REQUIRE(model_dir.entryInfoList().empty());
  BOOST_REQUIRE(QFileInfo(RECORD_PATH).exists());

  RecBaseManager manager;
  BOOST_REQUIRE_NO_THROW(manager.setFeatureFolderPath(FEATURE_FOLDER_PATH));

  Record r;
  r.setPath(RECORD_PATH);

  BOOST_REQUIRE_NO_THROW(manager.setRecordToBase(r, MODEL_NAME));
  model_dir.refresh();
  BOOST_REQUIRE_EQUAL(model_dir.entryInfoList().size(), 1);
  BOOST_CHECK_EQUAL(model_dir.entryInfoList().at(0).fileName().toStdString(),
                    RECORD_NAME.toStdString());

  //sprzątanie
  BOOST_CHECK(model_dir.remove(RECORD_NAME));
}


BOOST_AUTO_TEST_CASE(setRecordToModelDirIfModelDirDoesNotExists)
{
  const QString FEATURE_FOLDER_PATH = "feature-folder-rec-base-manager",
      RECORD_NAME = "record1.mp3",
      RECORD_PATH = FEATURE_FOLDER_PATH + "/" + RECORD_NAME;
  const string MODEL_NAME = "new-model", MODEL_PATH =
      FEATURE_FOLDER_PATH.toStdString() + "/" + MODEL_NAME;

  BOOST_REQUIRE(QDir(FEATURE_FOLDER_PATH).exists());
  BOOST_REQUIRE(!QDir(MODEL_PATH.c_str()).exists());
  BOOST_REQUIRE(QFileInfo(RECORD_PATH).exists());

  RecBaseManager manager;
  BOOST_REQUIRE_NO_THROW(manager.setFeatureFolderPath(FEATURE_FOLDER_PATH));

  Record r;
  r.setPath(RECORD_PATH);

  BOOST_REQUIRE_NO_THROW(manager.setRecordToBase(r, MODEL_NAME));

  QDir model_dir(MODEL_PATH.c_str());
  model_dir.setFilter(QDir::NoDotAndDotDot| QDir::Files);
  BOOST_REQUIRE(model_dir.exists());
  BOOST_REQUIRE_EQUAL(model_dir.entryInfoList().size(), 1);
  BOOST_CHECK_EQUAL(model_dir.entryInfoList().at(0).fileName().toStdString(),
                    RECORD_NAME.toStdString());
  //sprzątanie
  BOOST_CHECK(model_dir.remove(RECORD_NAME));
  BOOST_CHECK(QDir(FEATURE_FOLDER_PATH).rmdir(MODEL_NAME.c_str()));
}

BOOST_AUTO_TEST_CASE(setRecordToModelDirIfModelDirExistsAndContainsSomeFiles)
{
  const QString FEATURE_FOLDER_PATH = "feature-folder-rec-base-manager",
      RECORD_NAME = "record4",
      RECORD_PATH = FEATURE_FOLDER_PATH + "/" + RECORD_NAME;
  const string MODEL_NAME = "model2", MODEL_PATH =
      FEATURE_FOLDER_PATH.toStdString() + "/" + MODEL_NAME;
  QDir model_dir(MODEL_PATH.c_str());
  model_dir.setFilter(QDir::NoDotAndDotDot|QDir::Files);

  BOOST_REQUIRE(QDir(FEATURE_FOLDER_PATH).exists());
  BOOST_REQUIRE(model_dir.exists());
  BOOST_REQUIRE(!model_dir.entryInfoList().empty());
  BOOST_REQUIRE(!model_dir.entryList().contains(RECORD_NAME));
  BOOST_REQUIRE(QFileInfo(RECORD_PATH).exists());

  RecBaseManager manager;
  BOOST_REQUIRE_NO_THROW(manager.setFeatureFolderPath(FEATURE_FOLDER_PATH));

  Record r;
  r.setPath(RECORD_PATH);

  BOOST_REQUIRE_NO_THROW(manager.setRecordToBase(r, MODEL_NAME));
  uint32_t RECS_AFTER_SET = 4;
  model_dir.refresh();
  BOOST_REQUIRE_EQUAL(model_dir.entryInfoList().size(), RECS_AFTER_SET);
  BOOST_CHECK_EQUAL(model_dir.entryInfoList().at(3).fileName().toStdString(),
                    RECORD_NAME.toStdString());

  //sprzątanie
  BOOST_CHECK(model_dir.remove(RECORD_NAME));
}

BOOST_AUTO_TEST_CASE(throwFeatureFolderNotFoundAtSettingRecordIfFeatureFolderPathWasNotSetAndRecordExists)
{
  const QString FEATURE_FOLDER_PATH = "feature-folder-rec-base-manager",
      RECORD_NAME = "record4",
      RECORD_PATH = FEATURE_FOLDER_PATH + "/" + RECORD_NAME;

  Record r;
  r.setPath(RECORD_PATH);
  RecBaseManager manager;
  BOOST_REQUIRE_THROW(manager.setRecordToBase(r, "model1"), FeatureFolderNotFound);
}

BOOST_AUTO_TEST_CASE(throwFileNotFoundAtSettingRecordIfFeatureFolderPathWasSetAndRecordDoesNotExists)
{
  const QString FEATURE_FOLDER_PATH = "feature-folder-rec-base-manager";

  Record r;
  RecBaseManager manager;
  BOOST_REQUIRE_NO_THROW(manager.setFeatureFolderPath(FEATURE_FOLDER_PATH));
  BOOST_CHECK_THROW(manager.setRecordToBase(r, "model1"), FileNotFound);
}

BOOST_AUTO_TEST_CASE(checkExistanceOfRecordIfModelDirExistsAndContainsRecordAndQuerredRecordExists)
{
  const QString FEATURE_FOLDER_PATH = "feature-folder-rec-base-manager",
      RECORD_NAME = "record1.mp3",
      RECORD_PATH = FEATURE_FOLDER_PATH + "/" + RECORD_NAME;
  const string MODEL_NAME = "model2", MODEL_PATH =
      FEATURE_FOLDER_PATH.toStdString() + "/" + MODEL_NAME;
  QDir model_dir(MODEL_PATH.c_str());
  model_dir.setFilter(QDir::NoDotAndDotDot|QDir::Files);

  BOOST_REQUIRE(QDir(FEATURE_FOLDER_PATH).exists());
  BOOST_REQUIRE(model_dir.exists());
  BOOST_REQUIRE(!model_dir.entryInfoList().empty());
  BOOST_REQUIRE(model_dir.entryList().contains(RECORD_NAME));
  BOOST_REQUIRE(QFileInfo(RECORD_PATH).exists());

  RecBaseManager manager;
  BOOST_REQUIRE_NO_THROW(manager.setFeatureFolderPath(FEATURE_FOLDER_PATH));

  Record r;
  r.setPath(RECORD_PATH);
  BOOST_CHECK(manager.isRecordExists(r, MODEL_NAME));
}

BOOST_AUTO_TEST_CASE(checkExistanceOfRecordIfModelDirExistsAndNotContainsRecordAndQuerredRecordExists)
{
  const QString FEATURE_FOLDER_PATH = "feature-folder-rec-base-manager",
      RECORD_NAME = "record4",
      RECORD_PATH = FEATURE_FOLDER_PATH + "/" + RECORD_NAME;
  const string MODEL_NAME = "model2", MODEL_PATH =
      FEATURE_FOLDER_PATH.toStdString() + "/" + MODEL_NAME;
  QDir model_dir(MODEL_PATH.c_str());
  model_dir.setFilter(QDir::NoDotAndDotDot|QDir::Files);

  BOOST_REQUIRE(QDir(FEATURE_FOLDER_PATH).exists());
  BOOST_REQUIRE(model_dir.exists());
  BOOST_REQUIRE(!model_dir.entryInfoList().empty());
  BOOST_REQUIRE(!model_dir.entryList().contains(RECORD_NAME));
  BOOST_REQUIRE(QFileInfo(RECORD_PATH).exists());

  RecBaseManager manager;
  BOOST_REQUIRE_NO_THROW(manager.setFeatureFolderPath(FEATURE_FOLDER_PATH));

  Record r;
  r.setPath(RECORD_PATH);
  BOOST_CHECK(!manager.isRecordExists(r, MODEL_NAME));
}

BOOST_AUTO_TEST_CASE(checkExistanceOfRecordIfModelDirDoesNotExistsAndQuerredRecordExists)
{
  const QString FEATURE_FOLDER_PATH = "feature-folder-rec-base-manager",
      RECORD_NAME = "record4",
      RECORD_PATH = FEATURE_FOLDER_PATH + "/" + RECORD_NAME;
  const string MODEL_NAME = "new-model", MODEL_PATH =
      FEATURE_FOLDER_PATH.toStdString() + "/" + MODEL_NAME;
  QDir model_dir(MODEL_PATH.c_str());
  model_dir.setFilter(QDir::NoDotAndDotDot|QDir::Files);

  BOOST_REQUIRE(QDir(FEATURE_FOLDER_PATH).exists());
  BOOST_REQUIRE(!model_dir.exists());
  BOOST_REQUIRE(QFileInfo(RECORD_PATH).exists());

  RecBaseManager manager;
  BOOST_REQUIRE_NO_THROW(manager.setFeatureFolderPath(FEATURE_FOLDER_PATH));

  Record r;
  r.setPath(RECORD_PATH);
  BOOST_CHECK(!manager.isRecordExists(r, MODEL_NAME));

}

BOOST_AUTO_TEST_CASE(throwFileNotFoundAtCheckingExistanceOfRecordIfQuerredRecordDoesNotExistsAndModelDirExistsAndIsEmpty)
{
  const QString FEATURE_FOLDER_PATH = "feature-folder-rec-base-manager";
  const string MODEL_NAME = "model1", MODEL_PATH =
      FEATURE_FOLDER_PATH.toStdString() + "/" + MODEL_NAME;
  QDir model_dir(MODEL_PATH.c_str());
  model_dir.setFilter(QDir::NoDotAndDotDot|QDir::Files);

  BOOST_REQUIRE(QDir(FEATURE_FOLDER_PATH).exists());
  BOOST_REQUIRE(model_dir.exists());
  BOOST_REQUIRE(model_dir.entryInfoList().empty());

  RecBaseManager manager;
  BOOST_REQUIRE_NO_THROW(manager.setFeatureFolderPath(FEATURE_FOLDER_PATH));

  Record r;
  BOOST_CHECK_THROW(manager.isRecordExists(r, MODEL_NAME), FileNotFound);
}


BOOST_AUTO_TEST_CASE(throwFeatureFolderNotFoundAtCheckingExistanceOfRecordIfFeatureFolderWasNotSetAndQuerredRecordExists)
{
  const QString FEATURE_FOLDER_PATH = "feature-folder-rec-base-manager",
      RECORD_NAME = "record4",
      RECORD_PATH = FEATURE_FOLDER_PATH + "/" + RECORD_NAME;
  const string MODEL_NAME = "model1", MODEL_PATH =
      FEATURE_FOLDER_PATH.toStdString() + "/" + MODEL_NAME;

  BOOST_REQUIRE(QFileInfo(RECORD_PATH).exists());

  RecBaseManager manager;
  Record r;
  r.setPath(RECORD_PATH);
  BOOST_CHECK_THROW(manager.isRecordExists(r, MODEL_NAME), FeatureFolderNotFound);
}

BOOST_AUTO_TEST_CASE(correctlyGetModelDirPath)
{
  const QString FEATURE_FOLDER_PATH = "feature-folder-rec-base-manager",
      MODEL_NAME = "model1";
  BOOST_CHECK_EQUAL(RecBaseManager::getModelPath(MODEL_NAME, FEATURE_FOLDER_PATH).toStdString(),
                    (FEATURE_FOLDER_PATH + "/" + MODEL_NAME).toStdString());

}


BOOST_AUTO_TEST_SUITE_END()
