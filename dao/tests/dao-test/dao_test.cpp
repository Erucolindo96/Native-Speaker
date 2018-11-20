#ifndef DIAGONAL_TEST
#define DIAGONAL_TEST

#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE dao_test
#include<boost/test/unit_test.hpp>
#include "dao/FileModelDao.hpp"
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

static const uint32_t DISTRIB_CNT = 100, FEATURE_SIZE = 10;
static const double EPSILON = 0.0001;
static const RealVector<double> w = toRealVector({0.1179,9.1176e-07,0.3269,0.0190,0.3382,
                                            0.0005,0.1896,0.0080,1.1646e-08,1.9747e-07});
static const vector<RealVector<double>> means =
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


void initModel(GmmModel &model)
{
  for(uint32_t i=0; i < DISTRIB_CNT; ++i)
  {
    model.setDistribWeight(i, w[i]);
    model.setDistribMean(i, means[i]);
    model.setDistribCovariance(i, diag_cov[i]);
  }
}

void checkMeans(GmmModel &model,const vector<RealVector<double>> &correct_means)
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

void checkCovariances(GmmModel &model, const vector<RealVector<double>> &correct_diag_cov)
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

void checkWeights(GmmModel &model,const RealVector<double> &correct_weights)
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



BOOST_AUTO_TEST_SUITE( FileModelDaoTests )

BOOST_AUTO_TEST_CASE( getCorrectModelFileTypeIfThatWasSetInContructor )
{
  FileModelDao dao(RAW);
  BOOST_CHECK_EQUAL(dao.getFileType(), RAW);
}

BOOST_AUTO_TEST_CASE( getCorrectModelFileTypeIfThatWasSetInSetter )
{
  FileModelDao dao;
  BOOST_REQUIRE_NO_THROW(dao.setFileType(RAW));
  BOOST_CHECK_EQUAL(dao.getFileType(), RAW);
}

BOOST_AUTO_TEST_CASE( getCorrectMixtureSaveDirectoryIfThatWasSetInSetter )
{
  FileModelDao dao;
  BOOST_REQUIRE_NO_THROW(dao.setMixtureDir("folder"));
  BOOST_CHECK_EQUAL(dao.getMixtureDir(), "folder");
}

BOOST_AUTO_TEST_CASE(contructCorrectCopyOfDaoIfMixtureDirAndFileTypeWasSet)
{
  FileModelDao dao(XML);
  dao.setMixtureDir("/sciezka/folderu");
  FileModelDao copy = dao;
  BOOST_CHECK_EQUAL(copy.getFileType(), dao.getFileType());
  BOOST_CHECK_EQUAL(copy.getMixtureDir(), dao.getMixtureDir());
}

BOOST_AUTO_TEST_CASE(correctAssignOfDaoIfMixtureDirAndFileTypeWasSet)
{
  FileModelDao dao(RAW);
  dao.setMixtureDir("/sciezka/folderu");
  FileModelDao copy;
  BOOST_REQUIRE_NO_THROW(copy = dao);
  BOOST_CHECK_EQUAL(copy.getFileType(), dao.getFileType());
  BOOST_CHECK_EQUAL(copy.getMixtureDir(), dao.getMixtureDir());
}

BOOST_AUTO_TEST_CASE(correctMoveContructionOfDaoIfMixtureDirAndFileTypeWasSet)
{
  FileModelDao dao(RAW);
  dao.setMixtureDir("/sciezka/folderu");
  FileModelDao copy(std::move(dao));
  BOOST_CHECK_EQUAL(copy.getFileType(), RAW);
  BOOST_CHECK_EQUAL(copy.getMixtureDir(), "/sciezka/folderu");
}


BOOST_AUTO_TEST_CASE(correctMoveAssignmentOfDaoIfMixtureDirAndFileTypeWasSet)
{
  FileModelDao dao(RAW);
  dao.setMixtureDir("/sciezka/folderu");
  FileModelDao copy;
  BOOST_REQUIRE_NO_THROW(copy = std::move(dao));
  BOOST_CHECK_EQUAL(copy.getFileType(), RAW);
  BOOST_CHECK_EQUAL(copy.getMixtureDir(), "/sciezka/folderu");
}

BOOST_AUTO_TEST_CASE(throwFileNotFoundExceptionwhileReadingIfModelDirArentExist)
{
  FileModelDao dao(XML);
  dao.setMixtureDir("test_dao");

  std::unique_ptr<GmmModel> model_ptr;
  BOOST_CHECK_THROW(model_ptr = dao.readModel("model_testowy"), FileNotFound);

}

BOOST_AUTO_TEST_CASE(throwModelNameNotDefinedWhileReadIfModelNameIsEmpty)
{
  FileModelDao dao(XML);
  dao.setMixtureDir("test_dao");

  std::unique_ptr<GmmModel> model_ptr;
  BOOST_CHECK_THROW(model_ptr = dao.readModel(""), ModelNameNotDefined);

}

BOOST_AUTO_TEST_CASE(throwModelNameNotDefinedWhileWriteIfModelHaveEmptyName)
{
  FileModelDao dao(XML);
  dao.setMixtureDir("test_dao");

  DiagonalModel model(DISTRIB_CNT, FEATURE_SIZE);
  BOOST_CHECK_THROW(dao.writeModel(model), ModelNameNotDefined );
}

/*
BOOST_AUTO_TEST_CASE(throwDirNotDefinedWhileReadIfDaoHaventSettedDir)
{
  FileModelDao dao(XML);

  std::unique_ptr<GmmModel> model_ptr;
  BOOST_CHECK_THROW(model_ptr = dao.readModel("model1"), DirNotDefined);
}

BOOST_AUTO_TEST_CASE(throwDirNotDefinedWhileWriteIfDaoHaventSettedDir)
{
  FileModelDao dao(XML);

  DiagonalModel model(DISTRIB_CNT, FEATURE_SIZE);
  BOOST_CHECK_THROW(dao.writeModel(model), DirNotDefined);
}
*/






BOOST_AUTO_TEST_CASE(saveModelToFileIfModelDirAndFileTypeWasSet)
{
  FileModelDao dao(XML);
  dao.setMixtureDir("test_dao");
  bool not_created = system("[-e test_dao] || mkdir test_dao");
  BOOST_REQUIRE(!not_created);

  DiagonalModel model(DISTRIB_CNT, FEATURE_SIZE);
  initModel(model);
  model.setName("model_testowy");

  dao.writeModel(model);
  bool not_exist = system("cat model_testowy");
  BOOST_CHECK(!not_exist);
}


BOOST_AUTO_TEST_CASE(readCorrectModelFromFileIfModelDirExistWithSavedModel)
{
  bool not_exist = system("cat model_testowy");
  BOOST_REQUIRE(!not_exist);

  FileModelDao dao(XML);
  dao.setMixtureDir("test_dao");

  std::unique_ptr<GmmModel> model_ptr;
  BOOST_REQUIRE_NO_THROW(model_ptr = dao.readModel("model_testowy"));
  BOOST_CHECK_EQUAL(model_ptr->getName(), "model_testowy");
  checkWeights(*model_ptr, w);
  checkMeans(*model_ptr, means);
  checkCovariances(*model_ptr, diag_cov);
  system("[-e test_dao] && rm -d -r test_dao");

}

BOOST_AUTO_TEST_SUITE_END()












#endif
