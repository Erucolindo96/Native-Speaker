#include "temp_dir_test.hpp"

class TempDirMock : public TempDir
{
public:
  TempDirMock() = default;
  TempDirMock(const TempDirMock &other) = default;
  TempDirMock& operator=(const TempDirMock &other) = default;
  TempDirMock(TempDirMock &&other) = default;
  TempDirMock& operator=(TempDirMock &&other) = default;

  ~TempDirMock() override = default;

  void setDir(const QDir &dir)
  {
    RecordDir::setDir(dir);
  }

  bool exists() const
  {
    return RecordDir::exists();
  }

};



BOOST_AUTO_TEST_SUITE( TempDirTests )


BOOST_AUTO_TEST_CASE(initialization)
{
  const QString DIR_PATH = "feature-folder-temp-dir/temp-dir",
      DIR_NAME = "temp-dir";
  QDir FEATURE_FOLDER("feature-folder-temp-dir");
  if(!QDir(DIR_PATH).exists())
  {
    BOOST_CHECK(FEATURE_FOLDER.mkdir(DIR_NAME));
  }
}

BOOST_AUTO_TEST_CASE(setInstanceOfFeatureReaderAndReturnThisInstanceIfDirWasSet)
{
  const QString DIR_PATH = "feature-folder-temp-dir/temp-dir";
  QDir temp_dir(DIR_PATH);
  BOOST_REQUIRE(temp_dir.exists());

  TempDirMock dir;
  dir.setDir(temp_dir);

  std::unique_ptr<FeatureReader> reader = make_unique<FeatureReader>();
  FeatureReader* addr = reader.get();

  BOOST_CHECK_NO_THROW(dir.setFeatureReader(std::move(reader)));
  BOOST_CHECK_EQUAL(dir.getFeatureReaderRef().get(), addr);
}

BOOST_AUTO_TEST_CASE(throwDirNotFoundAtSettinFeatureReaderIfDirWasNotSet)
{
  TempDirMock dir;

  std::unique_ptr<FeatureReader> reader = make_unique<FeatureReader>();

  BOOST_CHECK_THROW(dir.setFeatureReader(std::move(reader)), DirNotFound);
}

BOOST_AUTO_TEST_CASE(throwDirNotFoundAtGettingFeatureReaderIfDirWasNotSet)
{
  TempDirMock dir;
  BOOST_CHECK_THROW(dir.getFeatureReaderRef(), DirNotFound);
}

BOOST_AUTO_TEST_CASE(correctlyConvertRecordIfDirWasSetAndRecordIsWavAndFeatureReaderWasSet)
{
  const QString DIR_PATH = "feature-folder-temp-dir/temp-dir",
      RECORD_PATH = "feature-folder-temp-dir/other-dir/janfigat1_2-01.wav",
      RECORD_NAME = "janfigat1_2-01";
  QDir temp_dir(DIR_PATH);
  BOOST_REQUIRE(temp_dir.exists());
  BOOST_REQUIRE(QFileInfo(RECORD_PATH).exists());

  TempDirMock dir;
  dir.setDir(temp_dir);

  std::unique_ptr<FeatureReader> reader = make_unique<FeatureReader>();
  dir.setFeatureReader(std::move(reader));

  Record r;
  r.setPath(RECORD_PATH);

  const uint32_t F_CNT = 483;
  std::vector<alize::Feature> vec;
  BOOST_REQUIRE_NO_THROW(vec = dir.convertToMfcc(r));
  BOOST_CHECK_EQUAL(vec.size(), F_CNT);

  //sprzątanie
  BOOST_CHECK(temp_dir.remove(RECORD_NAME + ".mfcc"));
  BOOST_CHECK(temp_dir.remove(RECORD_NAME + ".wav"));


}


