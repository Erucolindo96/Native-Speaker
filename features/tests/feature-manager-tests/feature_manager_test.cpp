#include "feature_manager_test.hpp"
using namespace std;
using namespace alize;
using namespace boost;

BOOST_AUTO_TEST_SUITE( FeatureManagerTest )


BOOST_AUTO_TEST_CASE(initialization)
{
  const QString FEATURE_FOLDER_PATH("feature-folder-feature-manager");
  if(!QDir(FEATURE_FOLDER_PATH).exists())
  {
    BOOST_CHECK(QDir(".").mkdir(FEATURE_FOLDER_PATH));
  }
}

BOOST_AUTO_TEST_CASE(setFeatureFolderIfFeatureFolderExists)
{
  const QString FEATURE_FOLDER_PATH("feature-folder-feature-manager");
  BOOST_REQUIRE(QDir(FEATURE_FOLDER_PATH).exists());
  FeatureManager manager;
  BOOST_CHECK_NO_THROW(manager.setFeatureFolder(FEATURE_FOLDER_PATH));
  BOOST_CHECK_EQUAL(manager.getFeatureFolder().toStdString(),
                    FEATURE_FOLDER_PATH.toStdString());
}

BOOST_AUTO_TEST_CASE(throwFeatureFolderNotFoundAdSettingFeatureFolderIfFeatureFolderDoesNotExists)
{
  const QString FEATURE_FOLDER_PATH("fake-folder");
  BOOST_REQUIRE(!QDir(FEATURE_FOLDER_PATH).exists());
  FeatureManager manager;
  BOOST_CHECK_THROW(manager.setFeatureFolder(FEATURE_FOLDER_PATH), FeatureFolderNotFound);
}

BOOST_AUTO_TEST_CASE(correctlyConvertWavFileIfConverterExistsAndFeatureReaderWasSetAndRecordExistsAndFeatureFolderWasSet)
{
  const QString FEATURE_FOLDER_PATH("feature-folder-feature-manager"),
      RECORD_PATH = "samples-feature-manager/wav/janfigat1_2-01.wav",
      RECORD_NAME = "janfigat1_2-01.wav";
  const uint32_t F_CNT  = 241, F_SIZE = 19;
  BOOST_REQUIRE(QDir(FEATURE_FOLDER_PATH).exists());
  BOOST_REQUIRE(QFileInfo(RECORD_PATH).exists());

  FeatureManager manager;
  BOOST_CHECK_NO_THROW(manager.setFeatureFolder(FEATURE_FOLDER_PATH));
  Record r;
  r.setPath(RECORD_PATH);
  std::vector<alize::Feature> vec;
  BOOST_REQUIRE_NO_THROW(vec = manager.convertRecord(r,F_SIZE, make_unique<FeatureReader>()));
  BOOST_CHECK_EQUAL(vec.size(), F_CNT);
  BOOST_CHECK_EQUAL((vec[0]).getVectSize(), F_SIZE);//log energii

  //sprzątanie
  TempDirManager temp;
  QDir temp_dir(FEATURE_FOLDER_PATH + "/" + temp.TEMP_DIR_NAME);
  temp_dir.setFilter(QDir::NoDotAndDotDot | QDir::AllEntries);
  for(auto file: temp_dir.entryInfoList())
  {
    BOOST_CHECK(temp_dir.remove(file.fileName()));
  }

}


BOOST_AUTO_TEST_CASE(correctlyConvertWavFileIfConverterExistsAndFeatureReaderWasNotSetAndRecordExistsAndFeatureFolderWasSet)
{
  const QString FEATURE_FOLDER_PATH("feature-folder-feature-manager"),
      RECORD_PATH = "samples-feature-manager/wav/janfigat1_2-01.wav",
      RECORD_NAME = "janfigat1_2-01.wav";
  const uint32_t F_CNT  = 241, F_SIZE = 9;
  BOOST_REQUIRE(QDir(FEATURE_FOLDER_PATH).exists());
  BOOST_REQUIRE(QFileInfo(RECORD_PATH).exists());

  FeatureManager manager;
  BOOST_CHECK_NO_THROW(manager.setFeatureFolder(FEATURE_FOLDER_PATH));

  Record r;
  r.setPath(RECORD_PATH);
  std::vector<alize::Feature> vec;
  BOOST_REQUIRE_NO_THROW(vec = manager.convertRecord(r, F_SIZE));
  BOOST_CHECK_EQUAL(vec.size(), F_CNT);
  BOOST_CHECK_EQUAL((vec[0]).getVectSize(), F_SIZE);//log energii

  //sprzątanie
  TempDirManager temp;
  QDir temp_dir(FEATURE_FOLDER_PATH + "/" + temp.TEMP_DIR_NAME);
  temp_dir.setFilter(QDir::NoDotAndDotDot | QDir::AllEntries);
  for(auto file: temp_dir.entryInfoList())
  {
    BOOST_CHECK(temp_dir.remove(file.fileName()));
  }

}

