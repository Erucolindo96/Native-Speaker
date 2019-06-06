#include"features/tests/mfcc_converter_tests/mfcc_converter_test.hpp"

using namespace boost;
using namespace std;
using namespace alize;




BOOST_AUTO_TEST_SUITE( MfccConverterTest )


BOOST_AUTO_TEST_CASE(setCorrectValOfSampleRate)
{
  std::unique_ptr<MfccConverter> conv = make_unique<MfccConverterWav>();
  BOOST_CHECK_NO_THROW(conv->setSampleRate(64000));
  BOOST_CHECK_EQUAL(conv->getSampleRate(), 64000);
}

BOOST_AUTO_TEST_CASE(throwInvalidArgumentAtSettingNotPositiveSampleRate)
{
  std::unique_ptr<MfccConverter> conv = make_unique<MfccConverterWav>();
  BOOST_CHECK_THROW(conv->setSampleRate(-10), invalid_argument);
  BOOST_CHECK_THROW(conv->setSampleRate(0), invalid_argument);
}

BOOST_AUTO_TEST_CASE(setCorrectValOfPreEmphasis)
{
  std::unique_ptr<MfccConverter> conv = make_unique<MfccConverterWav>();
  BOOST_CHECK_NO_THROW(conv->setPreEmphasis(0.8));
  BOOST_CHECK_EQUAL(conv->getPreEmphasis(), 0.8);
}

BOOST_AUTO_TEST_CASE(throwInvalidArgumentAtSettingNotPositivePreEmphasis)
{
  std::unique_ptr<MfccConverter> conv = make_unique<MfccConverterWav>();
  BOOST_CHECK_THROW(conv->setPreEmphasis(-1), invalid_argument);
  BOOST_CHECK_THROW(conv->setPreEmphasis(0), invalid_argument);
}

BOOST_AUTO_TEST_CASE(throwInvalidArgumentAtSettingPreEmphasisMoreThan0_95)
{
  std::unique_ptr<MfccConverter> conv = make_unique<MfccConverterWav>();
  BOOST_CHECK_THROW(conv->setPreEmphasis(1), invalid_argument);
  BOOST_CHECK_THROW(conv->setPreEmphasis(29), invalid_argument);
  BOOST_CHECK_THROW(conv->setPreEmphasis(0.955), invalid_argument);
}


BOOST_AUTO_TEST_CASE(SetCorrectValOfFrameLenght)
{
  std::unique_ptr<MfccConverter> conv = make_unique<MfccConverterWav>();
  BOOST_CHECK_NO_THROW(conv->setFrameLenght(30));
  BOOST_CHECK_EQUAL(conv->getFrameLenght(), 30);
}

BOOST_AUTO_TEST_CASE(throwInvalidArgumentAtSettingNotPositiveFrameLenght)
{
  std::unique_ptr<MfccConverter> conv = make_unique<MfccConverterWav>();
  BOOST_CHECK_THROW(conv->setFrameLenght(-1), invalid_argument);
  BOOST_CHECK_THROW(conv->setFrameLenght(0), invalid_argument);
  BOOST_CHECK_THROW(conv->setFrameLenght(-100), invalid_argument);
}

BOOST_AUTO_TEST_CASE(setCorrectValOfInterval)
{
  std::unique_ptr<MfccConverter> conv = make_unique<MfccConverterWav>();
  BOOST_CHECK_NO_THROW(conv->setInterval(15));
  BOOST_CHECK_EQUAL(conv->getInterval(), 15);
}

BOOST_AUTO_TEST_CASE(throwInvalidArgumentAtSettingNotPositiveInterval)
{
  std::unique_ptr<MfccConverter> conv = make_unique<MfccConverterWav>();
  BOOST_CHECK_THROW(conv->setInterval(-1), invalid_argument);
  BOOST_CHECK_THROW(conv->setInterval(0), invalid_argument);
  BOOST_CHECK_THROW(conv->setInterval(-100), invalid_argument);
}

BOOST_AUTO_TEST_CASE(setCorrectValOfFeatureLenght)
{
  std::unique_ptr<MfccConverter> conv = make_unique<MfccConverterWav>();
  BOOST_CHECK_NO_THROW(conv->setFeatureLenght(17));
}

BOOST_AUTO_TEST_CASE(throwInvalidArgumentAtSettingNotPositiveFeatureLenght)
{
  std::unique_ptr<MfccConverter> conv = make_unique<MfccConverterWav>();
  BOOST_CHECK_THROW(conv->setFeatureLenght(-1), invalid_argument);
  BOOST_CHECK_THROW(conv->setFeatureLenght(0), invalid_argument);
  BOOST_CHECK_THROW(conv->setFeatureLenght(-100), invalid_argument);
}

BOOST_AUTO_TEST_CASE(throwInvalidArgumentAtSettingFeatureLenghtMoreThan24)
{
  std::unique_ptr<MfccConverter> conv = make_unique<MfccConverterWav>();
  BOOST_CHECK_THROW(conv->setFeatureLenght(25), invalid_argument);
  BOOST_CHECK_THROW(conv->setFeatureLenght(100), invalid_argument);
}

BOOST_AUTO_TEST_CASE(returnCorrectFeatureLenghtAfterSettingCorrectValOfFeatureLenghtAndAddingLogEnergy)
{
  const int32_t FEATURES = 15, ALL_LENGHT = 16;
  std::unique_ptr<MfccConverter> conv = make_unique<MfccConverterWav>();
  BOOST_CHECK_NO_THROW(conv->setFeatureLenght(FEATURES));
  BOOST_CHECK_NO_THROW(conv->setLogEnergy(true));
  BOOST_CHECK_EQUAL(conv->getFeatureLenght(), ALL_LENGHT);
}

BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE( MfccConverterWavTest )

BOOST_AUTO_TEST_CASE(correctlyConvertWavRecordToMfccIfRecordExists)
{
  const QString RECORD_DIR = "samples/wav/",
      RECORD_NAME = "janfigat1_2-01",
      record_path = RECORD_DIR + RECORD_NAME + ".wav",
      DEST_FILE_PATH = RECORD_DIR + RECORD_NAME + SPro4File::VALID_EXT;
  const uint32_t F_CNT = 241;

  std::unique_ptr<MfccConverter> conv = make_unique<MfccConverterWav>();
  BOOST_REQUIRE(QFileInfo(record_path).exists());
  BOOST_REQUIRE(!QFileInfo(DEST_FILE_PATH).exists());

  Record r;
  r.setPath(record_path);

  BOOST_CHECK(false);//bo test nie działa - linijka ponizej wywala null ptr exception
  auto converted_file = conv->convertToSPro4(r);
  BOOST_REQUIRE(converted_file.exists());

  FeatureReader reader;
  auto f_vec = reader.readFile(converted_file);
  BOOST_REQUIRE_EQUAL(f_vec.size(), F_CNT);
  BOOST_CHECK(QDir(RECORD_DIR).remove(converted_file.getRecordInfo().fileName()));
}

BOOST_AUTO_TEST_CASE(throwFileNotFoundAtConvertingRecordIfRecordDoesNotExists)
{
  std::unique_ptr<MfccConverter> conv = make_unique<MfccConverterWav>();

  Record r;
  BOOST_CHECK_THROW(auto converted_file = conv->convertToSPro4(r), FileNotFound);
}

BOOST_AUTO_TEST_CASE(throwUnableToConvertToMfccAtConvertingIfRecordIsNotAWavFile)
{
  const QString RECORD_DIR = "samples/mp3/",
      RECORD_NAME = "inwokacja",
      record_path = RECORD_DIR + RECORD_NAME + ".mp3",
      DEST_FILE_PATH = RECORD_DIR + RECORD_NAME + SPro4File::VALID_EXT;

  std::unique_ptr<MfccConverter> conv = make_unique<MfccConverterWav>();
  BOOST_REQUIRE(QFileInfo(record_path).exists());

  Record r;
  r.setPath(record_path);
  BOOST_CHECK_THROW(auto converted_file = conv->convertToSPro4(r), UnableToConvertToMfcc);
  BOOST_CHECK(!QFileInfo(DEST_FILE_PATH).exists());
}

BOOST_AUTO_TEST_SUITE_END()



/*
BOOST_AUTO_TEST_CASE( throwFileNotFoundIfSourceFileDoesNotExist )
{
  MfccConverterLinux con;
    std::string source_path = "samples/not_a_file", dest_dir = "samples/mfcc/", dest_file = "dest_name.mfcc";
  BOOST_CHECK_THROW(con.convertToSPro4(source_path, dest_dir, dest_file),
                    FileNotFound);

}

BOOST_AUTO_TEST_CASE( throwDirNotFoundIfSourceDirDoesNotExist )
{
  MfccConverterLinux con;
  std::string source_file = "inwokacja.mp3", dest_dir = "converted/", dest_file = "dest_name.mfcc";
  BOOST_CHECK_THROW(con.convertToSPro4("/fake_dir/", source_file, dest_dir, dest_file),
                    FileNotFound);

}

BOOST_AUTO_TEST_CASE( throwDirNotFoundIfDestDirDoesNotExist )
{
  MfccConverterLinux con;
  std::string source_dir = "samples/mp3/", source_file = "inwokacja.mp3", dest_file = "dest_name.mfcc";;
  BOOST_CHECK_THROW(con.convertToSPro4(source_dir + source_file, "/fake_dir/", dest_file),
                    DirNotFound);
}

BOOST_AUTO_TEST_CASE(throwCannotConvertToSPro4IfSoruceFileIsNotAMp3File)
{
  MfccConverterLinux con;
  std::string source_dir = "samples/mp3/", source_file = "fake_mp3.mp3",
      dest_dir = "samples/mfcc/",dest_file = "fake_mfcc.mfcc";

  BOOST_CHECK_THROW(con.convertToSPro4(source_dir+source_file, dest_dir, dest_file),
                    CannotConvertToSPro4);
  BOOST_CHECK(!utils::fileExist(dest_dir+dest_file));
}

BOOST_AUTO_TEST_CASE(correctlyConvertMp3FileToSPro4MfccFormat)
{
  MfccConverterLinux con;
  std::string source_dir = "samples/mp3/", source_file = "inwokacja.mp3",
      dest_dir = "samples/mfcc",dest_file = "dest_name.mfcc";

  BOOST_CHECK_NO_THROW(con.convertToSPro4(source_dir+source_file, dest_dir, dest_file));
  BOOST_CHECK(exist(dest_dir+"/" + dest_file));
  FeatureReader reader;
  reader.setFeatureDir(dest_dir+"/");
  BOOST_CHECK_NO_THROW(reader.readFile(dest_file, ""));

  //czyszczenie po teście
  system((string("rm ") + dest_dir+ "/"+ dest_file).c_str() );

}
*/

