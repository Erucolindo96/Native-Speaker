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

const double EPSILON = 0.001;

static vector<Feature> training_vec;
static unique_ptr<ExpectationMaximalizationAlgo> algo;
static unique_ptr<DiagonalModel> model;

void initModel()
{
  RealVector<double> w = toRealVector({0.1179,9.1176e-07,0.3269,0.0190,0.3382,
                                       0.0005,0.1896,0.0080,1.1646e-08,1.9747e-07});

  vector<RealVector<double>> means =
  {
    toRealVector({0.0956, -1.9443, -1.1682}),
    toRealVector({2.1822, -0.8751, -0.5662}),
    toRealVector({-0.8053, 0.8925, 0.5803}),
    toRealVector({0.0717, -0.3415, 0.3327}),
    toRealVector({-3.3047, 0.2479, 2.0475}),
    toRealVector({0.0423, -1.0254, 0.2716}),
    toRealVector({1.5731, 0.0066, 0.1075}),
    toRealVector({-2.5675, -0.7903, 1.2512}),
    toRealVector({-3.0744, 1.5100, 0.2573}),
    toRealVector({-7.5657, -0.6368, -0.7270})
  }
  , diag_cov =
  {
    toRealVector({0.7084, 2.1100, 0.6456}),
    toRealVector({0.4001, 0.8660, 0.8787}),
    toRealVector({0.4651, 0.7869, 0.5204}),
    toRealVector({0.2381, 0.5247, 0.2334}),
    toRealVector({1.3183, 0.1552, 1.2684}),
    toRealVector({0.7396, 0.3389, 0.7244}),
    toRealVector({4.2471, 0.2853, 0.2328}),
    toRealVector({0.5637, 0.0952, 0.4191}),
    toRealVector({3.5123, 0.4048, 0.5357}),
    toRealVector({25.0547, 1.5978, 2.1099})
  };
  model = make_unique<DiagonalModel>(DISTRIB_CNT, FEATURE_SIZE);
  for(uint32_t i=0; i < DISTRIB_CNT; ++i)
  {
    model->setDistribWeight(i, w[i]);
    model->setDistribMean(i, means[i]);
    model->setDistribCovariance(i, diag_cov[i]);
  }
}

void initAlgo()
{
  algo = make_unique<ExpectationMaximalizationAlgo>();
}

void initTrainigFeatures()
{
  training_vec.push_back(toFeature({0.0898, -0.1913, -1.2639}));
  training_vec.push_back(toFeature({-0.0567, -0.0879, 1.3700}));
  training_vec.push_back(toFeature({0.0342, 0.1964, -0.2233}));
  training_vec.push_back(toFeature({-0.9715, 1.0808, 0.0447}));
  training_vec.push_back(toFeature({0.1006, 0.7065, -0.4112}));
BOOST_REQUIRE_EQUAL(training_vec.size(), FEATURE_CNT);
}

void checkMeans(DiagonalModel &model,const vector<RealVector<double>> &correct_means)
{
  for(uint32_t i = 0; i < DISTRIB_CNT; ++i)
  {
    BOOST_REQUIRE_EQUAL(model.getDistribMean(i).size(), FEATURE_SIZE);
    BOOST_REQUIRE_EQUAL(correct_means[i].size(), FEATURE_SIZE);

    for(uint32_t j = 0; j < FEATURE_SIZE; ++j)
    {
      BOOST_CHECK_SMALL(model.getDistribMean(i)[j] - correct_means[i][j],EPSILON);
      BOOST_CHECK_MESSAGE(abs(model.getDistribMean(i)[j] - correct_means[i][j]) < EPSILON,
                    "srednia nr :" + to_string(i) + ", pozycja nr:"+
                          to_string(j) + "\n");
    }
  }
}

void checkCovariances(DiagonalModel &model, const vector<RealVector<double>> &correct_diag_cov)
{
  for(uint32_t i = 0; i < DISTRIB_CNT; ++i)
  {
    BOOST_REQUIRE_EQUAL(model.getDistribCovariance(i).size(), FEATURE_SIZE);
    BOOST_REQUIRE_EQUAL(correct_diag_cov[i].size(), FEATURE_SIZE);

    for(uint32_t j = 0; j < FEATURE_SIZE; ++j)
    {
      BOOST_CHECK_SMALL(model.getDistribCovariance(i)[j] - correct_diag_cov[i][j],EPSILON);
      BOOST_CHECK_MESSAGE(abs(model.getDistribCovariance(i)[j] - correct_diag_cov[i][j]) < EPSILON,
                          "kowariancja nr :" + to_string(i) + ", pozycja nr:"+
                                to_string(j) + "\n");
    }
  }
}

void checkWeights(DiagonalModel &model,const RealVector<double> &correct_weights)
{
  double sum_weights = 0;
  for(uint32_t i = 0; i < DISTRIB_CNT; ++i)
  {
    BOOST_CHECK_SMALL(model.getDistribWeight(i) - correct_weights[i], EPSILON);
    BOOST_CHECK_MESSAGE(abs(model.getDistribWeight(i) - correct_weights[i]) < EPSILON,
                  "waga nr :" + to_string(i));
    sum_weights += model.getDistribWeight(i);
  }
  const double  SUM_EXPECTED = 1.0;
  BOOST_CHECK_SMALL(sum_weights - SUM_EXPECTED, EPSILON);
}

