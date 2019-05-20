#include "learning_thread_test.hpp"
using namespace std;
using namespace alize;
using namespace boost;
using namespace utils;


BOOST_AUTO_TEST_SUITE( LearningThreadTest )

BOOST_AUTO_TEST_CASE(correctlySetGmmModelAndGetReferenceToIt)
{
  uint32_t DISTRIB_CNT = 100, F_SIZE = 20;
  std::shared_ptr<GmmModel> model = make_shared<DiagonalModel>(DISTRIB_CNT, F_SIZE);

  BOOST_REQUIRE_NO_THROW(LearningThread t(model));
  LearningThread t(model);
  BOOST_CHECK_EQUAL(t.getModelPtr().get(), model.get());

}


BOOST_AUTO_TEST_CASE(correctlyIncrementIterCounter)
{

  uint32_t DISTRIB_CNT = 100, F_SIZE = 20;
  std::shared_ptr<GmmModel> model = make_shared<DiagonalModel>(DISTRIB_CNT, F_SIZE);

  LearningThread t(model);
  BOOST_CHECK_EQUAL(t.getIter(), 0);
  BOOST_REQUIRE_NO_THROW(t.incrementIter());
  BOOST_CHECK_EQUAL(t.getIter(), 1);
  BOOST_REQUIRE_NO_THROW(t.incrementIter());
  BOOST_CHECK_EQUAL(t.getIter(), 2);

}
BOOST_AUTO_TEST_CASE(correctlySetAndGetIterCnt)
{

  uint32_t DISTRIB_CNT = 100, F_SIZE = 20, ITERS = 20;
  std::shared_ptr<GmmModel> model = make_shared<DiagonalModel>(DISTRIB_CNT, F_SIZE);

  LearningThread t(model);
  BOOST_CHECK_EQUAL(t.getIterCnt(), 0);
  BOOST_REQUIRE_NO_THROW(t.setIterCnt(ITERS));
  BOOST_CHECK_EQUAL(t.getIterCnt(), ITERS);

}

BOOST_AUTO_TEST_CASE(correctlyCopyClass_WithoutIterCounterAndThreadSettings)
{
  uint32_t DISTRIB_CNT = 100, F_SIZE = 20, ITERS = 19;
  std::shared_ptr<GmmModel> model = make_shared<DiagonalModel>(DISTRIB_CNT, F_SIZE);

  BOOST_REQUIRE_NO_THROW(LearningThread t(model));
  LearningThread t(model);
  t.setIterCnt(ITERS);
  t.incrementIter();
  t.incrementIter();

  LearningThread copy(t);
  BOOST_CHECK_EQUAL(t.getModelPtr().get(), copy.getModelPtr().get());
  BOOST_REQUIRE_EQUAL(t.getIter(), 2);
  BOOST_CHECK_EQUAL(copy.getIter(), 0);

  BOOST_CHECK_EQUAL(t.getIterCnt(), ITERS);
  BOOST_CHECK_EQUAL(copy.getIterCnt(), 0);
}


BOOST_AUTO_TEST_CASE(correctlyMoveClass_WithIterCounterAndThreadSettings)
{
  uint32_t DISTRIB_CNT = 100, F_SIZE = 20, ITERS = 29;
  std::shared_ptr<GmmModel> model = make_shared<DiagonalModel>(DISTRIB_CNT, F_SIZE);

  BOOST_REQUIRE_NO_THROW(LearningThread t(model));
  LearningThread t(model);
  t.setIterCnt(ITERS);

  t.incrementIter();
  t.incrementIter();
  uint32_t t_iter_cnt = t.getIter();
  std::shared_ptr<GmmModel> t_model_ptr = t.getModelPtr();

  LearningThread copy(std::move(t));
  BOOST_CHECK_EQUAL(t_model_ptr.get(), copy.getModelPtr().get());
  BOOST_CHECK_EQUAL(t_iter_cnt, copy.getIter());

  BOOST_CHECK_EQUAL(copy.getIterCnt(), ITERS);
}


BOOST_AUTO_TEST_CASE(correctlyMoveAssingingWithIterCounterAndThreadSettings)
{
  uint32_t DISTRIB_CNT = 100, F_SIZE = 20, ITERS = 87;
  std::shared_ptr<GmmModel> model = make_shared<DiagonalModel>(DISTRIB_CNT, F_SIZE);

  BOOST_REQUIRE_NO_THROW(LearningThread t(model));
  LearningThread t(model);
  t.setIterCnt(ITERS);
  t.incrementIter();
  t.incrementIter();

  uint32_t t_iter_cnt = t.getIter();
  std::shared_ptr<GmmModel> t_model_ptr = t.getModelPtr();

  LearningThread copy(nullptr);
  copy.incrementIter();
  BOOST_REQUIRE_EQUAL(copy.getIter(), 1);

  copy = std::move(t);

  BOOST_CHECK_EQUAL(t_model_ptr.get(), copy.getModelPtr().get());
  BOOST_CHECK_EQUAL(t_iter_cnt, copy.getIter());
  BOOST_CHECK_EQUAL(copy.getIterCnt(), ITERS);

}