BOOST_AUTO_TEST_CASE(correctlyConvertRecordIfDirWasSetAndRecordIsWavAndFeatureReaderIsDefault)
{
  const QString DIR_PATH = "feature-folder-temp-dir/temp-dir",
      RECORD_PATH = "feature-folder-temp-dir/other-dir/janfigat1_2-01.wav",
      RECORD_NAME = "janfigat1_2-01";
  QDir temp_dir(DIR_PATH);
  BOOST_REQUIRE(temp_dir.exists());
  BOOST_REQUIRE(QFileInfo(RECORD_PATH).exists());

  TempDirMock dir;
  dir.setDir(temp_dir);

  Record r;
  r.setPath(RECORD_PATH);

  const uint32_t F_CNT = 483;
  std::vector<alize::Feature> vec;
  BOOST_REQUIRE_NO_THROW(vec = dir.convertToMfcc(r));
  BOOST_CHECK_EQUAL(vec.size(), F_CNT);

  //sprzątanie
  BOOST_CHECK(temp_dir.remove(RECORD_NAME + ".mfcc"));
  BOOST_CHECK(temp_dir.remove(RECORD_NAME + ".wav"));

}


BOOST_AUTO_TEST_CASE(throwDirNotFoundAtConvertingToMfccIfDirWasNotSetAndRecordIsWav)
{
  const QString RECORD_PATH = "feature-folder-temp-dir/other-dir/janfigat1_2-01.wav";

  BOOST_REQUIRE(QFileInfo(RECORD_PATH).exists());

  TempDirMock dir;

  Record r;
  r.setPath(RECORD_PATH);

  BOOST_REQUIRE_THROW(dir.convertToMfcc(r), DirNotFound);
}


BOOST_AUTO_TEST_CASE(throwFileNotFoundAtConvertingToMfccIfDirWasSetAndRecordDoesNotExists)
{
  const QString DIR_PATH = "feature-folder-temp-dir/temp-dir";

  QDir temp_dir(DIR_PATH);
  BOOST_REQUIRE(temp_dir.exists());

  TempDirMock dir;
  dir.setDir(temp_dir);

  Record r;
  BOOST_REQUIRE_THROW(dir.convertToMfcc(r), FileNotFound);
}

BOOST_AUTO_TEST_CASE(throwUnableToConvertToMfccAtConvertingToMfccIfDirWasSetAndRecordIsNotASupportedType)
{
  const QString DIR_PATH = "feature-folder-temp-dir/temp-dir",
      RECORD_PATH = "feature-folder-temp-dir/other-dir/janfigat1_2-01.txt",
      RECORD_NAME = "janfigat1_2-01";
  QDir temp_dir(DIR_PATH);
  BOOST_REQUIRE(temp_dir.exists());
  BOOST_REQUIRE(QFileInfo(RECORD_PATH).exists());

  TempDirMock dir;
  dir.setDir(temp_dir);

  Record r;
  r.setPath(RECORD_PATH);

  BOOST_REQUIRE_THROW(dir.convertToMfcc(r), UnableToConvertToMfcc);
}

BOOST_AUTO_TEST_CASE(CorrectlyCleanTempDirIfDirWasSetAndContainsSomeFiles)
{
  const QString DIR_PATH = "feature-folder-temp-dir/temp-dir",
      FILE1 = DIR_PATH + "/record1.wav",
      FILE2 = DIR_PATH + "/record2.mfcc",
      FILE3 = DIR_PATH + "/record4.txt";

  QDir temp_dir(DIR_PATH);
  temp_dir.setFilter(QDir::NoDotAndDotDot | QDir::AllEntries);

  BOOST_REQUIRE(temp_dir.exists());
  BOOST_REQUIRE(QFile(FILE1).open(QFile::ReadWrite));
  BOOST_REQUIRE(QFile(FILE2).open(QFile::ReadWrite));
  BOOST_REQUIRE(QFile(FILE3).open(QFile::ReadWrite));

  TempDirMock dir;
  dir.setDir(temp_dir);

  BOOST_CHECK_NO_THROW(dir.cleanDir());
  auto file_list = temp_dir.entryInfoList();
  BOOST_CHECK(file_list.empty());

  //sprzątanie
  if(!file_list.empty())
  {
      for(auto file:file_list)
      {
        temp_dir.remove(file.fileName());
      }
  }
  BOOST_CHECK(temp_dir.entryInfoList().empty());
}


BOOST_AUTO_TEST_CASE(throwDirNotFoundAtCleaningTempDirIfDirWasNotSet)
{
  TempDirMock dir;

  BOOST_CHECK_THROW(dir.cleanDir(), DirNotFound);
}




BOOST_AUTO_TEST_SUITE_END()
