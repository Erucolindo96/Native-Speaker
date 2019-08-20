#include "models/tests/verificator-test/verificator_test.hpp"


class DiagonalModelMock:public DiagonalModel
{

protected:
  double lk_;
public:

  DiagonalModelMock() = delete;
  explicit DiagonalModelMock(uint32_t distrib_cnt, uint32_t feature_size)
    :DiagonalModel(distrib_cnt, feature_size)
  {}
  explicit DiagonalModelMock(uint32_t distrib_cnt, uint32_t feature_size, const std::string &name)
    :DiagonalModel(distrib_cnt, feature_size, name)
  {}
  void setComputedLk(double lk)
  {
    lk_ = lk;
  }

  double countLikehoodWithWeight(const alize::Feature &arg)const override
  {
    return lk_;
  }




};

using namespace std;
using namespace boost;
using namespace alize;



BOOST_AUTO_TEST_SUITE(VerificatorTest)

BOOST_AUTO_TEST_CASE(ConstructCorrectVerificatorFromThreshold)
{
  const double THRESHOLD = 15.5;
  BOOST_CHECK_NO_THROW(Verificator v(THRESHOLD));
  Verificator v(THRESHOLD);
  BOOST_CHECK_EQUAL(v.getThreshold(), THRESHOLD);

}

BOOST_AUTO_TEST_CASE(ConstructCorrectDefaultVerificator)
{
  const double DEF_THRESHOLD = 0.0;
  BOOST_CHECK_NO_THROW(Verificator v);
  Verificator v;
  BOOST_CHECK_EQUAL(v.getThreshold(), DEF_THRESHOLD);

}

BOOST_AUTO_TEST_CASE(ConstructCorrectVerificatorFromAnotherIfAnotherIsValid)
{
  const double THRESHOLD = 15.5;
  Verificator v(THRESHOLD);
  Verificator other(v);
  BOOST_CHECK_EQUAL(v.getThreshold(), THRESHOLD);
  BOOST_CHECK_EQUAL(other.getThreshold(), THRESHOLD);
}

BOOST_AUTO_TEST_CASE(CorrectAssignVerificatorFromAnotherIfAnotherIsValid)
{
  const double THRESHOLD = 15.5;
  Verificator v(THRESHOLD);
  Verificator other;
  other = v;
  BOOST_CHECK_EQUAL(v.getThreshold(), THRESHOLD);
  BOOST_CHECK_EQUAL(other.getThreshold(), THRESHOLD);
}

BOOST_AUTO_TEST_CASE(AvoidSelfAssignment)
{
  const double THRESHOLD = 15.5;
  Verificator v(THRESHOLD);
  Verificator other;
  BOOST_CHECK_NO_THROW(v = v);
  BOOST_CHECK_EQUAL(v.getThreshold(), THRESHOLD);
}

BOOST_AUTO_TEST_CASE(ConstructCorrectVerificatorByMoveContructorIfAnotherIsValid)
{
  const double THRESHOLD = 15.5;
  Verificator v(THRESHOLD);
  Verificator other(std::move(v));
  BOOST_CHECK_EQUAL(other.getThreshold(), THRESHOLD);
}

BOOST_AUTO_TEST_CASE(CorrectMoveAssignVerificatorFromAnotherIfAnotherIsValid)
{
  const double THRESHOLD = 15.5;
  Verificator v(THRESHOLD);
  Verificator other;
  other = std::move(v);
  BOOST_CHECK_EQUAL(other.getThreshold(), THRESHOLD);
}

BOOST_AUTO_TEST_CASE(AvoidSelfMoveAssignment)
{
  const double THRESHOLD = 15.5;
  Verificator v(THRESHOLD);
  Verificator other;
  BOOST_CHECK_NO_THROW(v = v);
  BOOST_CHECK_EQUAL(v.getThreshold(), THRESHOLD);
}

BOOST_AUTO_TEST_CASE(GetCorrectThresholdIfItWasSet)
{
  const double THRESHOLD = 15.5;
  Verificator v;
  BOOST_CHECK_NO_THROW(v.setThreshold(THRESHOLD));
  BOOST_CHECK_EQUAL(v.getThreshold(), THRESHOLD);
}


BOOST_AUTO_TEST_CASE(throwInvalidFeatureSizeIfVerificatedAndUbmModelVectorSizeAreNotEqual)
{
  const uint32_t FEATURE_SIZE = 12, DISTRIB_CNT = 100, FEATURE_CNT = 20;
  const double THRESHOLD = 2.5;

  DiagonalModel model(FEATURE_SIZE, DISTRIB_CNT),
      ubm(FEATURE_SIZE + 1, DISTRIB_CNT);
  std::vector<Feature> features;

  for(uint32_t i = 0; i< FEATURE_CNT; ++i)
  {
    features.push_back(utils::toFeature({-7.123748, -0.490637, -1.437211,
                                         -0.833934, -0.797512, -0.988563,
                                         0.253725, -0.247003, 0.302838,
                                         -0.060661, -0.204023, -0.304669})
                       );//nie mają znaczenia ich wartości, ważne, żeby była odpowiednia ilość
    //Modele są mockami, można w nich ustawić odpowiednią wartośc podobieństwa
  }
  Verificator verificator;
  verificator.setThreshold(THRESHOLD);
  BOOST_CHECK_THROW(verificator.verifyModel(model,features, ubm), InvalidFeatureSize);

}

