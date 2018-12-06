#include"features/tests/mfcc_converter_tests/mfcc_converter_linux_test.hpp"

using namespace boost;
using namespace std;
using namespace alize;


static bool exist(const std::string &filename)
{
  ifstream f(filename);
  return f.good();
}


BOOST_AUTO_TEST_SUITE( MfccConverterLinuxTest )


BOOST_AUTO_TEST_CASE( throwFileNotFoundIfSourceFileDoesNotExist )
{
  MfccConverterLinux con;
    std::string source_path = "samples/not_a_file", dest_dir = "samples/mfcc/", dest_file = "dest_name.mfcc";
  BOOST_CHECK_THROW(con.convertToSPro4(source_path, dest_dir, dest_file),
                    FileNotFound);

}
/*
BOOST_AUTO_TEST_CASE( throwDirNotFoundIfSourceDirDoesNotExist )
{
  MfccConverterLinux con;
  std::string source_file = "inwokacja.mp3", dest_dir = "converted/", dest_file = "dest_name.mfcc";
  BOOST_CHECK_THROW(con.convertToSPro4("/fake_dir/", source_file, dest_dir, dest_file),
                    FileNotFound);

}
*/
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

BOOST_AUTO_TEST_SUITE_END()
