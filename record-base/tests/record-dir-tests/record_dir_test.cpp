#include "record_dir_test.hpp"

using namespace std;
using namespace alize;
using namespace boost;

class RecordDirMock: public RecordDir
{
public:
  RecordDirMock():RecordDir()
  {}
  RecordDirMock(const RecordDirMock &other) = default;
  RecordDirMock& operator=(const RecordDirMock &other) = default;
  RecordDirMock(RecordDirMock &&other) = default;
  RecordDirMock& operator=(RecordDirMock &&other) = default;

  void setDir(const QDir &dir)
  {
    RecordDir::setDir(dir);
  }

};

BOOST_AUTO_TEST_SUITE( RecordDirTests )

BOOST_AUTO_TEST_CASE(initialization)
{
  const QString RECORD_DIR = "record-dir";
  if(!QDir(RECORD_DIR).exists())
  {
    BOOST_CHECK(QDir(".").mkdir(RECORD_DIR));
  }
}



BOOST_AUTO_TEST_CASE(addRecordToDirIfDirExistsAndAddedRecordExists)
{
  const QString REC_PATH = "other-dir/record1.mp3",
      REC_DIR_PATH = "record-dir",
      REC_NAME = "record1.mp3";
  BOOST_REQUIRE(QDir(REC_DIR_PATH).exists());
  BOOST_REQUIRE(QFileInfo(REC_PATH).exists());

  RecordDirMock rec_dir;
  rec_dir.setDir(QDir(REC_DIR_PATH));
  Record rec;
  rec.setPath(REC_PATH);

  BOOST_REQUIRE_NO_THROW(rec_dir.addRecord(rec));
  BOOST_CHECK(QDir(REC_DIR_PATH).entryList().contains(REC_NAME));

  //sprzątanie
  BOOST_CHECK(QDir(REC_DIR_PATH).remove(REC_NAME));
}

BOOST_AUTO_TEST_CASE(throwFileNotFoundAtAddingRecordIfRecordIsNotAFile)
{
  const QString REC_DIR_PATH = "record-dir";
  BOOST_REQUIRE(QDir(REC_DIR_PATH).exists());

  RecordDirMock rec_dir;
  rec_dir.setDir(QDir(REC_DIR_PATH));
  Record rec;

  BOOST_CHECK_THROW(rec_dir.addRecord(rec), FileNotFound);
}

BOOST_AUTO_TEST_CASE(throwDirNotFoundAtAddingRecordIfDirRepresentedByClassDoesNotExists)
{
  const QString REC_PATH = "other-dir/record1.mp3",
      REC_DIR_PATH = "fake-record-dir",
      REC_NAME = "record1.mp3";
  BOOST_REQUIRE(!QDir(REC_DIR_PATH).exists());
  BOOST_REQUIRE(QFileInfo(REC_PATH).exists());

  RecordDirMock rec_dir;
  rec_dir.setDir(QDir(REC_DIR_PATH));
  Record rec;
  rec.setPath(REC_PATH);

  BOOST_CHECK_THROW(rec_dir.addRecord(rec), DirNotFound);
}


BOOST_AUTO_TEST_CASE(correctlyListRecordDirIfRecordDirExists)
{
  const QString REC_DIR_PATH = "other-dir";
  const string FIRST_FILE = "record1.mp3",
      SEC_FILE = "record2.wav", THIRTH_FILE = "record3.txt";
  const uint32_t FILES_IN_DIR = 3;
  BOOST_REQUIRE(QDir(REC_DIR_PATH).exists());

  RecordDirMock rec_dir;
  rec_dir.setDir(QDir(REC_DIR_PATH));
  std::vector<Record> rec_vec;

  BOOST_REQUIRE_NO_THROW(rec_vec = rec_dir.list());
  BOOST_REQUIRE_EQUAL(rec_vec.size(), FILES_IN_DIR);
  BOOST_CHECK_EQUAL(rec_vec[0].getRecordInfo().fileName().toStdString(), FIRST_FILE);
  BOOST_CHECK_EQUAL(rec_vec[1].getRecordInfo().fileName().toStdString(), SEC_FILE);
  BOOST_CHECK_EQUAL(rec_vec[2].getRecordInfo().fileName().toStdString(), THIRTH_FILE);

}

BOOST_AUTO_TEST_CASE(throwDirNotFoundAtListingDirIfRecordDirDoesNotExists)
{
  const QString REC_DIR_PATH = "fake-dir";
  BOOST_REQUIRE(!QDir(REC_DIR_PATH).exists());

  RecordDirMock rec_dir;
  rec_dir.setDir(QDir(REC_DIR_PATH));

  BOOST_CHECK_THROW(rec_dir.list(), DirNotFound);

}

BOOST_AUTO_TEST_CASE(checkExistanceOfRecordInDirIfRecordExistsInDirAndQueredRecordExistsInOtherDir)
{
  const QString REC_PATH = "other-dir/record1.mp3",
      REC_DIR_PATH = "record-dir",
      REC_NAME = "record1.mp3";
  BOOST_REQUIRE(QDir(REC_DIR_PATH).exists());
  BOOST_REQUIRE(QFileInfo(REC_PATH).exists());
  BOOST_REQUIRE(QFile(REC_DIR_PATH + "/" + REC_NAME).open(QFile::ReadWrite));

  RecordDirMock rec_dir;
  rec_dir.setDir(QDir(REC_DIR_PATH));
  Record rec;
  rec.setPath(REC_PATH);

  BOOST_REQUIRE_NO_THROW(rec_dir.haveRecord(rec));
  BOOST_CHECK(rec_dir.haveRecord(rec));

  //sprzątanie
  BOOST_CHECK(QDir(REC_DIR_PATH).remove(REC_NAME));
}

