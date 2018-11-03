#ifndef DIAGONAL_TEST
#define DIAGONAL_TEST

#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE diagonal_model_test
#include<boost/test/unit_test.hpp>
#include<alize/alize.h>
#include"models/diagonal_model.hpp"
#include"models/learning_algo.hpp"
#include <typeinfo>
#include <random>
#include<iostream>

using namespace boost;
using namespace std;
using namespace alize;


const uint32_t FEATURE_SIZE = 2;
const uint32_t FEATURE_CNT = 10;
const double EPS = 0.00001;

static Config def_config;
//static unique_ptr<Config> def_config("config");
static vector<Feature> training_vec(FEATURE_CNT, Feature(FEATURE_SIZE));

void initConfig()
{
  def_config.setParam("vectSize", to_string(FEATURE_SIZE).c_str());
 // def_config.setParam("distribType", "GD");
  def_config.setParam("mixtureDistribCount", "10");
  def_config.setParam("maxLLK", "100");
  def_config.setParam("minLLK", "-100");
  def_config.setParam("featureServerMemAlloc", "1000000");
}

BOOST_AUTO_TEST_SUITE( SettersAndGettersTest )


BOOST_AUTO_TEST_CASE(ConfigInit)
{
  initConfig();
}


BOOST_AUTO_TEST_CASE( getCorrectAlgoIfItWasSet )
{
    DiagonalModel model(def_config);
    unique_ptr<ExpectationMaximalizationAlgo> algo = make_unique<ExpectationMaximalizationAlgo>();
    model.addLearnAlgo(std::move(algo));
    BOOST_CHECK( typeid(*model.getLearnAlgo() ) == typeid(ExpectationMaximalizationAlgo) ) ;
}

BOOST_AUTO_TEST_CASE( getCorrectFeaturesIfTheyWasSet )
{
    DiagonalModel model(def_config);
    const uint32_t F_CNT = 5;
    vector<Feature> features(F_CNT, Feature(def_config));
    random_device random;
    for(uint32_t i=0; i < F_CNT; ++i)
    {
      for(uint32_t j=0; j < FEATURE_SIZE; ++j)
      {
        features[i][j] = 0.5;
      }
    }

    for(uint32_t i=0; i< F_CNT; ++i)
    {
      BOOST_CHECK_NO_THROW(model.addTrainingFeature(features[i]));

    }

    auto features_in_model = model.getTrainingFeatures();
    BOOST_REQUIRE_EQUAL(features_in_model.size(), features.size());
    for(uint32_t i=0; i< features.size(); ++i )
    {
      BOOST_CHECK(features[i] == features_in_model[i]);
    }

}

BOOST_AUTO_TEST_CASE(getCorrectVectorSizeIfThatWasSetInConfig)
{
  DiagonalModel model(def_config);
  BOOST_CHECK_EQUAL(model.getFeatureVectorSize(), stoi(def_config.getParam("vectSize").c_str()));
}

BOOST_AUTO_TEST_CASE(throwExceptionIfIndexOfDistribIsOutOfRangeInGetWeight)
{
  const uint32_t DISTRIB_CNT = stoi(def_config.getParam("mixtureDistribCount").c_str());
  DiagonalModel model(def_config);
  BOOST_CHECK_THROW(model.getDistribWeight(-1), IndexOutOfBounds);
  BOOST_CHECK_THROW(model.getDistribWeight(DISTRIB_CNT + 1), IndexOutOfBounds);

}

BOOST_AUTO_TEST_CASE(throwExceptionIfIndexOfDistribIsOutOfRangeInSetWeight)
{
  const uint32_t DISTRIB_CNT = stoi(def_config.getParam("mixtureDistribCount").c_str());
  DiagonalModel model(def_config);
  BOOST_CHECK_THROW(model.setDistribWeight(-1, 0.1), IndexOutOfBounds);
  BOOST_CHECK_THROW(model.setDistribWeight(DISTRIB_CNT + 1, 0.1), IndexOutOfBounds);

}


BOOST_AUTO_TEST_CASE(getCorrectNumberOfDistribIfParamsAreCorrect)
{
  const uint32_t DISTRIB_CNT = stoi(def_config.getParam("mixtureDistribCount").c_str());
  DiagonalModel model(def_config);
  BOOST_CHECK_NO_THROW(model.getDistribCount());
  BOOST_CHECK_EQUAL(model.getDistribCount(), DISTRIB_CNT);
}

BOOST_AUTO_TEST_CASE(getCorrectWeightIfIndexOfDistributionIsCorrect)
{
  const uint32_t DISTRIB_CNT = stoi(def_config.getParam("mixtureDistribCount").c_str());
  DiagonalModel model(def_config);
  BOOST_CHECK_NO_THROW(model.setDistribWeight(DISTRIB_CNT - 1, 0.5));
  model.getDistribWeight(DISTRIB_CNT - 1);
  BOOST_CHECK_CLOSE(model.getDistribWeight(DISTRIB_CNT - 1), 0.5, EPS);
}