BOOST_AUTO_TEST_SUITE( initialization )

BOOST_AUTO_TEST_CASE( initialization )
{
  initModel();
  initAlgo();
  initTrainigFeatures();
}


BOOST_AUTO_TEST_SUITE_END()//initialization

BOOST_AUTO_TEST_SUITE( invalid_use )

BOOST_AUTO_TEST_CASE( throwLearningModelWithoutFeaturesExceptionIfTrainingVecInEmpty )
{
  std::vector<Feature> empty_vec;
  BOOST_CHECK_THROW(algo->learnModel(*model, empty_vec, 10), LearningModelWithoutFeaturesException);
}

BOOST_AUTO_TEST_SUITE_END()//invalid_use


BOOST_AUTO_TEST_SUITE( iterations_of_em_algo )

BOOST_AUTO_TEST_CASE( prepareCorrectFirstIterationOfLearningIfModelInitialatedAsAbove )
{

  double previous_lk = model->countLikehoodWithWeight(training_vec[0]);
  BOOST_REQUIRE_NO_THROW(algo->learnModel(*model, training_vec, 1));


  RealVector<double> weights_expected = toRealVector({0.1933,1.4974e-08 ,0.5528,0.0482,0.0113,
                                                  0.0005, 0.1939, 0.00001, 3.0684e-09, 2.7300e-08});
  vector<RealVector<double>> means_expected =
  {
    toRealVector({0.0835, -0.1022, -1.1378}),
    toRealVector({0.0829, -0.0595, -1.0238}),
    toRealVector({-0.3243, 0.5079, 0.2748}),
    toRealVector({0.0156, 0.2340, 0.1553}),
    toRealVector({-0.0973, 0.0192, 1.1079}),
    toRealVector({0.0277, -0.0910, -0.1318}),
    toRealVector({0.0141, 0.3529, -0.2514}),
    toRealVector({-0.0564, -0.0876, 1.3645}),
    toRealVector({-0.5759, 0.8877, -0.0867}),
    toRealVector({0.0271, 0.0228, -0.7135})
  },
  diag_cov_expected =
  {
    toRealVector({0.0044, 3.4570, 0.1165}),
    toRealVector({4.4076, 0.7480, 0.4827}),
    toRealVector({0.4548, 0.4017, 0.6672}),
    toRealVector({0.0165, 0.4257, 0.6431}),
    toRealVector({10.3357, 0.1447,1.2643}),
    toRealVector({0.0055, 0.9002, 1.6496}),
    toRealVector({2.4726, 0.2253, 0.3641}),
    toRealVector({6.3055, 0.4939, 0.0249}),
    toRealVector({6.5035, 0.4770, 0.2203}),
    toRealVector({57.6950, 0.5731, 0.7276})
  };

  checkWeights(*model, weights_expected);
  checkMeans(*model, means_expected);
  checkCovariances(*model, diag_cov_expected);

  BOOST_CHECK_GE(model->countLikehoodWithWeight(training_vec[0]), previous_lk);
}


BOOST_AUTO_TEST_CASE( prepareCorrectSecondIterationOfLearningIfModelInitialatedAsAbove )
{

  double previous_lk = model->countLikehoodWithWeight(training_vec[0]);
  algo->learnModel(*model, training_vec, 1);

  RealVector<double> weights_expected = toRealVector({2.3955e-01,1.9606e-09,4.9558e-01,1.5898e-01,3.1592e-03,
                                                      1.3891e-03, 1.0133e-01, 2.4812e-05, 1.4020e-09, 1.4510e-09});
  vector<RealVector<double>> means_expected =
  {
    toRealVector({0.0897, -0.0156, -1.0723}),
    toRealVector({-0.1214, 0.4089, -0.4750}),
    toRealVector({-0.3302, 0.5169, 0.2561}),
    toRealVector({0.0161, 0.1913, 0.3091}),
    toRealVector({-0.0502, -0.0315, 1.1220}),
    toRealVector({0.0163, 0.1463, 0.2570}),
    toRealVector({-0.2071, 0.5718, -0.1964}),
    toRealVector({-0.0567, -0.0879, 1.3700}),
    toRealVector({-0.6147, 0.8787, -0.0815}),
    toRealVector({-0.2123, 0.4838, -0.2286})
  },
  diag_cov_expected =
  {
    toRealVector({0.0002, 0.1271, 0.1382}),
    toRealVector({0.2084, 0.4317, 0.5431}),
    toRealVector({0.2247, 0.2416, 0.4994}),
    toRealVector({0.0039, 0.0946, 0.7406}),
    toRealVector({0.0112, 0.0335, 0.3667}),
    toRealVector({0.0040, 0.1432, 0.9784}),
    toRealVector({0.2552, 0.1986, 0.1239}),
    toRealVector({1.0e-04*0.0010, 1.0e-04* 0.0009, 1.0e-04*0.3054}),
    toRealVector({0.2471, 0.1015, 0.0426}),
    toRealVector({0.2641, 0.4243, 0.5753})
  };

  checkWeights(*model, weights_expected);
  checkMeans(*model, means_expected);
  checkCovariances(*model, diag_cov_expected);

  BOOST_CHECK_GE(model->countLikehoodWithWeight(training_vec[0]), previous_lk);

}


BOOST_AUTO_TEST_SUITE_END()//iterations_of_em_algo




#endif
