#include "record_tests.hpp"

using namespace std;
using namespace alize;
using namespace boost;

BOOST_AUTO_TEST_SUITE( RecordTests )

BOOST_AUTO_TEST_CASE(initialization)
{
  QDir test_dir("feature-folder");
  const QString other_folder = "other_folder";

  if(!test_dir.entryList().contains(other_folder))
  {
    BOOST_CHECK(test_dir.mkdir(other_folder));
  }
}

BOOST_AUTO_TEST_CASE( throwFileNotFoundAtGetRecordInfoIfPathWasNotSet )
{
  Record r;
  BOOST_CHECK_THROW(r.getRecordInfo(), FileNotFound);
}


BOOST_AUTO_TEST_CASE( setPathIfPathPointToRealFile )
{
  const QString path = "feature-folder/record1.mp3", name = "record1.mp3";
  Record r;
  BOOST_REQUIRE_NO_THROW(r.setPath(path));
  BOOST_CHECK(r.getRecordInfo().fileName() == name);

}

BOOST_AUTO_TEST_CASE( throwFileNotFoundAtSetPathIfPathNotPointToRealFile )
{
  const QString path = "fake-folder/fake_file.mp3";//, name = "record1.mp3";
  Record r;
  BOOST_REQUIRE_THROW(r.setPath(path), FileNotFound);
}

BOOST_AUTO_TEST_CASE( setNameAndDirIfDirExistsAndFileExists )
{
  const QString name = "record1.mp3";
  QDir dir("feature-folder");
  Record r;
  BOOST_REQUIRE(dir.exists());
  BOOST_REQUIRE_NO_THROW(r.setPath(name, dir));
  BOOST_CHECK(r.getRecordInfo().fileName() == name);

}

BOOST_AUTO_TEST_CASE( throwFileNotFoundAtSetPathIfDirExistsAndFileNotExists )
{
  const QString  name = "fake-record1.mp3";
  QDir dir("feature-folder");
  Record r;
  BOOST_REQUIRE(dir.exists());

  BOOST_REQUIRE_THROW(r.setPath(name, dir), FileNotFound);
}

BOOST_AUTO_TEST_CASE( throwDirNotFoundAtSetPathIfDirNotExistsAndFileExists )
{
  const QString  name = "record1.mp3";
  QDir dir("fake-folder");
  Record r;
  BOOST_REQUIRE(!dir.exists());

  BOOST_REQUIRE_THROW(r.setPath(name, dir), DirNotFound);
}



BOOST_AUTO_TEST_CASE( checkExistanceOfRecordIfRecordExists )
{
  const QString path = "feature-folder/record1.mp3";
  QDir dir("feature-folder");
  Record r;
  BOOST_REQUIRE(dir.exists());
  BOOST_REQUIRE(QFileInfo(path).exists());

  BOOST_REQUIRE_NO_THROW(r.setPath(path));
  BOOST_CHECK(r.exists());
}

BOOST_AUTO_TEST_CASE( checkNoExistanceOfRecordIfRecordDoesNotExists )
{
  const QString path = "feature-folder/record1.mp3", name = "record1.mp3";
  QDir dir("feature-folder");
  Record r;
  BOOST_REQUIRE(dir.exists());
  BOOST_REQUIRE(QFileInfo(path).exists());

  BOOST_REQUIRE_NO_THROW(r.setPath(path));
  BOOST_CHECK(r.exists());

  BOOST_REQUIRE(dir.remove(name));
  BOOST_CHECK(!r.exists());

  BOOST_CHECK(QFile(path).open(QFile::ReadWrite));
}




BOOST_AUTO_TEST_CASE( copyRecordIfDestDirExistsAndRecordExists )
{
  const QString path = "feature-folder/record1.mp3", name = "record1.mp3",
      dest_path = "feature-folder/other_folder/record1.mp3";
  QDir dest_dir("feature-folder/other_folder");
  Record r;
  BOOST_REQUIRE(dest_dir.exists());
  BOOST_REQUIRE(!QFileInfo(dest_path).exists());

  BOOST_REQUIRE_NO_THROW(r.setPath(path));
  BOOST_REQUIRE(r.getRecordInfo().exists());

  Record copied;
  BOOST_CHECK_NO_THROW(copied = r.copy(dest_dir));
  BOOST_CHECK(copied.getRecordInfo().exists());
  BOOST_CHECK_EQUAL(copied.getRecordInfo().fileName().toStdString(),name.toStdString());

  BOOST_CHECK(dest_dir.entryList().contains(name));

  BOOST_CHECK(dest_dir.remove(name));//usuwanie utwofeature-folder/other_folderrzonego pliku
}