BOOST_AUTO_TEST_CASE(checkExistanceOfRecordInDirIfRecordNotExistsInDirAndQueredRecordExistsInOtherDir)
{
  const QString REC_PATH = "other-dir/record1.mp3",
      REC_DIR_PATH = "record-dir",
      REC_NAME = "record1.mp3";
  BOOST_REQUIRE(QDir(REC_DIR_PATH).exists());
  BOOST_REQUIRE(QFileInfo(REC_PATH).exists());

  RecordDirMock rec_dir;
  rec_dir.setDir(QDir(REC_DIR_PATH));
  Record rec;
  rec.setPath(REC_PATH);

  BOOST_REQUIRE_NO_THROW(rec_dir.haveRecord(rec));
  BOOST_CHECK(!rec_dir.haveRecord(rec));
}

BOOST_AUTO_TEST_CASE(throwFileNotFoundAtCheckingExistanceOfRecordInRecordDirExistsAndQueredRecordDoesNotExists)
{
  const QString REC_DIR_PATH = "record-dir",
      REC_NAME = "record1.mp3";
  BOOST_REQUIRE(QDir(REC_DIR_PATH).exists());

  RecordDirMock rec_dir;
  rec_dir.setDir(QDir(REC_DIR_PATH));

  Record rec;

  BOOST_REQUIRE_THROW(rec_dir.haveRecord(rec), FileNotFound);
}

BOOST_AUTO_TEST_CASE(throwDirNotFoundAtCheckingExistanceOfRecordInRecordDirDoesNotExistsAndQueredRecordExists)
{
  const QString REC_PATH = "other-dir/record1.mp3",
      REC_DIR_PATH = "fake-record-dir",
      REC_NAME = "record1.mp3";
  BOOST_REQUIRE(!QDir(REC_DIR_PATH).exists());
  BOOST_REQUIRE(QFileInfo(REC_PATH).exists());

  RecordDirMock rec_dir;
  rec_dir.setDir(QDir(REC_DIR_PATH));

  Record rec;
  rec.setPath(REC_PATH);

  BOOST_REQUIRE_THROW(rec_dir.haveRecord(rec), DirNotFound);
}

BOOST_AUTO_TEST_CASE(checkExistanceOfRecordDirIfDirDoesExists)
{
  const QString REC_DIR_PATH = "record-dir";

  BOOST_REQUIRE(QDir(REC_DIR_PATH).exists());

  RecordDirMock rec_dir;
  rec_dir.setDir(QDir(REC_DIR_PATH));

  BOOST_REQUIRE_NO_THROW(rec_dir.exists());
  BOOST_CHECK(rec_dir.exists());

}

BOOST_AUTO_TEST_CASE(checkExistanceOfRecordDirIfDirDoesNotExists)
{
  const QString REC_DIR_PATH = "fake-record-dir";

  BOOST_REQUIRE(!QDir(REC_DIR_PATH).exists());

  RecordDirMock rec_dir;
  rec_dir.setDir(QDir(REC_DIR_PATH));

  BOOST_REQUIRE_NO_THROW(rec_dir.exists());
  BOOST_CHECK(!rec_dir.exists());

}

BOOST_AUTO_TEST_CASE(checkExistanceOfRecordDirIfDirWasRemovedAtRuntime)
{
  const QString REC_DIR_PATH = "another-record-dir";

  BOOST_REQUIRE(!QDir(REC_DIR_PATH).exists());
  BOOST_REQUIRE(QDir(".").mkdir(REC_DIR_PATH));

  RecordDirMock rec_dir;
  rec_dir.setDir(QDir(REC_DIR_PATH));

  BOOST_CHECK(rec_dir.exists());
  BOOST_REQUIRE(QDir(".").rmdir(REC_DIR_PATH));
  BOOST_CHECK(!rec_dir.exists());

}





//BOOST_AUTO_TEST_CASE(removeAllFileInDirIfRecordDirExistsAndIsNotEmpty)
//{
//  const QString REC_DIR_PATH = "record-dir",
//      REC_NAME_1 = "record1.mp3", REC_NAME_2 = "record2.wav";
//  const uint32_t EMPTY_DIR_SIZE = 2;
//  BOOST_REQUIRE(QDir(REC_DIR_PATH).exists());
//  BOOST_REQUIRE_EQUAL(QDir(REC_DIR_PATH).entryList().size(), EMPTY_DIR_SIZE);
//  BOOST_REQUIRE(QFile(REC_DIR_PATH + "/" + REC_NAME_1).open(QFile::ReadWrite));
//  BOOST_REQUIRE(QFile(REC_DIR_PATH + "/" + REC_NAME_2).open(QFile::ReadWrite));

//  RecordDirMock rec_dir;
//  rec_dir.setDir(QDir(REC_DIR_PATH));

//  BOOST_REQUIRE_NO_THROW(rec_dir.removeAll());
//  BOOST_CHECK(!QDir(REC_DIR_PATH).entryList().contains(REC_NAME_1));
//  BOOST_CHECK(!QDir(REC_DIR_PATH).entryList().contains(REC_NAME_2));

//}

//BOOST_AUTO_TEST_CASE(throwDirNotFoundAtRemovingRecordsFromDirIfDirDoesNotExists)
//{
//  const QString REC_DIR_PATH = "fake-record-dir";
////      REC_NAME_1 = "record1.mp3", REC_NAME_2 = "record2.wav";
//  BOOST_REQUIRE(!QDir(REC_DIR_PATH).exists());

//  RecordDirMock rec_dir;
//  rec_dir.setDir(QDir(REC_DIR_PATH));

//  BOOST_CHECK_THROW(rec_dir.removeAll(), DirNotFound);

//}



BOOST_AUTO_TEST_SUITE_END()