BOOST_AUTO_TEST_CASE(throwInvalidFeatureSizeIfVerificatedAndUbmModelVectorSizeAreEqualAndSomeFeaturesSizesNotEquals)
{
  const uint32_t FEATURE_SIZE = 12, DISTRIB_CNT = 100, FEATURE_CNT = 100;
  const double THRESHOLD = 2.5;

  DiagonalModel model(FEATURE_SIZE, DISTRIB_CNT),
      ubm(FEATURE_SIZE, DISTRIB_CNT);
  std::vector<Feature> features;
  for(uint32_t i = 0; i< FEATURE_CNT; ++i)
  {
    if(i < FEATURE_CNT/2) //połowa wektorów cech jest poprawna
    {
      features.push_back(utils::toFeature({-7.123748, -0.490637, -1.437211,
                                           -0.833934, -0.797512, -0.988563,
                                           0.253725, -0.247003, 0.302838,
                                           -0.060661, -0.204023, -0.304669})
                         );//normalna ilość elementów
    }
    features.push_back(utils::toFeature({-7.123748, -0.490637, -1.437211,
                                         -0.833934, -0.797512, -0.988563,
                                         0.253725, -0.247003, 0.302838,
                                         -0.060661, -0.204023, -0.304669,
                                         -0.060661, -0.204023, -0.304669})
                       );//o 3 elementy więcej niż VectorSize w modelach
  }
  Verificator verificator;
  verificator.setThreshold(THRESHOLD);
  BOOST_CHECK_THROW(verificator.verifyModel(model,features, ubm), InvalidFeatureSize);

}


BOOST_AUTO_TEST_CASE(throwVerifyModelWithoutFeaturesIfFeatureVectorInEmpty)
{
  const uint32_t FEATURE_SIZE = 12, DISTRIB_CNT = 100;
  const double THRESHOLD = 2.5;
  DiagonalModel model(FEATURE_SIZE, DISTRIB_CNT),
      ubm(FEATURE_SIZE, DISTRIB_CNT);
  std::vector<Feature> features;
  Verificator verificator;
  verificator.setThreshold(THRESHOLD);
  BOOST_CHECK_THROW(verificator.verifyModel(model,features, ubm), VerifyModelWithoutFeatures);

}

BOOST_AUTO_TEST_CASE(CorrectVerifyModelIfLikehoodOfAllFeaturesAreComputingCorrectly)
{
  const uint32_t FEATURE_SIZE = 12, FEATURE_CNT = 10, DISTRIB_CNT = 100;
  const double THRESHOLD = 2;
  std::vector<Feature> features;

  for(uint32_t i = 0; i< FEATURE_CNT; ++i)
  {
    features.push_back(utils::toFeature({-7.123748, -0.490637, -1.437211,
                                         -0.833934, -0.797512, -0.988563,
                                         0.253725, -0.247003, 0.302838,
                                         -0.060661, -0.204023, -0.304669})
                       );//nie mają znaczenia ich wartości, ważne, żeby była odpowiednia ilość
    //Modele są mockami, można w nich ustawić odpowiednią wartośc podobieństwa
  }
  DiagonalModelMock model(DISTRIB_CNT, FEATURE_SIZE);
  DiagonalModelMock ubm(DISTRIB_CNT, FEATURE_SIZE);
  double EXPECTED_LK_MODEL = 100;//log(100*10)= 6,9078
  double EXPECTED_LK_UBM = 7.5;//log(7,5*10) = 4,3175
  model.setComputedLk(EXPECTED_LK_MODEL);
  ubm.setComputedLk(EXPECTED_LK_UBM);

  Verificator verificator;
  verificator.setThreshold(THRESHOLD);
  BOOST_CHECK_EQUAL(verificator.verifyModel(model,features, ubm), true);
  EXPECTED_LK_MODEL = 10;//log(10*10)= 4,6052
  EXPECTED_LK_UBM = 75;//log(75*10) = 6,6201
  model.setComputedLk(EXPECTED_LK_MODEL);
  ubm.setComputedLk(EXPECTED_LK_UBM);

  BOOST_CHECK_EQUAL(verificator.verifyModel(model,features, ubm), false);


}

BOOST_AUTO_TEST_SUITE_END()