BOOST_AUTO_TEST_CASE(throwFeatureFolderNotFoundAtConvertingWavFileIfFeatureFolderWasNotSetAndConverterExistsAndRecordExists)
{
  const QString FEATURE_FOLDER_PATH("feature-folder-feature-manager"),
      RECORD_PATH = "samples-feature-manager/wav/janfigat1_2-01.wav",
      RECORD_NAME = "janfigat1_2-01.wav";

  BOOST_REQUIRE(QDir(FEATURE_FOLDER_PATH).exists());
  BOOST_REQUIRE(QFileInfo(RECORD_PATH).exists());

  FeatureManager manager;

  Record r;
  r.setPath(RECORD_PATH);
  const uint32_t F_SIZE = 8;
  BOOST_REQUIRE_THROW(manager.convertRecord(r, F_SIZE), FeatureFolderNotFound);

}

BOOST_AUTO_TEST_CASE(throwFileNotFoundAtConvertingWavFileIfFeatureFolderWasSetAndRecordDoesNotExists)
{
  const QString FEATURE_FOLDER_PATH("feature-folder-feature-manager"),
      RECORD_PATH = "fake-path";

  BOOST_REQUIRE(QDir(FEATURE_FOLDER_PATH).exists());
  FeatureManager manager;
  BOOST_CHECK_NO_THROW(manager.setFeatureFolder(FEATURE_FOLDER_PATH));

  Record r;
  const uint32_t F_SIZE = 8;
  BOOST_REQUIRE_THROW(manager.convertRecord(r, F_SIZE), FileNotFound);

}

BOOST_AUTO_TEST_CASE(throwUnableToConvertToMfccAtConvertingNotSupportedIfFeatureFolderWasSet)
{
  const QString FEATURE_FOLDER_PATH("feature-folder-feature-manager"),
      RECORD_PATH = "samples-feature-manager/mfcc/file.txt",
      RECORD_PATH2 = "samples-feature-manager/mfcc/file";

  BOOST_REQUIRE(QDir(FEATURE_FOLDER_PATH).exists());
  BOOST_REQUIRE(QFileInfo(RECORD_PATH).exists());
  BOOST_REQUIRE(QFileInfo(RECORD_PATH2).exists());

  FeatureManager manager;
  BOOST_CHECK_NO_THROW(manager.setFeatureFolder(FEATURE_FOLDER_PATH));

  Record r;
  r.setPath(RECORD_PATH);
    const uint32_t F_SIZE = 20;
  BOOST_REQUIRE_THROW(manager.convertRecord(r, F_SIZE), UnableToConvertToMfcc);
  r.setPath(RECORD_PATH2);
  BOOST_REQUIRE_THROW(manager.convertRecord(r, F_SIZE), UnableToConvertToMfcc);

}


BOOST_AUTO_TEST_CASE(correctlyConvertTwoWavFileIfConverterExistsAndFeatureReaderWasSetAndRecordExistsAndFeatureFolderWasSet)
{
  const QString FEATURE_FOLDER_PATH("feature-folder-feature-manager"),
      RECORD_PATH = "samples-feature-manager/wav/janfigat1_2-01.wav",
      RECORD_PATH2 = "samples-feature-manager/wav/kasprzak10_3-01.wav";

  const uint32_t F_CNT = 523, F_SIZE = 17;
  BOOST_REQUIRE(QDir(FEATURE_FOLDER_PATH).exists());
  BOOST_REQUIRE(QFileInfo(RECORD_PATH).exists());
  BOOST_REQUIRE(QFileInfo(RECORD_PATH2).exists());

  FeatureManager manager;
  BOOST_CHECK_NO_THROW(manager.setFeatureFolder(FEATURE_FOLDER_PATH));
  Record r1, r2;
  r1.setPath(RECORD_PATH);
  r2.setPath(RECORD_PATH2);
  std::vector<Record> recs = {r1, r2};
  std::vector<alize::Feature> vec;
  BOOST_REQUIRE_NO_THROW(vec = manager.convertRecord(recs,F_SIZE, make_unique<FeatureReader>()));
  BOOST_CHECK_EQUAL(vec.size(), F_CNT);
  BOOST_CHECK_EQUAL((vec[0]).getVectSize(), F_SIZE);//log energii
  TempDirManager temp;
  //sprzątanie
  QDir temp_dir(FEATURE_FOLDER_PATH + "/" + temp.TEMP_DIR_NAME);
  temp_dir.setFilter(QDir::NoDotAndDotDot | QDir::AllEntries);
  for(auto file: temp_dir.entryInfoList())
  {
    BOOST_CHECK(temp_dir.remove(file.fileName()));
  }

}


