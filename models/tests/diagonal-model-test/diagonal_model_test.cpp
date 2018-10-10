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

using namespace boost;
using namespace std;
using namespace alize;


const uint32_t FEATURE_SIZE = 12;
const uint32_t FEATURE_CNT = 10;

static unique_ptr<Config> def_config;
static vector<Feature> training_vec(FEATURE_CNT, Feature(FEATURE_SIZE));

void initConfig()
{
  def_config = nullptr;
  def_config = make_unique<Config>();
  def_config->setParam("vectSize", to_string(FEATURE_SIZE).c_str());

}


BOOST_AUTO_TEST_SUITE( SettersAndGettersTest )

BOOST_AUTO_TEST_CASE( getAnotherConfigIfSheWasSet )
{
    initConfig();
    DiagonalModel model(*def_config);
    Config other;
    model.setConfig(other);
    BOOST_CHECK( model.getConfig() == other );
}

BOOST_AUTO_TEST_CASE( getCorrectAlgoIfItWasSet )
{
    initConfig();
    DiagonalModel model(*def_config);
    unique_ptr<ExpectationMaximalizationAlgo> algo = make_unique<ExpectationMaximalizationAlgo>();
    model.addLearnAlgo(std::move(algo));
    BOOST_CHECK( typeid(*model.getLearnAlgo() ) == typeid(ExpectationMaximalizationAlgo) ) ;
}

