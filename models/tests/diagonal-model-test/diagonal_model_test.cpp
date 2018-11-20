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
#include"exceptions/simple_exceptions.hpp"

using namespace boost;
using namespace std;
using namespace alize;


const uint32_t FEATURE_SIZE = 2, DISTRIB_CNT = 10;
const uint32_t FEATURE_CNT = 10;
const double EPS = 0.00001;

static vector<Feature> training_vec(FEATURE_CNT, Feature(FEATURE_SIZE));


BOOST_AUTO_TEST_SUITE( SettersAndGettersTest )


BOOST_AUTO_TEST_CASE( getCorrectFeaturesIfTheyWasSet )
{
    DiagonalModel model(DISTRIB_CNT, FEATURE_SIZE);
    const uint32_t F_CNT = 5;
    vector<Feature> features(F_CNT, Feature(FEATURE_SIZE));

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

BOOST_AUTO_TEST_CASE( getCorrectFeatureVectorIfItWasSet )
{
  DiagonalModel model(DISTRIB_CNT, FEATURE_SIZE);
  const uint32_t F_CNT = 5;
  vector<Feature> features(F_CNT, Feature(FEATURE_SIZE));

  for(uint32_t i=0; i < F_CNT; ++i)
  {
    for(uint32_t j=0; j < FEATURE_SIZE; ++j)
    {
      features[i][j] = 0.5;
    }
  }
  BOOST_CHECK_NO_THROW(model.addTrainingFeature(features));

  auto features_in_model = model.getTrainingFeatures();
  BOOST_REQUIRE_EQUAL(features_in_model.size(), features.size());
  for(uint32_t i=0; i< features.size(); ++i )
  {
    BOOST_CHECK(features[i] == features_in_model[i]);
  }

}

BOOST_AUTO_TEST_CASE(constructModelWithName)
{
  const std::string name = "testowy";
  DiagonalModel model(DISTRIB_CNT, FEATURE_SIZE, name);
  BOOST_CHECK_EQUAL(model.getName(), name);
}

BOOST_AUTO_TEST_CASE(setModelName)
{
  const std::string name = "testowy_model";
  DiagonalModel model(DISTRIB_CNT, FEATURE_SIZE);
  BOOST_CHECK_NO_THROW(model.setName(name));
  BOOST_CHECK_EQUAL(model.getName(), name);
}

BOOST_AUTO_TEST_CASE(getDefaultModelNameIfTheyWasNotSet)
{
  const string def_name = "";
  DiagonalModel model(DISTRIB_CNT, FEATURE_SIZE);
  BOOST_CHECK_EQUAL(model.getName(), def_name);
}



BOOST_AUTO_TEST_CASE(getCorrectVectorSizeIfThatWasSetInConfig)
{
  DiagonalModel model(DISTRIB_CNT, FEATURE_SIZE);
  BOOST_CHECK_EQUAL(model.getFeatureVectorSize(), FEATURE_SIZE);
}

BOOST_AUTO_TEST_CASE(throwExceptionIfIndexOfDistribIsOutOfRangeInGetWeight)
{

  DiagonalModel model(DISTRIB_CNT, FEATURE_SIZE);
  BOOST_CHECK_THROW(model.getDistribWeight(-1), IndexOutOfBounds);
  BOOST_CHECK_THROW(model.getDistribWeight(DISTRIB_CNT + 1), IndexOutOfBounds);

}

BOOST_AUTO_TEST_CASE(throwExceptionIfIndexOfDistribIsOutOfRangeInSetWeight)
{

  DiagonalModel model(DISTRIB_CNT, FEATURE_SIZE);
  BOOST_CHECK_THROW(model.setDistribWeight(-1, 0.1), IndexOutOfBounds);
  BOOST_CHECK_THROW(model.setDistribWeight(DISTRIB_CNT + 1, 0.1), IndexOutOfBounds);

}


BOOST_AUTO_TEST_CASE(getCorrectNumberOfDistribIfParamsAreCorrect)
{

  DiagonalModel model(DISTRIB_CNT, FEATURE_SIZE);
  BOOST_CHECK_NO_THROW(model.getDistribCount());
  BOOST_CHECK_EQUAL(model.getDistribCount(), DISTRIB_CNT);
}

BOOST_AUTO_TEST_CASE(getCorrectWeightIfIndexOfDistributionIsCorrect)
{

  DiagonalModel model(DISTRIB_CNT, FEATURE_SIZE);
  BOOST_CHECK_NO_THROW(model.setDistribWeight(DISTRIB_CNT - 1, 0.5));
  model.getDistribWeight(DISTRIB_CNT - 1);
  BOOST_CHECK_CLOSE(model.getDistribWeight(DISTRIB_CNT - 1), 0.5, EPS);
}


BOOST_AUTO_TEST_CASE(throwExceptionIfIndexOfDistribIsOutOfRangeInGetMean)
{

  DiagonalModel model(DISTRIB_CNT, FEATURE_SIZE);
  BOOST_CHECK_THROW(model.getDistribMean(-1), IndexOutOfBounds);
  BOOST_CHECK_THROW(model.getDistribMean(DISTRIB_CNT + 1), IndexOutOfBounds);

}

BOOST_AUTO_TEST_CASE(throwExceptionIfIndexOfDistribIsOutOfRangeInSetMean)
{

  DiagonalModel model(DISTRIB_CNT, FEATURE_SIZE);

  RealVector<double> vec(FEATURE_SIZE, FEATURE_SIZE);
  BOOST_REQUIRE_EQUAL(vec.size(),FEATURE_SIZE);
  BOOST_CHECK_THROW(model.setDistribMean(-1, vec), IndexOutOfBounds);
  BOOST_CHECK_THROW(model.setDistribMean(DISTRIB_CNT + 1, vec), IndexOutOfBounds);

}

BOOST_AUTO_TEST_CASE(throwExceptionIfSizeOfSettedMeanIsIncorrect)
{

  DiagonalModel model(DISTRIB_CNT, FEATURE_SIZE);
  RealVector<double> vec(FEATURE_SIZE - 2,FEATURE_SIZE - 2);
  BOOST_CHECK_THROW(model.setDistribMean(1, vec), InvalidFeatureVectorSize);

}


BOOST_AUTO_TEST_CASE(getCorrectMeanIfIndexOfDistributionIsCorrect)
{


  DiagonalModel model(DISTRIB_CNT, FEATURE_SIZE);
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

  DiagonalModel model(DISTRIB_CNT, FEATURE_SIZE);
  BOOST_CHECK_THROW(model.getDistribCovariance(-1), IndexOutOfBounds);
  BOOST_CHECK_THROW(model.getDistribCovariance(DISTRIB_CNT + 1), IndexOutOfBounds);

}

BOOST_AUTO_TEST_CASE(throwExceptionIfIndexOfDistribIsOutOfRangeInSetCovariance)
{

  DiagonalModel model(DISTRIB_CNT, FEATURE_SIZE);

  BOOST_CHECK_THROW(model.setDistribCovariance(-1, RealVector<double>(FEATURE_SIZE, FEATURE_SIZE)), IndexOutOfBounds);
  BOOST_CHECK_THROW(model.setDistribCovariance(DISTRIB_CNT + 1, RealVector<double>(FEATURE_SIZE, FEATURE_SIZE)), IndexOutOfBounds);

}

BOOST_AUTO_TEST_CASE(throwExceptionIfSizeOfSettedCovarianceIsIncorrect)
{

  DiagonalModel model(DISTRIB_CNT, FEATURE_SIZE);

  RealVector<double> vec(FEATURE_SIZE - 2, FEATURE_SIZE - 2);
  BOOST_CHECK_THROW(model.setDistribCovariance(1, vec), InvalidFeatureVectorSize);

}


BOOST_AUTO_TEST_CASE(getCorrectCovarianceIfIndexOfDistributionIsCorrect)
{

  DiagonalModel model(DISTRIB_CNT, FEATURE_SIZE);
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

BOOST_AUTO_TEST_CASE(getRandomInitDataIfModelIsntSetManually)
{
  DiagonalModel model(DISTRIB_CNT, FEATURE_SIZE);
  BOOST_REQUIRE_EQUAL(model.getDistribCount(), DISTRIB_CNT);
  BOOST_REQUIRE_EQUAL(model.getFeatureVectorSize(), FEATURE_SIZE);
  for(uint32_t i = 0; i< DISTRIB_CNT; ++i)
  {
    BOOST_CHECK_NO_THROW(model.getDistribWeight(i));
    BOOST_CHECK_NO_THROW(model.getDistribMean(i));
    BOOST_CHECK_NO_THROW(model.getDistribCovariance(i));
  }
}

BOOST_AUTO_TEST_SUITE_END()



BOOST_AUTO_TEST_SUITE( CountingLikehood )

BOOST_AUTO_TEST_CASE(throwExceptionIfIndexOfDistribIsOutOfRangeInCountLikehood)
{

  DiagonalModel model(DISTRIB_CNT, FEATURE_SIZE);
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

  DiagonalModel model(DISTRIB_CNT, FEATURE_SIZE);
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


  DiagonalModel model(DISTRIB_CNT, FEATURE_SIZE);
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