BOOST_AUTO_TEST_CASE(throwExceptionIfIndexOfDistribIsOutOfRangeInGetMean)
{
  const uint32_t DISTRIB_CNT = stoi(def_config.getParam("mixtureDistribCount").c_str());
  DiagonalModel model(def_config);
  BOOST_CHECK_THROW(model.getDistribMean(-1), IndexOutOfBounds);
  BOOST_CHECK_THROW(model.getDistribMean(DISTRIB_CNT + 1), IndexOutOfBounds);

}

BOOST_AUTO_TEST_CASE(throwExceptionIfIndexOfDistribIsOutOfRangeInSetMean)
{
  const uint32_t DISTRIB_CNT = stoi(def_config.getParam("mixtureDistribCount").c_str());
  DiagonalModel model(def_config);

  RealVector<double> vec(FEATURE_SIZE, FEATURE_SIZE);
  //vec[FEATURE_SIZE - 1] = 12;
  BOOST_REQUIRE_EQUAL(vec.size(),FEATURE_SIZE);
  BOOST_CHECK_THROW(model.setDistribMean(-1, vec), IndexOutOfBounds);
  BOOST_CHECK_THROW(model.setDistribMean(DISTRIB_CNT + 1, vec), IndexOutOfBounds);

}

BOOST_AUTO_TEST_CASE(throwExceptionIfSizeOfSettedMeanIsIncorrect)
{
  const uint32_t DISTRIB_CNT = stoi(def_config.getParam("mixtureDistribCount").c_str());
  DiagonalModel model(def_config);
  RealVector<double> vec(FEATURE_SIZE - 2,FEATURE_SIZE - 2);
  //vec[FEATURE_SIZE - 2 - 1] = 1.0;
  BOOST_CHECK_THROW(model.setDistribMean(1, vec), InvalidFeatureVectorSize);

}


BOOST_AUTO_TEST_CASE(getCorrectMeanIfIndexOfDistributionIsCorrect)
{

  const uint32_t DISTRIB_CNT = stoi(def_config.getParam("mixtureDistribCount").c_str());
  DiagonalModel model(def_config);
  RealVector<double> correct_mean(FEATURE_SIZE, FEATURE_SIZE), ret;
  for(uint32_t i=0; i < FEATURE_SIZE; ++i)
  {
    correct_mean[i] = 0.5;
  }
  BOOST_CHECK_NO_THROW(model.setDistribMean(DISTRIB_CNT - 1, correct_mean));
  BOOST_CHECK_NO_THROW(ret = model.getDistribMean(DISTRIB_CNT - 1));
  for(uint32_t i=0; i < FEATURE_SIZE; ++i)
  {
    BOOST_CHECK_EQUAL(correct_mean[i], ret[i]);
  }
}


BOOST_AUTO_TEST_CASE(throwExceptionIfIndexOfDistribIsOutOfRangeInGetCovariance)
{
  const uint32_t DISTRIB_CNT = stoi(def_config.getParam("mixtureDistribCount").c_str());
  DiagonalModel model(def_config);
  BOOST_CHECK_THROW(model.getDistribCovariance(-1), IndexOutOfBounds);
  BOOST_CHECK_THROW(model.getDistribCovariance(DISTRIB_CNT + 1), IndexOutOfBounds);

}

BOOST_AUTO_TEST_CASE(throwExceptionIfIndexOfDistribIsOutOfRangeInSetCovariance)
{
  const uint32_t DISTRIB_CNT = stoi(def_config.getParam("mixtureDistribCount").c_str());
  DiagonalModel model(def_config);

  BOOST_CHECK_THROW(model.setDistribCovariance(-1, RealVector<double>(FEATURE_SIZE, FEATURE_SIZE)), IndexOutOfBounds);
  BOOST_CHECK_THROW(model.setDistribCovariance(DISTRIB_CNT + 1, RealVector<double>(FEATURE_SIZE, FEATURE_SIZE)), IndexOutOfBounds);

}

BOOST_AUTO_TEST_CASE(throwExceptionIfSizeOfSettedCovarianceIsIncorrect)
{
  const uint32_t DISTRIB_CNT = stoi(def_config.getParam("mixtureDistribCount").c_str());
  DiagonalModel model(def_config);

  RealVector<double> vec(FEATURE_SIZE - 2, FEATURE_SIZE - 2);
  BOOST_CHECK_THROW(model.setDistribCovariance(1, vec), InvalidFeatureVectorSize);

}


BOOST_AUTO_TEST_CASE(getCorrectCovarianceIfIndexOfDistributionIsCorrect)
{
  const uint32_t DISTRIB_CNT = stoi(def_config.getParam("mixtureDistribCount").c_str());
  DiagonalModel model(def_config);
  RealVector<double> correct_cov(FEATURE_SIZE, FEATURE_SIZE), ret;
  for(uint32_t i=0; i < FEATURE_SIZE; ++i)
  {
    correct_cov[i] = 0.5;
  }
  BOOST_CHECK_NO_THROW(model.setDistribCovariance(DISTRIB_CNT - 1, correct_cov));
  BOOST_CHECK_NO_THROW(ret = model.getDistribCovariance(DISTRIB_CNT - 1));
  for(uint32_t i=0; i < FEATURE_SIZE; ++i)
  {
    BOOST_CHECK_EQUAL(correct_cov[i], ret[i]);
  }

}

