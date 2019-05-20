#include "learning_performer_test.hpp"

using namespace std;
using namespace alize;
using namespace boost;
using namespace utils;

class LearningPerformerMock: public LearningPerformer
{
public:
  LearningPerformerMock() :LearningPerformer()
  {}

  const LearningThread& startLearningMock(std::shared_ptr<GmmModel> m,
                                      std::unique_ptr<LearningAlgo> &&algo,
                                      std::vector<alize::Feature> &f_vec,
                                      uint32_t iter_cnt )
  {
    LearningPerformer::startLearning(m, std::move(algo), f_vec, iter_cnt);
    return l_thread_list_.back();
  }

  /**
   * @brief removeDoneThreads Wykonuje metodę protected LearningPerformer::removeDoneThreads
   * Używa się jej do testów tej metody protected
   */
  void removeDoneThreads()
  {
    LearningPerformer::removeDoneThreads();
  }

  const std::list<LearningThread>& getList()const
  {
    return l_thread_list_;
  }

  ~LearningPerformerMock() override = default;

};

BOOST_AUTO_TEST_SUITE( LearningPerformerTest )


BOOST_AUTO_TEST_CASE(correctlyRunLearningOfTwoModelsAndCheckStateMethod)
{
  uint32_t DISTRIB_CNT = 10, F_SIZE = 3, TEST_DISTRIB_NUM = 0;
  std::shared_ptr<GmmModel> model1 = make_shared<DiagonalModel>(DISTRIB_CNT, F_SIZE),
      model2 = make_shared<DiagonalModel>(DISTRIB_CNT*2, F_SIZE);

  auto begin_distrib_mean1 = model1->getDistribMean(TEST_DISTRIB_NUM),
      begin_distrib_mean2 = model2->getDistribMean(TEST_DISTRIB_NUM);

  std::vector<Feature> f_vec = {
    toFeature({0, 1.2, -0.3}),
     toFeature({0, 1.2, -0.3}),
     toFeature({-2.4, 1.2, -0.3})
  };

  LearningPerformerMock performer;

  std::vector<std::shared_ptr<GmmModel>> models;
  models.push_back(model1);
  models.push_back(model2);

  uint32_t ITERS = 4;
  auto thread1 = performer.startLearningMock(models[0],make_unique<ExpectationMaximalizationAlgo>(),
      f_vec, ITERS );
  auto thread2 = performer.startLearningMock(models[1],make_unique<ExpectationMaximalizationAlgo>(),
      f_vec, ITERS );
  sleep(3);//po takim czasie uczenie powinno sie zakonczyc

  BOOST_REQUIRE(performer.getList().front().isDone());
  BOOST_REQUIRE(performer.getList().back().isDone());

  //sprawdzenie, czy zmieniły się parametry modelu
  BOOST_REQUIRE_EQUAL(thread1.getModelPtr().get(), models[0].get());
  BOOST_CHECK_EQUAL(thread1.getModelPtr()->getDistribMean(TEST_DISTRIB_NUM)[0],
                      models[0]->getDistribMean(TEST_DISTRIB_NUM)[0]);
  BOOST_CHECK_EQUAL(thread1.getModelPtr()->getDistribMean(TEST_DISTRIB_NUM)[1],
                      models[0]->getDistribMean(TEST_DISTRIB_NUM)[1]);
  BOOST_CHECK_EQUAL(thread1.getModelPtr()->getDistribMean(TEST_DISTRIB_NUM)[2],
                      models[0]->getDistribMean(TEST_DISTRIB_NUM)[2]);

  BOOST_CHECK_NE(thread1.getModelPtr()->getDistribMean(TEST_DISTRIB_NUM)[0],
                      begin_distrib_mean1[0]);
  BOOST_CHECK_NE(thread1.getModelPtr()->getDistribMean(TEST_DISTRIB_NUM)[1],
                      begin_distrib_mean1[1]);
  BOOST_CHECK_NE(thread1.getModelPtr()->getDistribMean(TEST_DISTRIB_NUM)[2],
                      begin_distrib_mean1[2]);

  //sprawdzanie parametrow drugiego modelu
  BOOST_REQUIRE_EQUAL(thread2.getModelPtr().get(), models[1].get());
  BOOST_CHECK_EQUAL(thread2.getModelPtr()->getDistribMean(TEST_DISTRIB_NUM)[0],
                      models[1]->getDistribMean(TEST_DISTRIB_NUM)[0]);
  BOOST_CHECK_EQUAL(thread2.getModelPtr()->getDistribMean(TEST_DISTRIB_NUM)[1],
                      models[1]->getDistribMean(TEST_DISTRIB_NUM)[1]);
  BOOST_CHECK_EQUAL(thread2.getModelPtr()->getDistribMean(TEST_DISTRIB_NUM)[2],
                      models[1]->getDistribMean(TEST_DISTRIB_NUM)[2]);

  BOOST_CHECK_NE(thread2.getModelPtr()->getDistribMean(TEST_DISTRIB_NUM)[0],
                      begin_distrib_mean2[0]);
  BOOST_CHECK_NE(thread2.getModelPtr()->getDistribMean(TEST_DISTRIB_NUM)[1],
                      begin_distrib_mean2[1]);
  BOOST_CHECK_NE(thread2.getModelPtr()->getDistribMean(TEST_DISTRIB_NUM)[2],
                      begin_distrib_mean2[2]);
}