BOOST_AUTO_TEST_CASE(correctlyPerformLearningAndCheckStateMethod)
{
  uint32_t DISTRIB_CNT = 10, F_SIZE = 3, TEST_DISTRIB_NUM = 0;
  std::shared_ptr<GmmModel> model = make_shared<DiagonalModel>(DISTRIB_CNT, F_SIZE);
  auto begin_distrib_mean = model->getDistribMean(TEST_DISTRIB_NUM);
  std::vector<Feature> f_vec = {
    toFeature({0, 1.2, -0.3}),
     toFeature({0, 1.2, -0.3}),
     toFeature({-2.4, 1.2, -0.3})
  };

  BOOST_REQUIRE_NO_THROW(LearningThread t(model));
  LearningThread t(model);

  BOOST_CHECK(!t.isDone());
  uint32_t ITERS = 2;
  BOOST_REQUIRE_NO_THROW(LearningThread::learningOperation(t, make_unique<ExpectationMaximalizationAlgo>(),
                                     f_vec, ITERS));
  BOOST_CHECK_EQUAL(t.getIter(), ITERS);
  BOOST_CHECK_EQUAL(t.getIterCnt(), ITERS);
  BOOST_CHECK(!t.isDone());//ponieważ nie został uruchomiony drugi wątek
  //sprawdzenie, czy zmieniły się parametry modelu
  BOOST_REQUIRE_EQUAL(t.getModelPtr().get(), model.get());
  BOOST_CHECK_EQUAL(t.getModelPtr()->getDistribMean(TEST_DISTRIB_NUM)[0],
                      model->getDistribMean(TEST_DISTRIB_NUM)[0]);
  BOOST_CHECK_EQUAL(t.getModelPtr()->getDistribMean(TEST_DISTRIB_NUM)[1],
                      model->getDistribMean(TEST_DISTRIB_NUM)[1]);
  BOOST_CHECK_EQUAL(t.getModelPtr()->getDistribMean(TEST_DISTRIB_NUM)[2],
                      model->getDistribMean(TEST_DISTRIB_NUM)[2]);

  BOOST_CHECK_NE(t.getModelPtr()->getDistribMean(TEST_DISTRIB_NUM)[0],
                      begin_distrib_mean[0]);
  BOOST_CHECK_NE(t.getModelPtr()->getDistribMean(TEST_DISTRIB_NUM)[1],
                      begin_distrib_mean[1]);
  BOOST_CHECK_NE(t.getModelPtr()->getDistribMean(TEST_DISTRIB_NUM)[2],
                      begin_distrib_mean[2]);

}

BOOST_AUTO_TEST_CASE(throwLearningModelWithoutFeaturesAtPerformingLearningWithNoFeatureVector)
{
  uint32_t DISTRIB_CNT = 10, F_SIZE = 3, ITERS = 2;
  std::shared_ptr<GmmModel> model = make_shared<DiagonalModel>(DISTRIB_CNT, F_SIZE);

  std::vector<Feature> f_vec;

  LearningThread t(model);
  BOOST_CHECK_THROW(LearningThread::learningOperation(t, make_unique<ExpectationMaximalizationAlgo>(),
                                  f_vec, ITERS),
                    LearningModelWithoutFeatures);
}

