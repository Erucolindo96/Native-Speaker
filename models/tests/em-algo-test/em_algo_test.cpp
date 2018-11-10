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

const double EPS = 0.0001;

static vector<Feature> training_vec;
static unique_ptr<ExpectationMaximalizationAlgo> algo;
static unique_ptr<DiagonalModel> model;

void initModel()
{
  RealVector<double> w = toRealVector({0.1179,0.0000,0.3269,0.0190,0.3382,
                                       0.0005,0.1896,0.0080,0.0000,0.0000});

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
  training_vec.push_back(toFeature({-0.718, 0.5266, -0.3104}));
  training_vec.push_back(toFeature({0.0342, 0.1964, -0.2233}));
  training_vec.push_back(toFeature({-0.9715, 1.0808, 0.0447}));
  training_vec.push_back(toFeature({0.1006, 0.7065, -0.4112}));
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
  initModel();
  initAlgo();
  initTrainigFeatures();
}


BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE( invalid_use )

BOOST_AUTO_TEST_CASE( throwLearningModelWithoutFeaturesExceptionIfTrainingVecInEmpty )
{
  std::vector<Feature> empty_vec;
  BOOST_CHECK_THROW(algo->learnModel(*model, empty_vec, 10), LearningModelWithoutFeaturesException);
}

BOOST_AUTO_TEST_SUITE_END()//invalid_use


BOOST_AUTO_TEST_SUITE( iteration_of_em_algo )

BOOST_AUTO_TEST_CASE( prepareCorrectFirstIterationOfLearningIfModelInitialatedAsAbove )
{
  algo->learnModel(*model, training_vec, 1);
  RealVector<double> weights_expected = toRealVector({0.2023,0.0000,0.4972,0.0476,0.0025,
                                                      0.0003, 0.2500, 0.0000, 0.0000, 0.0000});
  vector<RealVector<double>> means_expected =
  {
    toRealVector({0.0766, -0.0726, -1.1048}),
    toRealVector({0.0806, -0.0378, -1.0537}),
    toRealVector({-0.3575, 0.7097, -0.2171}),
    toRealVector({0.0123, 0.4058, -0.3185}),
    toRealVector({-0.2458, 0.5657, -0.2770}),
    toRealVector({0.0718, -0.0621, -1.0142}),
    toRealVector({-0.0059, 0.4196, -0.3405}),
    toRealVector({0.0572, 0.0300, -0.6849}),
    toRealVector({-0.5133, 0.8542, -0.1464}),
    toRealVector({0.0267, 0.0852, -0.9068})
  },
  diag_cov_expected =
  {
    toRealVector({0.0054, 3.5815, 0.1306}),
    toRealVector({4.4177, 0.7946, 0.3921}),
    toRealVector({0.4381, 0.1572, 0.7093}),
    toRealVector({0.0176, 0.6183, 0.4569}),
    toRealVector({9.5487, 0.2489, 5.5030}),
    toRealVector({0.0034, 0.9878, 1.8421}),
    toRealVector({2.5272, 0.2472, 0.2574}),
    toRealVector({6.8901, 0.7134, 4.0146}),
    toRealVector({6.8153, 0.5082, 0.2157}),
    toRealVector({57.6894, 0.6809, 0.2616})
  };

  checkWeights(*model, weights_expected);
  checkMeans(*model, means_expected);
  checkCovariances(*model, diag_cov_expected);
}


BOOST_AUTO_TEST_CASE( prepareCorrectSecondIterationOfLearningIfModelInitialatedAsAbove )
{
  algo->learnModel(*model, training_vec, 1);
  RealVector<double> weights_expected = toRealVector({0.2377,0.0000,0.4731,0.1331,0.0002,
                                                      0.0006, 0.1553, 0.0000, 0.0000, 0.0000});
  vector<RealVector<double>> means_expected =
  {
    toRealVector({0.0856, -0.0298, -1.0624}),
    toRealVector({-0.0625, 0.3096, -0.5687}),
    toRealVector({-0.3384, 0.7077, -0.1981}),
    toRealVector({0.0241, 0.3774, -0.3546}),
    toRealVector({-0.3142, 0.6405, -0.2345}),
    toRealVector({0.0670, 0.1994, -0.6109}),
    toRealVector({-0.1748, 0.5508, -0.2512}),
    toRealVector({-0.2117, 0.4819, -0.3614}),
    toRealVector({-0.4755, 0.7694, -0.1357}),
    toRealVector({-0.0673, 0.3532, -0.5153})
  },
  diag_cov_expected =
  {
    toRealVector({0.0006, 0.1060, 0.1472}),
    toRealVector({0.1221, 0.3001, 0.4717}),
    toRealVector({0.2280, 0.1053, 0.0426}),
    toRealVector({0.0043, 0.0660, 0.0619}),
    toRealVector({0.2296, 0.1513, 0.0854}),
    toRealVector({0.0012, 0.1828, 0.3753}),
    toRealVector({0.1860, 0.1281, 0.0505}),
    toRealVector({0.2616, 0.3927, 0.2776}),
    toRealVector({0.2490, 0.1273, 0.0380}),
    toRealVector({0.1109, 0.2408, 0.3628})
  };

  checkWeights(*model, weights_expected);
  checkMeans(*model, means_expected);
  checkCovariances(*model, diag_cov_expected);
}


BOOST_AUTO_TEST_SUITE_END()




#endif