BOOST_AUTO_TEST_CASE(correctlyConvertTwoWavFileIfConverterExistsAndFeatureReaderWasNotSetAndRecordExistsAndFeatureFolderWasSet)
{
  const QString FEATURE_FOLDER_PATH("feature-folder-feature-manager"),
      RECORD_PATH = "samples-feature-manager/wav/janfigat1_2-01.wav",
      RECORD_PATH2 = "samples-feature-manager/wav/kasprzak10_3-01.wav";

  const uint32_t F_CNT  = 523, F_SIZE = 5;
  BOOST_REQUIRE(QDir(FEATURE_FOLDER_PATH).exists());
  BOOST_REQUIRE(QFileInfo(RECORD_PATH).exists());
  BOOST_REQUIRE(QFileInfo(RECORD_PATH2).exists());

  FeatureManager manager;
  BOOST_CHECK_NO_THROW(manager.setFeatureFolder(FEATURE_FOLDER_PATH));

  Record r1, r2;
  r1.setPath(RECORD_PATH);
  r2.setPath(RECORD_PATH2);
  std::vector<Record> recs = {r1,r2};
  std::vector<alize::Feature> vec;
  BOOST_REQUIRE_NO_THROW(vec = manager.convertRecord(recs, F_SIZE));
  BOOST_CHECK_EQUAL(vec.size(), F_CNT);
  BOOST_CHECK_EQUAL((vec[0]).getVectSize(), F_SIZE);//log energii
  TempDirManager temp;
  //sprzątanie
  QDir temp_dir(FEATURE_FOLDER_PATH + "/" + temp.TEMP_DIR_NAME);
  temp_dir.setFilter(QDir::NoDotAndDotDot | QDir::AllEntries);
  for(auto file: temp_dir.entryInfoList())
  {
    BOOST_CHECK(temp_dir.remove(file.fileName()));
  }

}


BOOST_AUTO_TEST_CASE(throwFeatureFolderNotFoundAtConvertingTwoWavFilesIfFeatureFolderWasNotSetAndConverterExistsAndRecordExists)
{
  const QString FEATURE_FOLDER_PATH("feature-folder-feature-manager"),
      RECORD_PATH = "samples-feature-manager/wav/janfigat1_2-01.wav",
      RECORD_PATH2 =  "samples-feature-manager/wav/kasprzak10_3-01.wav";

  BOOST_REQUIRE(QDir(FEATURE_FOLDER_PATH).exists());
  BOOST_REQUIRE(QFileInfo(RECORD_PATH).exists());
  BOOST_REQUIRE(QFileInfo(RECORD_PATH2).exists());

  FeatureManager manager;

  Record r1,r2;
  r1.setPath(RECORD_PATH);
  r2.setPath(RECORD_PATH2);
  std::vector<Record> recs = {r1,r2};
    const uint32_t F_SIZE = 8;
  BOOST_REQUIRE_THROW(manager.convertRecord(recs, F_SIZE), FeatureFolderNotFound);

}