BOOST_AUTO_TEST_CASE( getCorrectFeaturesIfTheyWasSet )
{
    initConfig();
    DiagonalModel model(*def_config);
    const uint32_t F_CNT = 5;
    vector<Feature> features(F_CNT, Feature(FEATURE_SIZE) );
    random_device random;
    for(uint32_t i=0; i< features.size(); ++i)
    {
      for(uint32_t j=0; j< FEATURE_SIZE; ++j)
      {
        Feature& ref = features[i];
        ref[j] = random();
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

BOOST_AUTO_TEST_CASE(throwExceptionIfIndexOfDistribIsOutOfRangeInGetWeight)
{
  initConfig();
  const uint32_t DISTRIB_CNT = 512;
  DiagonalModel model(*def_config, DISTRIB_CNT);
  BOOST_CHECK_THROW(model.getDistribWeight(-1), out_of_range);
  BOOST_CHECK_THROW(model.getDistribWeight(DISTRIB_CNT + 1), out_of_range);

}

BOOST_AUTO_TEST_CASE(throwExceptionIfIndexOfDistribIsOutOfRangeInSetWeight)
{
  initConfig();
  const uint32_t DISTRIB_CNT = 197;
  DiagonalModel model(*def_config, DISTRIB_CNT);
  BOOST_CHECK_THROW(model.setDistribWeight(-1, 0.1), out_of_range);
  BOOST_CHECK_THROW(model.setDistribWeight(DISTRIB_CNT + 1, 0.1), out_of_range);

}

BOOST_AUTO_TEST_CASE(getCorrectWeightIfIndexOfDistributionIsCorrect)
{
  initConfig();
  const uint32_t DISTRIB_CNT = 100;
  DiagonalModel model(*def_config, DISTRIB_CNT);
  BOOST_CHECK_NO_THROW(model.setDistribWeight(DISTRIB_CNT - 1, 0.5));
  BOOST_CHECK_EQUAL(model.getDistribWeight(DISTRIB_CNT - 1), 0.5);
}


BOOST_AUTO_TEST_CASE(throwExceptionIfIndexOfDistribIsOutOfRangeInGetMean)
{
  initConfig();
  const uint32_t DISTRIB_CNT = 512;
  DiagonalModel model(*def_config, DISTRIB_CNT);
  BOOST_CHECK_THROW(model.getDistribMean(-1), out_of_range);
  BOOST_CHECK_THROW(model.getDistribMean(DISTRIB_CNT + 1), out_of_range);

}

BOOST_AUTO_TEST_CASE(throwExceptionIfIndexOfDistribIsOutOfRangeInSetMean)
{
  initConfig();
  const uint32_t DISTRIB_CNT = 197;
  DiagonalModel model(*def_config, DISTRIB_CNT);

  BOOST_CHECK_THROW(model.setDistribMean(-1, RealVector<double>(FEATURE_SIZE)), out_of_range);
  BOOST_CHECK_THROW(model.setDistribMean(DISTRIB_CNT + 1, RealVector<double>(FEATURE_SIZE)), out_of_range);

}

BOOST_AUTO_TEST_CASE(throwExceptionIfSizeOfSettedMeanIsIncorrect)
{
  initConfig();
  const uint32_t DISTRIB_CNT = 197;
  DiagonalModel model(*def_config, DISTRIB_CNT);
  RealVector<double> vec(FEATURE_SIZE - 2);
  BOOST_CHECK_THROW(model.setDistribMean(1, vec), domain_error);

}


BOOST_AUTO_TEST_CASE(getCorrectMeanIfIndexOfDistributionIsCorrect)
{
  initConfig();
  const uint32_t DISTRIB_CNT = 100;
  DiagonalModel model(*def_config, DISTRIB_CNT);
  RealVector<double> correct_mean(FEATURE_SIZE), ret;
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
  initConfig();
  const uint32_t DISTRIB_CNT = 512;
  DiagonalModel model(*def_config, DISTRIB_CNT);
  BOOST_CHECK_THROW(model.getDistribCovariance(-1), out_of_range);
  BOOST_CHECK_THROW(model.getDistribCovariance(DISTRIB_CNT + 1), out_of_range);

}

BOOST_AUTO_TEST_CASE(throwExceptionIfIndexOfDistribIsOutOfRangeInSetCovariance)
{
  initConfig();
  const uint32_t DISTRIB_CNT = 197;
  DiagonalModel model(*def_config, DISTRIB_CNT);

  BOOST_CHECK_THROW(model.setDistribCovariance(-1, RealVector<double>(FEATURE_SIZE)), out_of_range);
  BOOST_CHECK_THROW(model.setDistribCovariance(DISTRIB_CNT + 1, RealVector<double>(FEATURE_SIZE)), out_of_range);

}

BOOST_AUTO_TEST_CASE(throwExceptionIfSizeOfSettedCovarianceIsIncorrect)
{
  initConfig();
  const uint32_t DISTRIB_CNT = 197;
  DiagonalModel model(*def_config, DISTRIB_CNT);
  RealVector<double> vec(FEATURE_SIZE - 2);
  BOOST_CHECK_THROW(model.setDistribCovariance(1, vec), domain_error);

}


BOOST_AUTO_TEST_CASE(getCorrectCovarianceIfIndexOfDistributionIsCorrect)
{
  initConfig();
  const uint32_t DISTRIB_CNT = 100;
  DiagonalModel model(*def_config, DISTRIB_CNT);
  RealVector<double> correct_cov(FEATURE_SIZE), ret;
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

BOOST_AUTO_TEST_CASE(throwExceptionIfIndexOfDistribIsOutOfRangeInCountLikehood)
{
  initConfig();
  const uint32_t DISTRIB_CNT = 10, FEATURE_SIZE_NOW = 2;
  DiagonalModel model(*def_config, DISTRIB_CNT);
  RealVector<double> mean(FEATURE_SIZE_NOW), cov(FEATURE_SIZE_NOW);
  Feature f(FEATURE_SIZE_NOW);
  for(uint32_t i=0; i< FEATURE_SIZE_NOW; ++i)
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

  BOOST_CHECK_THROW(model.countLikehoodWithWeight(f, -1), out_of_range);
  BOOST_CHECK_THROW(model.countLikehoodWithWeight(f, DISTRIB_CNT + 1), out_of_range);


}

BOOST_AUTO_TEST_CASE(countCorrectLikehoodOneDistribWithWeightIfParametersAreCorrect)
{
  initConfig();
  const uint32_t DISTRIB_CNT = 10, FEATURE_SIZE_NOW = 2;
  DiagonalModel model(*def_config, DISTRIB_CNT);
  RealVector<double> mean(FEATURE_SIZE_NOW), cov(FEATURE_SIZE_NOW);
  Feature f(FEATURE_SIZE_NOW);
  for(uint32_t i=0; i< FEATURE_SIZE_NOW; ++i)
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
  /*teraz powinnismy otrzymac w każdej dystrybucji rozkład normalny
    pomnożony przez wagę równą 1/DISTRIB_CNT
  */
  DistribGD distrib(FEATURE_SIZE_NOW);
  distrib.setMeanVect(mean);
  distrib.getCovVect() = cov;
  distrib.computeAll();
  /* Dla wektora cech, zawierającego same zera powinnismy uzyskać wartość == 0.4*/
  BOOST_CHECK_CLOSE(distrib.computeLK(f), 0.4, 0.0001);
  double likehood = distrib.computeLK(f) * (1/DISTRIB_CNT);
  /*waga * gęstość z jednej dystrybucji  */
  BOOST_CHECK_CLOSE(model.countLikehoodWithWeight(f, 0), likehood, 0.0001);

}

BOOST_AUTO_TEST_CASE(countCorrectLikehoodAllDistribIfParametersAreCorrect)
{
  initConfig();
  const uint32_t DISTRIB_CNT = 10, FEATURE_SIZE_NOW = 2;
  DiagonalModel model(*def_config, DISTRIB_CNT);
  RealVector<double> mean(FEATURE_SIZE_NOW), cov(FEATURE_SIZE_NOW);
  Feature f(FEATURE_SIZE_NOW);
  for(uint32_t i=0; i< FEATURE_SIZE_NOW; ++i)
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
  /*teraz powinnismy otrzymac w każdej dystrybucji rozkład normalny
    pomnożony przez wagę równą 1/DISTRIB_CNT
  */
  DistribGD distrib(FEATURE_SIZE_NOW);
  distrib.setMeanVect(mean);
  distrib.getCovVect() = cov;
  distrib.computeAll();
  /* Dla wektora cech, zawierającego same zera powinnismy uzyskać wartość == 0.4*/
  BOOST_CHECK_CLOSE(distrib.computeLK(f), 0.4, 0.0001);
  double likehood = distrib.computeLK(f);
  /*waga * gęstość z jednej dystrybucji * ilość dystrybucji */
  double summary_likehood = (1/DISTRIB_CNT) * likehood * DISTRIB_CNT;
  BOOST_CHECK_CLOSE(model.countLikehoodWithWeight(f), summary_likehood, 0.0001);

}








BOOST_AUTO_TEST_SUITE_END()




#endif
