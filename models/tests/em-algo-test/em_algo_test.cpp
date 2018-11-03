#ifndef DIAGONAL_TEST
#define DIAGONAL_TEST

#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE em_algo_test
#include<boost/test/unit_test.hpp>
#include "models/learning_algo.hpp"
#include "models/diagonal_model.hpp"
#include <typeinfo>
#include <random>
#include<iostream>
#include"utils/utils.hpp"

using namespace boost;
using namespace std;
using namespace alize;
using namespace utils;


const uint32_t FEATURE_SIZE = 3;
const uint32_t DISTRIB_CNT = 10;
const uint32_t FEATURE_CNT = 5;

const double EPS = 0.00001;

static Config def_config;
//static unique_ptr<Config> def_config("config");
static vector<Feature> training_vec;
static unique_ptr<ExpectationMaximalizationAlgo> algo;
static unique_ptr<DiagonalModel> model;


void initConfig()
{
  def_config.setParam("vectSize", to_string(FEATURE_SIZE).c_str());
  def_config.setParam("mixtureDistribCount", to_string(DISTRIB_CNT).c_str());
  def_config.setParam("maxLLK", "100");
  def_config.setParam("minLLK", "-100");
  def_config.setParam("featureServerMemAlloc", "1000000");
}
void initModel()
{
  RealVector<double> w = convert({0.5,0.5,0.5,0.5,0.5,0.3,0.3,0.3,0.3,0.3});

  vector<RealVector<double>> means, diag_cov;
  model = make_unique<DiagonalModel>(def_config);
  for(uint32_t i=0; i < DISTRIB_CNT; ++i)
  {
    model->setDistribWeight(i, w[i]);
    model->setDistribMean(i, convert({0.0,0.0,0.0}));
    model->setDistribCovariance(i, convert({1.0, 1.0, 1.0}));
  }
}

void initAlgo()
{
  algo = make_unique<ExpectationMaximalizationAlgo>();
}

void initTrainigFeatures()
{
  Feature f = convert(std::vector<double>({1.0,10.1,-1.0}));
  training_vec.push_back();
}

void checkMeans(DiagonalModel &model, vector<RealVector<double>> correct_means)
{
  for(uint32_t i = 0; i < DISTRIB_CNT; ++i)
  {
    BOOST_REQUIRE_EQUAL(model.getDistribMean(i).size(), FEATURE_SIZE);
    BOOST_REQUIRE_EQUAL(correct_means[i].size(), FEATURE_SIZE);

    for(uint32_t j = 0; j < FEATURE_SIZE; ++j)
    {
      BOOST_CHECK_CLOSE(model.getDistribMean(i)[j] ,correct_means[i][j],EPS);
    }
  }
}

void checkCovariances(DiagonalModel &model, vector<RealVector<double>> correct_diag_cov)
{
  for(uint32_t i = 0; i < DISTRIB_CNT; ++i)
  {
    BOOST_REQUIRE_EQUAL(model.getDistribCovariance(i).size(), FEATURE_SIZE);
    BOOST_REQUIRE_EQUAL(correct_diag_cov[i].size(), FEATURE_SIZE);

    for(uint32_t j = 0; j < FEATURE_SIZE; ++j)
    {
      BOOST_CHECK_CLOSE(model.getDistribCovariance(i)[j] ,correct_diag_cov[i][j],EPS);
    }
  }
}

void checkWeights(DiagonalModel &model, RealVector<double> correct_weights)
{
  for(uint32_t i = 0; i < DISTRIB_CNT; ++i)
  {
    BOOST_CHECK_CLOSE(model.getDistribWeight(i), correct_weights[i], EPS);
  }
}

BOOST_AUTO_TEST_SUITE( initialization )

BOOST_AUTO_TEST_CASE( initialization )
{
  initConfig();
  initModel();
  initAlgo();
  initTrainigFeatures();
}


BOOST_AUTO_TEST_SUITE_END()



BOOST_AUTO_TEST_SUITE( iteration_of_em_algo )

BOOST_AUTO_TEST_CASE( prepareCorrectOneIterationOfLearningIfModelInitialatedAsAbove )
{
  //model->learnModelUsingLearnAlgo(algo);
  //model->learnModel();
  algo->performOneIteration(*model,training_vec);
  RealVector<double> weights_expected = convert({0.125,0.125,0.125,0.125,0.125, 0.075, 0.075, 0.075, 0.075, 0.075});
  vector<RealVector<double>> means_expected(DISTRIB_CNT, RealVector<double>(DISTRIB_CNT, DISTRIB_CNT) ),
      diag_cov_expected(DISTRIB_CNT, RealVector<double>(DISTRIB_CNT, DISTRIB_CNT));
  for(uint32_t i = 0; i < DISTRIB_CNT; ++i)
  {
    means_expected[i] = convert({-0.1637, 0.4638, -0.4328});
    diag_cov_expected[i] = convert({0.1937, 0.4039, 0.3830});
  }

  checkWeights(*model, weights_expected);
  checkMeans(*model, means_expected);
  checkCovariances(*model, diag_cov_expected);
}


BOOST_AUTO_TEST_SUITE_END()




#endif