BOOST_AUTO_TEST_SUITE_END()



BOOST_AUTO_TEST_SUITE( CountingLikehood )

BOOST_AUTO_TEST_CASE(throwExceptionIfIndexOfDistribIsOutOfRangeInCountLikehood)
{
  const uint32_t DISTRIB_CNT = stoi(def_config.getParam("mixtureDistribCount").c_str());
  DiagonalModel model(def_config);
  RealVector<double> mean(FEATURE_SIZE,FEATURE_SIZE), cov(FEATURE_SIZE, FEATURE_SIZE);
  Feature f(FEATURE_SIZE);
  for(uint32_t i=0; i< FEATURE_SIZE; ++i)
  {
    mean[i] = 0.0;
    cov[i] = 1.0;
    f[i] = 0;
  }
  for(uint32_t i=0;i < DISTRIB_CNT; ++i)
  {
    model.setDistribWeight(i, 1/DISTRIB_CNT);
    model.setDistribMean(i, mean);
    model.setDistribCovariance(i, cov);
  }

  BOOST_CHECK_THROW(model.countLikehoodWithWeight(f, -1), IndexOutOfBounds);
  BOOST_CHECK_THROW(model.countLikehoodWithWeight(f, DISTRIB_CNT + 1), IndexOutOfBounds);


}

BOOST_AUTO_TEST_CASE(countCorrectLikehoodOneDistribWithWeightIfParametersAreCorrect)
{
  const uint32_t DISTRIB_CNT = stoi(def_config.getParam("mixtureDistribCount").c_str());
  DiagonalModel model(def_config);
  RealVector<double> mean(FEATURE_SIZE, FEATURE_SIZE), cov(FEATURE_SIZE,FEATURE_SIZE);
  Feature f(FEATURE_SIZE);
  for(uint32_t i=0; i< FEATURE_SIZE; ++i)
  {
    mean[i] = 0.0;
    cov[i] = 1.0;
    f[i] = 0;
  }
  for(uint32_t i=0;i < DISTRIB_CNT; ++i)
  {
    model.setDistribWeight(i, 1/DISTRIB_CNT);
    model.setDistribMean(i, mean);
    model.setDistribCovariance(i, cov);
  }
  //teraz powinnismy otrzymac w każdej dystrybucji rozkład normalny
  //  pomnożony przez wagę równą 1/DISTRIB_CNT

  DistribGD distrib(FEATURE_SIZE);
  distrib.setMeanVect(mean);
  distrib.getCovVect() = cov;
  distrib.computeAll();
  // Dla wektora cech, zawierającego same zera powinnismy uzyskać wartość == 0.15915494309189535
  BOOST_CHECK_CLOSE(distrib.computeLK(f), 0.15915494309189535, EPS);
  double likehood = distrib.computeLK(f) * (1/DISTRIB_CNT);
  // waga * gęstość z jednej dystrybucji
  BOOST_CHECK_CLOSE(model.countLikehoodWithWeight(f, 0), likehood, EPS);

}


BOOST_AUTO_TEST_CASE(countCorrectLikehoodAllDistribIfParametersAreCorrect)
{

  const uint32_t DISTRIB_CNT = stoi(def_config.getParam("mixtureDistribCount").c_str());
  DiagonalModel model(def_config);
  RealVector<double> mean(FEATURE_SIZE, FEATURE_SIZE), cov(FEATURE_SIZE, FEATURE_SIZE);
  Feature f(FEATURE_SIZE);
  for(uint32_t i=0; i< FEATURE_SIZE; ++i)
  {
    mean[i] = 0;
    cov[i] = 1.0;
    f[i] = 0;
  }
  const double WEIGHT = 1.0/DISTRIB_CNT;
  for(uint32_t i=0;i < DISTRIB_CNT; ++i)
  {
    model.setDistribWeight(i, WEIGHT);
    model.setDistribMean(i, mean);
    model.setDistribCovariance(i, cov);
  }

  DistribGD distrib(FEATURE_SIZE);
  distrib.setMeanVect(mean);
  distrib.getCovVect() = cov;
  distrib.computeAll();

  //Dla wektora cech, zawierającego same zera powinnismy uzyskać(dla jednej dystrybucji)
  //wartość == 0.15915494309189535
  double likehood_one_distrib = distrib.computeLK(f);
  BOOST_CHECK_CLOSE(likehood_one_distrib, 0.15915494309189535, EPS);
  //waga * gęstość z jednej dystrybucji * ilość dystrybucji(bo są takie same)
  double summary_likehood = likehood_one_distrib * WEIGHT * DISTRIB_CNT;
  BOOST_CHECK_CLOSE(model.countLikehoodWithWeight(f), summary_likehood , EPS);

}


BOOST_AUTO_TEST_SUITE_END()




#endif
