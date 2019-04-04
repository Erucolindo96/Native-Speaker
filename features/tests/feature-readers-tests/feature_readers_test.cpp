#include"features/tests/feature-readers-tests/feature_readers_test.hpp"

using namespace boost;
using namespace std;
using namespace alize;
using namespace utils;

static const uint32_t DISTRIB_CNT = 100, FEATURE_SIZE = 12;
static const double EPSILON = 0.0001;




BOOST_AUTO_TEST_SUITE( FeatureReaderTests )



BOOST_AUTO_TEST_CASE(throwFileNotFoundExceptionWhileReadingFeatureVectIfFeatureFileArentExist)
{
  FeatureReader reader;
  SPro4File file;
  BOOST_CHECK_THROW(reader.readFile(file), FileNotFound);
}

BOOST_AUTO_TEST_CASE(throwFileNotFoundExceptionWhileReadingSampleRateIfFeatureFileArentExist)
{
  FeatureReader reader;
  SPro4File file;

  BOOST_CHECK_THROW(reader.getSampleRate(file), FileNotFound);

}


BOOST_AUTO_TEST_CASE(readCorrectFeatureVectFromFileIfFileExistsAndHaveCorrectExt)
{
  const string FILE = "testing_feature.mfcc", DIR = "samples/mfcc/";
  BOOST_REQUIRE(QFileInfo((DIR + FILE).c_str()).exists());

  FeatureReader reader;
  SPro4File file;
  file.setPath((DIR + FILE).c_str());

  vector<Feature> feature_vec;
  BOOST_REQUIRE_NO_THROW(feature_vec = reader.readFile(file));
  RealVector<double> expected_feature_zero =
      utils::toRealVector({-7.227401, -0.610783, -1.328951, -1.678702,
                           -0.652852, -0.155907, -0.557129, -0.187439,
                           -0.197170, -0.104965, -0.327201, 0.230283});
  BOOST_REQUIRE(!feature_vec.empty());
  BOOST_REQUIRE_EQUAL(feature_vec[0].getVectSize(), expected_feature_zero.size());
  for(uint32_t i = 0 ;i< FEATURE_SIZE; ++i)
  {
    BOOST_CHECK_SMALL(feature_vec[0][i] - expected_feature_zero[i], EPSILON);
  }
}

BOOST_AUTO_TEST_CASE(readCorrectFeatureSampleRateFromFileIfDirExistWithSavedFeature)
{
  const string FILE = "testing_feature.mfcc", DIR = "samples/mfcc/";
  BOOST_REQUIRE(QFileInfo((DIR + FILE).c_str()).exists());

  FeatureReader reader;
  SPro4File file;
  file.setPath((DIR + FILE).c_str());

  const double SAMPLE_RATE_EXPECTED = 100;
  double sample_rate = 0;
  BOOST_REQUIRE_NO_THROW(sample_rate = reader.getSampleRate(file));
  BOOST_CHECK_SMALL(sample_rate - SAMPLE_RATE_EXPECTED, EPSILON);

}


BOOST_AUTO_TEST_SUITE_END()

//BOOST_AUTO_TEST_SUITE( FeatureReaderSilenceCutterTests )


//BOOST_AUTO_TEST_CASE(CutSilenceFromVectsIfDirExistWithSavedFeature)
//{
//  const string FILE = "testing_feature", EXT = ".mfcc", DIR = "./samples/mfcc/";
//  BOOST_REQUIRE(exist(DIR + FILE + EXT));

//  FeatureReaderSilenceCutter reader;
//  reader.setFeatureDir(DIR);

//  vector<Feature> feature_vec;
//  BOOST_REQUIRE_NO_THROW(feature_vec = reader.readFile(FILE, EXT));
//  const uint32_t LOG_ENERGY_INDEX = 0;
//  for(uint32_t i = 0 ;i< feature_vec.size(); ++i)
//  {
//    BOOST_CHECK(feature_vec[i][LOG_ENERGY_INDEX] >= reader.MIN_ENERGY);
//  }
//}


//BOOST_AUTO_TEST_SUITE_END()