BOOST_AUTO_TEST_CASE(throwLearningModelWithoutFeaturesAtRunLearningWithNoFeatureVector)
{
  uint32_t DISTRIB_CNT = 10, F_SIZE = 3, ITERS = 2;
  std::shared_ptr<GmmModel> model = make_shared<DiagonalModel>(DISTRIB_CNT, F_SIZE);

  std::vector<Feature> f_vec;

  LearningPerformer performer;
  BOOST_CHECK_THROW(performer.startLearning(model, make_unique<ExpectationMaximalizationAlgo>(),
                                  f_vec, ITERS),
                    LearningModelWithoutFeatures);
}

BOOST_AUTO_TEST_CASE(throwRerunningLearningThreadAtRunningLearningIfThreadIsLearningNowTheSameModel)
{
  uint32_t DISTRIB_CNT = 10, F_SIZE = 3;
  std::shared_ptr<GmmModel> model = make_shared<DiagonalModel>(DISTRIB_CNT, F_SIZE);

  std::vector<Feature> f_vec = {
    toFeature({0, 1.2, -0.3}),
     toFeature({0, 1.2, -0.3}),
     toFeature({-2.4, 1.2, -0.3})
  };

  LearningPerformer p;

  uint32_t ITERS = 10;
  BOOST_REQUIRE_NO_THROW(p.startLearning(model, make_unique<ExpectationMaximalizationAlgo>(),
                                     f_vec, ITERS));
  BOOST_CHECK_THROW(p.startLearning(model, make_unique<ExpectationMaximalizationAlgo>(),
                                     f_vec, ITERS), RerunningLearningThread);
  sleep(3);//po to, aby uruchomiony wątek skonczyl sie wykonac
  //inaczej straci dostęp do swojej struktury(na stosie)
  //i będzie odwoływał się do nie swojej pamięci

}

BOOST_AUTO_TEST_CASE(removeOnlyDoneThreadsFromInternalThreadListIfThereIs2ThreadDoneAnd2Working)
{
  uint32_t DISTRIB_CNT = 10, F_SIZE = 3;
  std::shared_ptr<GmmModel> model_done1 = make_shared<DiagonalModel>(DISTRIB_CNT, F_SIZE),
      model_done2 = make_shared<DiagonalModel>(DISTRIB_CNT, F_SIZE),
      model_working1 = make_shared<DiagonalModel>(DISTRIB_CNT, F_SIZE),
      model_working2 = make_shared<DiagonalModel>(DISTRIB_CNT, F_SIZE);

  std::vector<Feature> f_vec = {
    toFeature({0, 1.2, -0.3}),
     toFeature({0, 1.2, -0.3}),
     toFeature({-2.4, 1.2, -0.3})
  };

  LearningPerformerMock p;

  BOOST_REQUIRE_NO_THROW(p.startLearning(model_done1, make_unique<ExpectationMaximalizationAlgo>(),
                                     f_vec, 4));
  BOOST_REQUIRE_NO_THROW(p.startLearning(model_done2, make_unique<ExpectationMaximalizationAlgo>(),
                                     f_vec, 4));
  sleep(3);//powinny skonczyc prace

  //teraz uruchomimy 2 nowe z dużą ilościa iteracji -
  //nie powinny skonczyc na tyle szybko, by skonczyc sie wykonywac
  BOOST_REQUIRE_NO_THROW(p.startLearning(model_working1, make_unique<ExpectationMaximalizationAlgo>(),
                                     f_vec, 50));
  BOOST_CHECK_EQUAL(p.getList().size(),1);//startLearning woła removeDoneThreads -
  //wiec zostanie tylko właśnie uruchomiony wątek

  BOOST_REQUIRE_NO_THROW(p.startLearning(model_working2, make_unique<ExpectationMaximalizationAlgo>(),
                                     f_vec, 50));

  const uint32_t TH_WORKING = 2;
  BOOST_CHECK_EQUAL(p.getList().size(),TH_WORKING);

  sleep(3);//2 pozostałe powinny sie wykonać
  p.removeDoneThreads();
  BOOST_CHECK_EQUAL(p.getList().size(), 0);
}





BOOST_AUTO_TEST_SUITE_END()
