#include "learning_controler_test.hpp"
 using namespace std;
 using namespace alize;

 using namespace utils;
class LearningControllerMock: public LearningController
{
public:
  LearningControllerMock() = default;

  ~LearningControllerMock()override  = default;

  void addLearningThreadToList(LearningThread &&t)
  {
    l_thread_list_.push_back(std::move(t));
  }
  LearningThread& getLastThread()
  {
    return l_thread_list_.back();
  }


};


BOOST_AUTO_TEST_SUITE( LearningControllerTests )

BOOST_AUTO_TEST_CASE(correctlyChangeComboBoxPtr)
{
  QComboBox box1, box2;
  LearningController c;
  BOOST_CHECK_NO_THROW(c.setComboBoxPtr(&box1));
  BOOST_CHECK_NO_THROW(c.setComboBoxPtr(&box2));

}


BOOST_AUTO_TEST_CASE(correctlyRunActualizingThreadAndCheckActualizationOfListIfInListAreTwoThreads)
{
  const uint32_t ITER_CNT = 10, ACT_ITER = 2, THREAD_CNT = 1, DISTRIB_CNT = 10,
      F_SIZE = 3;
  const string NAME = "model1";
  QComboBox box;
  QProgressBar bar;
  LearningControllerMock c;
  shared_ptr<GmmModel> model = make_shared<DiagonalModel>(F_SIZE, DISTRIB_CNT);
  model->setName(NAME);
  LearningThread t(model);
  LearningThread t2(model);

  t.incrementIter();
  t.incrementIter();
  t.setIterCnt(ITER_CNT);
  t2.setIterCnt(ITER_CNT);

  BOOST_REQUIRE_EQUAL(t.getIter(), ACT_ITER);

  c.addLearningThreadToList(std::move(t ));
  c.addLearningThreadToList(std::move(t2));

  BOOST_CHECK_NO_THROW(c.setComboBoxPtr(&box));
  BOOST_CHECK_NO_THROW(c.setProgressBarPtr(&bar));

  BOOST_REQUIRE_NO_THROW(c.runDisplayThread());
  this_thread::sleep_for(std::chrono::seconds(1));//poczekaj az wątek zaktualizuje liste
  BOOST_CHECK_EQUAL(box.count(), THREAD_CNT);

  box.setCurrentIndex(1);
  box.setCurrentIndex(0);
  //powinnismy wywolac sygnal zmieniający aktualny element
  this_thread::sleep_for(std::chrono::seconds(1));//zeby wątek zdążył zaktualizować dane
  BOOST_CHECK_EQUAL(bar.value(), ACT_ITER);
  BOOST_CHECK_EQUAL(bar.maximum(), ITER_CNT);
  BOOST_CHECK_EQUAL(box.currentText().toStdString(), NAME );
}




BOOST_AUTO_TEST_CASE(correctlyRunActualizingThreadAndCheckActualizationOfThreadIterIfInListAreTwoThreadsAndOneWasRunned)
{
  const uint32_t ITER_CNT = 10, ACT_ITER = 2, THREAD_CNT = 1, DISTRIB_CNT = 10,
      F_SIZE = 3;
  const string NAME = "model1";
  std::vector<alize::Feature> f_vec = {
    toFeature({0, 1.2, -0.3}),
     toFeature({0, 1.2, -0.3}),
     toFeature({-2.4, 1.2, -0.3})
  };

  QComboBox box;
  QProgressBar bar;
  LearningControllerMock c;
  shared_ptr<GmmModel> model = make_shared<DiagonalModel>(F_SIZE, DISTRIB_CNT);
  LearningThread t(model);
  LearningThread t_done(model);

  t.incrementIter();
  t.incrementIter();
  t.setIterCnt(ITER_CNT);
  //t_done.run(make_unique<ExpectationMaximalizationAlgo>(), f_vec, ITER_CNT);

  BOOST_REQUIRE_EQUAL(t.getIter(), ACT_ITER);
  c.addLearningThreadToList(std::move(t ));
  c.addLearningThreadToList(std::move(t_done));

  c.setComboBoxPtr(&box);
  c.setProgressBarPtr(&bar);

  BOOST_REQUIRE_NO_THROW(c.runDisplayThread());
  this_thread::sleep_for(std::chrono::seconds(1));
  //poczekaj az wątek zaktualizuje liste
  BOOST_REQUIRE_EQUAL(box.count(), THREAD_CNT);

  box.setCurrentIndex(1);
  //powinnismy wywolac sygnal zmieniający aktualny element
  this_thread::sleep_for(std::chrono::seconds(1));//zeby wątek zdążył zaktualizować dane
  BOOST_CHECK_EQUAL(bar.value(), 0);
  BOOST_CHECK_EQUAL(bar.maximum(), 0);
  BOOST_CHECK_EQUAL(box.currentText().toStdString(), NAME );
  c.getLastThread().run(make_unique<ExpectationMaximalizationAlgo>(), f_vec, ITER_CNT);
  //zaczekaj az skonczy uczyc

  this_thread::sleep_for(std::chrono::seconds(2));
  BOOST_CHECK_EQUAL(bar.value(), ITER_CNT);
  BOOST_CHECK_EQUAL(bar.maximum(), ITER_CNT);
  BOOST_CHECK_EQUAL(box.currentText().toStdString(), NAME );



}




//BOOST_AUTO_TEST_CASE(throwRerunningThreadAtRunDisplayThreadIfThisOneWasRunned)
//{
//  QListWidget w_list;
//  LearningControllerMock c;
//  shared_ptr<GmmModel> model = make_shared<DiagonalModel>(12, 100);

//  BOOST_CHECK_NO_THROW(c.setListWidgetPtr(&w_list));

//  BOOST_REQUIRE_NO_THROW(c.runDisplayThread());
//  BOOST_CHECK_THROW(c.runDisplayThread(), RerunningThread);
//}

BOOST_AUTO_TEST_SUITE_END()