BOOST_AUTO_TEST_CASE(correctlyRunLearningInOtherThreadAndCheckStateMethod)
{
  uint32_t DISTRIB_CNT = 10, F_SIZE = 3, TEST_DISTRIB_NUM = 0;
  std::shared_ptr<GmmModel> model = make_shared<DiagonalModel>(DISTRIB_CNT, F_SIZE);
  auto begin_distrib_mean = model->getDistribMean(TEST_DISTRIB_NUM);
  std::vector<Feature> f_vec = {
    toFeature({0, 1.2, -0.3}),
     toFeature({0, 1.2, -0.3}),
     toFeature({-2.4, 1.2, -0.3})
  };

  BOOST_REQUIRE_NO_THROW(LearningThread t(model));
  LearningThread t(model);


  BOOST_CHECK(!t.isDone());
  uint32_t ITERS = 2;
  BOOST_REQUIRE_NO_THROW(t.run(make_unique<ExpectationMaximalizationAlgo>(),
                                     f_vec, ITERS));
  sleep(3);
  BOOST_CHECK_EQUAL(t.getIterCnt(), ITERS);
  BOOST_CHECK_EQUAL(t.getIter(), ITERS);
  BOOST_CHECK(t.isDone());
  //sprawdzenie, czy zmieniły się parametry modelu
  BOOST_REQUIRE_EQUAL(t.getModelPtr().get(), model.get());
  BOOST_CHECK_EQUAL(t.getModelPtr()->getDistribMean(TEST_DISTRIB_NUM)[0],
                      model->getDistribMean(TEST_DISTRIB_NUM)[0]);
  BOOST_CHECK_EQUAL(t.getModelPtr()->getDistribMean(TEST_DISTRIB_NUM)[1],
                      model->getDistribMean(TEST_DISTRIB_NUM)[1]);
  BOOST_CHECK_EQUAL(t.getModelPtr()->getDistribMean(TEST_DISTRIB_NUM)[2],
                      model->getDistribMean(TEST_DISTRIB_NUM)[2]);

  BOOST_CHECK_NE(t.getModelPtr()->getDistribMean(TEST_DISTRIB_NUM)[0],
                      begin_distrib_mean[0]);
  BOOST_CHECK_NE(t.getModelPtr()->getDistribMean(TEST_DISTRIB_NUM)[1],
                      begin_distrib_mean[1]);
  BOOST_CHECK_NE(t.getModelPtr()->getDistribMean(TEST_DISTRIB_NUM)[2],
                      begin_distrib_mean[2]);

}

BOOST_AUTO_TEST_CASE(throwLearningModelWithoutFeaturesAtRunLearningWithNoFeatureVector)
{
  uint32_t DISTRIB_CNT = 10, F_SIZE = 3, ITERS = 2;
  std::shared_ptr<GmmModel> model = make_shared<DiagonalModel>(DISTRIB_CNT, F_SIZE);

  std::vector<Feature> f_vec;

  LearningThread t(model);
  BOOST_CHECK_THROW(t.run(make_unique<ExpectationMaximalizationAlgo>(),
                                  f_vec, ITERS),
                    LearningModelWithoutFeatures);
}

BOOST_AUTO_TEST_CASE(throwRerunningLearningThreadAtRunningLearningIfThreadWasRunned)
{
  uint32_t DISTRIB_CNT = 10, F_SIZE = 3, TEST_DISTRIB_NUM = 0;
  std::shared_ptr<GmmModel> model = make_shared<DiagonalModel>(DISTRIB_CNT, F_SIZE);
  auto begin_distrib_mean = model->getDistribMean(TEST_DISTRIB_NUM);
  std::vector<Feature> f_vec = {
    toFeature({0, 1.2, -0.3}),
     toFeature({0, 1.2, -0.3}),
     toFeature({-2.4, 1.2, -0.3})
  };

  LearningThread t(model);

  uint32_t ITERS = 10;
  BOOST_CHECK(!t.isDone());
  BOOST_REQUIRE_NO_THROW(t.run(make_unique<ExpectationMaximalizationAlgo>(),
                                     f_vec, ITERS));
  sleep(3);
  BOOST_CHECK(t.isDone());
  BOOST_CHECK_THROW(t.run(make_unique<ExpectationMaximalizationAlgo>(),
                                     f_vec, ITERS), RerunningLearningThread);
  BOOST_CHECK(t.isDone());
}

//BOOST_AUTO_TEST_CASE(emitSignalIterationCompleteIfEverythingIsOkWithLearning)
//{
//  uint32_t DISTRIB_CNT = 10, F_SIZE = 3;
//  std::shared_ptr<GmmModel> model = make_shared<DiagonalModel>(DISTRIB_CNT, F_SIZE);
//  LearningThread* t = new LearningThread(model);
//  QProgressBar *bar = new QProgressBar();
//  bar->setValue(0);
//  QObject::connect(t, SIGNAL(iterationComplete(int)), bar, SLOT(setValue(int)),
//                   Qt::DirectConnection);

//  std::vector<Feature> f_vec = {
//    toFeature({0, 1.2, -0.3}),
//     toFeature({0, 1.2, -0.3}),
//     toFeature({-2.4, 1.2, -0.3})
//  };

//  uint32_t ITERS = 10;
//  BOOST_CHECK(!t->isDone());
//  BOOST_REQUIRE_NO_THROW(t->run(make_unique<ExpectationMaximalizationAlgo>(),
//                                     f_vec, ITERS));
//  sleep(3);
//  BOOST_CHECK(t->isDone());
//  BOOST_CHECK_EQUAL(bar->value(), ITERS);
//}





BOOST_AUTO_TEST_SUITE_END()
