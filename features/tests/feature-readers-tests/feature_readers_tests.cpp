#ifndef DIAGONAL_TEST
#define DIAGONAL_TEST

#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE feature_readers_tests
#include<boost/test/unit_test.hpp>
#include"features/FeatureReader.hpp"
#include"models/diagonal_model.hpp"
#include <typeinfo>
#include <random>
#include<iostream>
#include"utils/utils.hpp"
#include<memory>

#include"exceptions/simple_exceptions.hpp"

using namespace boost;
using namespace std;
using namespace alize;
using namespace utils;

static const uint32_t DISTRIB_CNT = 100, FEATURE_SIZE = 12;
static const double EPSILON = 0.0001;



BOOST_AUTO_TEST_SUITE( FeatureReaderLinuxTests )

BOOST_AUTO_TEST_CASE( getCorrectFeatureReadDirectoryIfThatWasSetInSetter )
{
  FeatureReaderLinux reader;
  BOOST_REQUIRE_NO_THROW(reader.setFeatureDir("folder"));
  BOOST_CHECK_EQUAL(reader.getFeatureDir(), "folder");
}

BOOST_AUTO_TEST_CASE(contructCorrectCopyOfreaderIfFeatureDirWasSet)
{
  FeatureReaderLinux reader;
  reader.setFeatureDir("/sciezka/folderu");
  FeatureReaderLinux copy = reader;
  BOOST_CHECK_EQUAL(copy.getFeatureDir(), reader.getFeatureDir());
}

BOOST_AUTO_TEST_CASE(correctAssignOfreaderIfFeatureDirWasSet)
{
  FeatureReaderLinux reader;
  reader.setFeatureDir("/sciezka/folderu");
  FeatureReaderLinux copy;
  BOOST_REQUIRE_NO_THROW(copy = reader);
  BOOST_CHECK_EQUAL(copy.getFeatureDir(), reader.getFeatureDir());
}

BOOST_AUTO_TEST_CASE(correctMoveContructionOfreaderIfFeatureDirWasSet)
{
  FeatureReaderLinux reader;
  reader.setFeatureDir("/sciezka/folderu");
  FeatureReaderLinux copy(std::move(reader));
  BOOST_CHECK_EQUAL(copy.getFeatureDir(), "/sciezka/folderu");
}


BOOST_AUTO_TEST_CASE(correctMoveAssignmentOfreaderIfFeatureDirWasSet)
{
  FeatureReaderLinux reader;
  reader.setFeatureDir("/sciezka/folderu");
  FeatureReaderLinux copy;
  BOOST_REQUIRE_NO_THROW(copy = std::move(reader));
  BOOST_CHECK_EQUAL(copy.getFeatureDir(), "/sciezka/folderu");
}

BOOST_AUTO_TEST_CASE(throwFileNotFoundExceptionWhileReadingFeatureVectIfFeatureDirArentExist)
{
  FeatureReaderLinux reader;
  reader.setFeatureDir("nope_folder");

  BOOST_CHECK_THROW(reader.readFile("nope_file", "nope_ext"), FileNotFound);

}

BOOST_AUTO_TEST_CASE(throwFileNotFoundExceptionWhileReadingSampleRateIfFeatureDirArentExist)
{
  FeatureReaderLinux reader;
  reader.setFeatureDir("nope_folder");

  BOOST_CHECK_THROW(reader.getSampleRate("nope_file", "nope_ext"), FileNotFound);

}

BOOST_AUTO_TEST_CASE(readCorrectFeatureVectFromFileIfDirExistWithSavedFeature)
{
  const string FILE = "testing_feature", EXT = ".mfcc";
  bool not_exist = system(("cat "+FILE +EXT).c_str());
  BOOST_REQUIRE(!not_exist);

  FeatureReaderLinux reader;
  reader.setFeatureDir("./");

  vector<Feature> feature_vec;
  BOOST_REQUIRE_NO_THROW(feature_vec = reader.readFile(FILE, EXT));
  RealVector<double> expected_feature_zero =
      utils::toRealVector({-7.227401, -0.610783, -1.328951, -1.678702,
                           -0.652852, -0.155907, -0.557129, -0.187439,
                           -0.197170, -0.104965, -0.327201, 0.230283});

  BOOST_REQUIRE_EQUAL(feature_vec.size(), expected_feature_zero.size());
  for(uint32_t i = 0 ;i< FEATURE_SIZE; ++i)
  {
    BOOST_CHECK_SMALL(feature_vec[0][i] - expected_feature_zero[i], EPSILON);
  }
}

BOOST_AUTO_TEST_CASE(readCorrectFeatureSampleRateFromFileIfDirExistWithSavedFeature)
{
  const string FILE = "testing_feature", EXT = ".mfcc";
  bool not_exist = system(("cat "+FILE +EXT).c_str());
  BOOST_REQUIRE(!not_exist);

  FeatureReaderLinux reader;
  reader.setFeatureDir("./");
  const double SAMPLE_RATE_EXPECTED = 100;
  double sample_rate = 0;
  BOOST_REQUIRE_NO_THROW(sample_rate = reader.getSampleRate(FILE, EXT));
  BOOST_CHECK_SMALL(sample_rate - SAMPLE_RATE_EXPECTED, EPSILON);

}


BOOST_AUTO_TEST_SUITE_END()












#endif