BOOST_AUTO_TEST_CASE( throwFileNotFoundAtCopyIfDestDirExistsAndFilePathNotSet )
{
  QDir dest_dir("feature-folder/other_folder");
  Record r;
  BOOST_REQUIRE(dest_dir.exists());

  BOOST_REQUIRE_THROW(r.copy(dest_dir), FileNotFound);
  BOOST_CHECK_EQUAL(dest_dir.entryInfoList().size(), 2);// folder zawiera elementy "." oraz ".."
}

BOOST_AUTO_TEST_CASE( throwDirNotFoundAtCopyIfDestDirNotExistsAndFilePathWasSet )
{
  const QString path = "feature-folder/record1.mp3", name = "record1.mp3";
  QDir dest_dir("fake-folder");
  Record r;
  BOOST_REQUIRE(!dest_dir.exists());
  BOOST_REQUIRE(QFileInfo(path).exists());

  BOOST_REQUIRE_NO_THROW(r.setPath(path));
  BOOST_REQUIRE_THROW(r.copy(dest_dir), DirNotFound);
}



BOOST_AUTO_TEST_CASE( moveRecordIfDestDirExistsAndRecordExists )
{
  const QString path = "feature-folder/record2.wav", name = "record2.wav",
      dest_path = "feature-folder/other_folder/record2.wav";
  QDir dest_dir("feature-folder/other_folder");
  Record r;
  BOOST_REQUIRE(dest_dir.exists());
  BOOST_REQUIRE(QFileInfo(path).exists());
  BOOST_REQUIRE(!QFileInfo(dest_path).exists());

  BOOST_REQUIRE_NO_THROW(r.setPath(path));
  BOOST_REQUIRE(r.getRecordInfo().exists());

  BOOST_CHECK_NO_THROW(r.move(dest_dir));
  BOOST_CHECK(r.getRecordInfo().exists());

  BOOST_CHECK_EQUAL(r.getRecordInfo().fileName().toStdString(),name.toStdString());

  BOOST_CHECK(dest_dir.entryInfoList().contains(QFileInfo(dest_path)));

  BOOST_CHECK(dest_dir.remove(name)); //usunięcie przeniesionego pliku
  BOOST_CHECK(QFile(path).open(QFile::ReadWrite));//odtworzenie przeniesionego pliku
}

BOOST_AUTO_TEST_CASE( throwFileNotFoundAtMoveIfDestDirExistsAndFilePathNotSet )
{
  QDir dest_dir("feature-folder/other_folder");
  Record r;
  BOOST_REQUIRE(dest_dir.exists());

  BOOST_REQUIRE_THROW(r.move(dest_dir), FileNotFound);
  BOOST_CHECK_EQUAL(dest_dir.entryInfoList().size(), 2);// folder zawiera elementy "." oraz ".."
}

BOOST_AUTO_TEST_CASE( throwDirNotFoundAtMoveIfDestDirNotExistsAndFilePathWasSet )
{
  const QString path = "feature-folder/record1.mp3", name = "record1.mp3";
  QDir dest_dir("fake-folder");
  Record r;
  BOOST_REQUIRE(!dest_dir.exists());

  BOOST_REQUIRE_NO_THROW(r.setPath(path));
  BOOST_REQUIRE_THROW(r.move(dest_dir), DirNotFound);
}

BOOST_AUTO_TEST_CASE( renameRecordIfRecordExists )
{
  const QString path = "feature-folder/record2.wav", name = "record2.wav",
      new_path ="feature-folder/record3.wav", new_name = "record3.wav";
  QDir dir("feature-folder");
  Record r;

  BOOST_REQUIRE(QFileInfo(path).exists());
  BOOST_REQUIRE(!QFileInfo(new_path).exists());

  BOOST_REQUIRE_NO_THROW(r.setPath(path));
  BOOST_REQUIRE(r.getRecordInfo().exists());

  BOOST_CHECK_NO_THROW(r.rename(new_name));
  BOOST_CHECK(r.getRecordInfo().exists());

  BOOST_CHECK_EQUAL(r.getRecordInfo().fileName().toStdString(),new_name.toStdString());
  BOOST_CHECK(QFileInfo(new_path).exists());
  BOOST_CHECK(!QFileInfo(path).exists());

  BOOST_CHECK(dir.remove(new_name)); //usunięcie zmienionego pliku
  BOOST_CHECK(QFile(path).open(QFile::ReadWrite));//odtworzenie pierwotnego pliku

}

BOOST_AUTO_TEST_CASE( throwFileNotFoundAtRenameIfFilePathNotSet )
{
  Record r;
  BOOST_REQUIRE_THROW(r.rename("fake-file"), FileNotFound);
}





BOOST_AUTO_TEST_SUITE_END()

