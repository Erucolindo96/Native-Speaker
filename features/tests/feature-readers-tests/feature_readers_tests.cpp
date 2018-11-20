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
#include<fstream>

using namespace boost;
using namespace std;
using namespace alize;
using namespace utils;

static const uint32_t DISTRIB_CNT = 100, FEATURE_SIZE = 12;
static const double EPSILON = 0.0001;


bool exist(const std::string &filename)
{
  ifstream f(filename);
  return f.good();
}


BOOST_AUTO_TEST_SUITE( FeatureReaderTests )

BOOST_AUTO_TEST_CASE( getCorrectFeatureReadDirectoryIfThatWasSetInSetter )
{
  FeatureReader reader;
  BOOST_REQUIRE_NO_THROW(reader.setFeatureDir("folder"));
  BOOST_CHECK_EQUAL(reader.getFeatureDir(), "folder");
}

BOOST_AUTO_TEST_CASE(contructCorrectCopyOfreaderIfFeatureDirWasSet)
{
  FeatureReader reader;
  reader.setFeatureDir("/sciezka/folderu");
  FeatureReader copy = reader;
  BOOST_CHECK_EQUAL(copy.getFeatureDir(), reader.getFeatureDir());
}

BOOST_AUTO_TEST_CASE(correctAssignOfreaderIfFeatureDirWasSet)
{
  FeatureReader reader;
  reader.setFeatureDir("/sciezka/folderu");
  FeatureReader copy;
  BOOST_REQUIRE_NO_THROW(copy = reader);
  BOOST_CHECK_EQUAL(copy.getFeatureDir(), reader.getFeatureDir());
}

BOOST_AUTO_TEST_CASE(correctMoveContructionOfreaderIfFeatureDirWasSet)
{
  FeatureReader reader;
  reader.setFeatureDir("/sciezka/folderu");
  FeatureReader copy(std::move(reader));
  BOOST_CHECK_EQUAL(copy.getFeatureDir(), "/sciezka/folderu");
}


BOOST_AUTO_TEST_CASE(correctMoveAssignmentOfreaderIfFeatureDirWasSet)
{
  FeatureReader reader;
  reader.setFeatureDir("/sciezka/folderu");
  FeatureReader copy;
  BOOST_REQUIRE_NO_THROW(copy = std::move(reader));
  BOOST_CHECK_EQUAL(copy.getFeatureDir(), "/sciezka/folderu");
}

BOOST_AUTO_TEST_CASE(throwFileNotFoundExceptionWhileReadingFeatureVectIfFeatureDirArentExist)
{
  FeatureReader reader;
  reader.setFeatureDir("nope_folder");

  BOOST_CHECK_THROW(reader.readFile("testing_feature", ".mfcc"), FileNotFound);

}

BOOST_AUTO_TEST_CASE(throwFileNotFoundExceptionWhileReadingSampleRateIfFeatureDirArentExist)
{
  FeatureReader reader;
  reader.setFeatureDir("nope_folder");

  BOOST_CHECK_THROW(reader.getSampleRate("testing_feature", ".mfcc"), FileNotFound);

}

BOOST_AUTO_TEST_CASE(throwFileNotFoundExceptionWhileReadingFeatureVectIfFeatureFileArentExist)
{
  FeatureReader reader;
  reader.setFeatureDir("./");

  BOOST_CHECK_THROW(reader.readFile("nope_file", ".mfcc"), FileNotFound);

}

BOOST_AUTO_TEST_CASE(throwFileNotFoundExceptionWhileReadingSampleRateIfFeatureFileArentExist)
{
  FeatureReader reader;
  reader.setFeatureDir("./");

  BOOST_CHECK_THROW(reader.getSampleRate("nope_file", ".mfcc"), FileNotFound);

}

BOOST_AUTO_TEST_CASE(readCorrectFeatureVectFromFileIfDirExistWithSavedFeature)
{
  const string FILE = "testing_feature", EXT = ".mfcc";
  BOOST_REQUIRE(exist(FILE + EXT));

  FeatureReader reader;
  reader.setFeatureDir("./");

  vector<Feature> feature_vec;
  BOOST_REQUIRE_NO_THROW(feature_vec = reader.readFile(FILE, EXT));
  RealVector<double> expected_feature_zero =
      utils::toRealVector({-7.227401, -0.610783, -1.328951, -1.678702,
                           -0.652852, -0.155907, -0.557129, -0.187439,
                           -0.197170, -0.104965, -0.327201, 0.230283});

  BOOST_REQUIRE_EQUAL(feature_vec[0].getVectSize(), expected_feature_zero.size());
  for(uint32_t i = 0 ;i< FEATURE_SIZE; ++i)
  {
    BOOST_CHECK_SMALL(feature_vec[0][i] - expected_feature_zero[i], EPSILON);
  }
}

BOOST_AUTO_TEST_CASE(readCorrectFeatureSampleRateFromFileIfDirExistWithSavedFeature)
{
  const string FILE = "testing_feature", EXT = ".mfcc";

  BOOST_REQUIRE(exist(FILE + EXT));

  FeatureReader reader;
  reader.setFeatureDir("./");
  const double SAMPLE_RATE_EXPECTED = 100;
  double sample_rate = 0;
  BOOST_REQUIRE_NO_THROW(sample_rate = reader.getSampleRate(FILE, EXT));
  BOOST_CHECK_SMALL(sample_rate - SAMPLE_RATE_EXPECTED, EPSILON);

}


BOOST_AUTO_TEST_SUITE_END()












#endif