BOOST_AUTO_TEST_CASE(throwFileNotFoundAtConvertingTwoWavFilesIfFeatureFolderWasSetAndOneRecordDoesNotExists)
{
  const QString FEATURE_FOLDER_PATH("feature-folder-feature-manager"),
      RECORD_PATH = "samples-feature-manager/wav/janfigat1_2-01.wav";

  BOOST_REQUIRE(QDir(FEATURE_FOLDER_PATH).exists());
  BOOST_REQUIRE(QFileInfo(RECORD_PATH).exists());

  FeatureManager manager;
  BOOST_CHECK_NO_THROW(manager.setFeatureFolder(FEATURE_FOLDER_PATH));


  Record r1,r2;
  r1.setPath(RECORD_PATH);
    const uint32_t F_SIZE = 8;
  BOOST_REQUIRE_THROW(manager.convertRecord({r1,r2}, F_SIZE), FileNotFound);
  BOOST_REQUIRE_THROW(manager.convertRecord({r2,r1}, F_SIZE), FileNotFound);

}

BOOST_AUTO_TEST_CASE(throwUnableToConvertToMfccAtConvertingTwoFileWhickOneIsNotSupportedFilesIfFeatureFolderWasSet)
{
  const QString FEATURE_FOLDER_PATH("feature-folder-feature-manager"),
      RECORD_PATH = "samples-feature-manager/mfcc/file.txt",
      RECORD_PATH2 =  "samples-feature-manager/wav/kasprzak10_3-01.wav";

  BOOST_REQUIRE(QDir(FEATURE_FOLDER_PATH).exists());
  BOOST_REQUIRE(QFileInfo(RECORD_PATH).exists());
  BOOST_REQUIRE(QFileInfo(RECORD_PATH2).exists());

  FeatureManager manager;
  BOOST_CHECK_NO_THROW(manager.setFeatureFolder(FEATURE_FOLDER_PATH));

  Record r1, r2;
  r1.setPath(RECORD_PATH);
  r2.setPath(RECORD_PATH2);

    const uint32_t F_SIZE = 8;
  BOOST_REQUIRE_THROW(manager.convertRecord({r1,r2}, F_SIZE), UnableToConvertToMfcc);
  BOOST_REQUIRE_THROW(manager.convertRecord({r2,r1}, F_SIZE), UnableToConvertToMfcc);


}

BOOST_AUTO_TEST_CASE(correctlyCleanTempDirFromFilesIfTheyAreMoreThan1AndFeatureFolderWasSet)
{
  TempDirManager temp;
  const QString FEATURE_FOLDER_PATH("feature-folder-feature-manager"),
      TEMP_FILE_PATH = FEATURE_FOLDER_PATH + "/" + temp.TEMP_DIR_NAME + "/file1.mfcc",
      TEMP_FILE_PATH2 =  FEATURE_FOLDER_PATH + "/" + temp.TEMP_DIR_NAME + "/file1.wav",
      TEMP_FILE_PATH3 =  FEATURE_FOLDER_PATH + "/" + temp.TEMP_DIR_NAME + "/file2.txt"
      ;

  BOOST_REQUIRE(QDir(FEATURE_FOLDER_PATH).exists());
  //BOOST_REQUIRE(QDir(FEATURE_FOLDER_PATH).mkdir(temp.TEMP_DIR_NAME));
  BOOST_REQUIRE(QFile(TEMP_FILE_PATH).open(QFile::ReadWrite));
  BOOST_REQUIRE(QFile(TEMP_FILE_PATH2).open(QFile::ReadWrite));
  BOOST_REQUIRE(QFile(TEMP_FILE_PATH3).open(QFile::ReadWrite));

  FeatureManager manager;
  BOOST_REQUIRE_NO_THROW(manager.setFeatureFolder(FEATURE_FOLDER_PATH));

  BOOST_CHECK_NO_THROW(manager.clean());
  QDir temp_dir(FEATURE_FOLDER_PATH + "/" + temp.TEMP_DIR_NAME);
  temp_dir.setFilter(QDir::NoDotAndDotDot | QDir::AllEntries);
  BOOST_CHECK(temp_dir.exists());
  BOOST_CHECK(temp_dir.entryInfoList().empty());

  //sprzątanie
  if(!temp_dir.entryInfoList().empty())
  {
    for(auto file:temp_dir.entryInfoList())
    {
      temp_dir.remove(file.fileName());
    }
  }
  BOOST_CHECK(QDir(FEATURE_FOLDER_PATH).rmdir(temp.TEMP_DIR_NAME));
}

BOOST_AUTO_TEST_CASE(throwFeatureFolderNotFoundAtCleaningTempDirIfFeatureFolderWasNotSet)
{
  FeatureManager manager;
  BOOST_CHECK_THROW(manager.clean(), FeatureFolderNotFound);
}



BOOST_AUTO_TEST_SUITE_END()

