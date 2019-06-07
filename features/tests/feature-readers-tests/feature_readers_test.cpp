#include"features/tests/feature-readers-tests/feature_readers_test.hpp"

using namespace boost;
using namespace std;
using namespace alize;
using namespace utils;

//static const uint32_t DISTRIB_CNT = 100, FEATURE_SIZE = 12;
//static const double EPSILON = 0.0001;




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
  const double EPSILON = 0.0001;
  const string FILE = "testing_feature.mfcc", DIR = "samples/mfcc/";
  BOOST_REQUIRE(QFileInfo((DIR + FILE).c_str()).exists());

  FeatureReader reader;
  SPro4File file;
  file.setPath((DIR + FILE).c_str());

  vector<Feature> feature_vec;
  BOOST_REQUIRE_NO_THROW(feature_vec = reader.readFile(file));
  RealVector<double> expected_feature_zero =
      utils::toRealVector({-0.980402, -0.637758, -0.646379,
                           -0.072449, 0.428985, 0.506418,
                           -0.455474, 0.150900, 0.329370,
                           0.260792, -1.197633, 0.447731,
                           -1.287831, 0.072889, -0.203951,
                           -1.820158, -1.576474, 0.847596,
                           -1.140186, -0.038114, 0.151650,
                           0.112668, -0.024415, -0.128676,
                           -0.039389, 0.281176, 0.159363,
                           -0.097660, 0.060293, 0.247564,
                           -0.434428, 0.149061, 0.151218,
                           0.056053, 0.574276, 0.515589,
                           -0.053472, -0.010750});
  const uint32_t  FEATURE_SIZE = expected_feature_zero.size();

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

  const double SAMPLE_RATE_EXPECTED = 100, EPSILON = 0.0001;
  double sample_rate = 0;
  BOOST_REQUIRE_NO_THROW(sample_rate = reader.getSampleRate(file));
  BOOST_CHECK_SMALL(sample_rate - SAMPLE_RATE_EXPECTED, EPSILON);

}


BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE( FeatureReaderSilenceCutterTests )




BOOST_AUTO_TEST_CASE(correctlyCountIndexOfLogEnergyIfFeatureVecContainDiffVec)
{
  FeatureReaderSilenceCutter r;
  const uint32_t F_SIZE = 32;
  BOOST_CHECK_EQUAL(r.countIndexOfLogEnergy(F_SIZE, true), (F_SIZE/2)-1);
}

BOOST_AUTO_TEST_CASE(correctlyCountIndexOfLogEnergyIfFeatureVecNotContainDiffVec)
{
  FeatureReaderSilenceCutter r;
  const uint32_t F_SIZE = 32;
  BOOST_CHECK_EQUAL(r.countIndexOfLogEnergy(F_SIZE, false), F_SIZE - 1);
}

BOOST_AUTO_TEST_CASE(CutSilenceFromVectsIfDirExistWithSavedFeature)
{
  const string FILE_NAME = "testing_feature.mfcc", DIR = "./samples/mfcc/";
  BOOST_REQUIRE(QFileInfo((DIR + FILE_NAME ).c_str()).exists());
  const uint32_t  FEATURE_SIZE = 38;

  FeatureReaderSilenceCutter reader;

  SPro4File file;
  file.setPath((DIR + FILE_NAME).c_str());

  vector<Feature> feature_vec;
  BOOST_REQUIRE_NO_THROW(feature_vec = reader.readFile(file));
  BOOST_CHECK_EQUAL(feature_vec.size(), 177);

  const uint32_t LOG_ENERGY_INDEX = reader.countIndexOfLogEnergy(FEATURE_SIZE, true);
  BOOST_CHECK_EQUAL(LOG_ENERGY_INDEX, 18);
  for(uint32_t i = 0 ;i< feature_vec.size(); ++i)
  {
    cout<<feature_vec[i][LOG_ENERGY_INDEX]<<endl;
    BOOST_CHECK(feature_vec[i][LOG_ENERGY_INDEX] >= reader.MIN_ENERGY);
  }
}


BOOST_AUTO_TEST_SUITE_END()


