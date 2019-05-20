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
//  void setActModelDisplayed(QString act_model)
//  {
//    act_displayed_name_ = act_model;
//  }
  void removeDoneThreads()
  {
    LearningController::removeDoneThreads();
  }

public slots:
  void actualizeProgressBarByLearningThread(const QString model_name, const qint32 act_iter, const qint32 iter_cnt)
  {
    LearningController::actualizeProgressBarByLearningThread(model_name, act_iter, iter_cnt);
  }
  void actualizeProgressBarByMainThread()
  {
    LearningController::actualizeProgressBarByMainThread();
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

BOOST_AUTO_TEST_CASE(fillComboBoxWithNamesOfLearningModelsAtStartLearning)
{
  const uint32_t ITER_CNT = 10, DISTRIB_CNT = 10,
      F_SIZE = 3;
  const string NAME = "model1", NAME2 = "model2";
  QComboBox box;
  QProgressBar bar;
  bar.setMaximum(20);
  bar.setValue(10);
  std::vector<alize::Feature> f_vec = {
    toFeature({0, 1.2, -0.3}),
    toFeature({0, 1.2, -0.3}),
    toFeature({-2.4, 1.2, -0.3})
  };

  LearningControllerMock c;
  BOOST_CHECK_NO_THROW(c.setComboBoxPtr(&box));
  BOOST_CHECK_NO_THROW(c.setProgressBarPtr(&bar));
  shared_ptr<GmmModel> model = make_shared<DiagonalModel>( DISTRIB_CNT,F_SIZE),
      model2 = make_shared<DiagonalModel>( DISTRIB_CNT,F_SIZE);
  model->setName(NAME);
  model2->setName(NAME2);


  BOOST_CHECK_NO_THROW(c.startLearning(model, make_unique<ExpectationMaximalizationAlgo>(),
                                       f_vec, ITER_CNT));
  BOOST_CHECK_NO_THROW(c.startLearning(model2, make_unique<ExpectationMaximalizationAlgo>(),
                                       f_vec, ITER_CNT));
  sleep(3);
  BOOST_CHECK_EQUAL(box.itemText(0).toStdString(), NAME );
  BOOST_CHECK_EQUAL(box.itemText(1).toStdString(), NAME2 );

}

BOOST_AUTO_TEST_CASE(correctlyUpdateProgressBarByMainWindowWithoutRunningThreads)
{
  const uint32_t ITER_CNT = 10, ACT_ITER = 2, DISTRIB_CNT = 10,
      F_SIZE = 3;
  const string NAME = "model1", NAME2 = "model2";
  QComboBox box;
  QProgressBar bar;
  bar.setMaximum(20);
  bar.setValue(10);

  LearningControllerMock c;
  BOOST_CHECK_NO_THROW(c.setComboBoxPtr(&box));
  BOOST_CHECK_NO_THROW(c.setProgressBarPtr(&bar));
  shared_ptr<GmmModel> model = make_shared<DiagonalModel>( DISTRIB_CNT,F_SIZE),
      model2 = make_shared<DiagonalModel>( DISTRIB_CNT, F_SIZE);
  model->setName(NAME);
  model2->setName(NAME2);
  LearningThread t(model);
  LearningThread t2(model2);

  t.incrementIter();
  t.incrementIter();
  t.setIterCnt(ITER_CNT);
  BOOST_REQUIRE_EQUAL(t.getIter(), ACT_ITER);
  c.addLearningThreadToList(std::move(t ));
  c.addLearningThreadToList(std::move(t2));

  box.addItems({NAME.c_str(), NAME2.c_str()});//dodajemy ręcznie, bo dodawanie nazw modeli uczonych jest przeprowadzzane w startLearning()
  //a jego tu nie wołamy
  c.actualizeProgressBarByMainThread();
  BOOST_CHECK_EQUAL(bar.value(), ACT_ITER);
}

BOOST_AUTO_TEST_CASE(correctlyUpdateProgressBarByMainWindowButLikeThreadWithoutRunningThreads)
{
  const uint32_t ITER_CNT = 10, ACT_ITER = 2, DISTRIB_CNT = 10,
      F_SIZE = 3;
  const string NAME = "model1", NAME2 = "model2";
  QComboBox box;
  QProgressBar bar;
  bar.setMaximum(20);
  bar.setValue(10);

  LearningControllerMock c;
  BOOST_CHECK_NO_THROW(c.setComboBoxPtr(&box));
  BOOST_CHECK_NO_THROW(c.setProgressBarPtr(&bar));
  shared_ptr<GmmModel> model = make_shared<DiagonalModel>( DISTRIB_CNT,F_SIZE),
      model2 = make_shared<DiagonalModel>( DISTRIB_CNT, F_SIZE);
  model->setName(NAME);
  model2->setName(NAME2);

  LearningThread t(model);
  LearningThread t2(model2);

  t.incrementIter();
  t.incrementIter();
  t.setIterCnt(ITER_CNT);
  BOOST_REQUIRE_EQUAL(t.getIter(), ACT_ITER);
  c.addLearningThreadToList(std::move(t2));
  c.addLearningThreadToList(std::move(t ));

  box.addItems({NAME.c_str(), NAME2.c_str()});//dodajemy ręcznie, bo dodawanie nazw modeli uczonych jest przeprowadzzane w startLearning()
  //a jego tu nie wołamy
  //c.setActModelDisplayed(NAME.c_str());
  c.actualizeProgressBarByLearningThread(c.getLastThread().getModelPtr()->getName().c_str(),
                                         c.getLastThread().getIter(), c.getLastThread().getIterCnt());
  BOOST_CHECK_EQUAL(bar.value(), ACT_ITER);
}

BOOST_AUTO_TEST_CASE(correctlyCleanComboBoxAtRemovingDoneThreadsItThreadsAreDone)
{
  const uint32_t ITER_CNT = 10, DISTRIB_CNT = 10,
      F_SIZE = 3;
  const string NAME = "model1", NAME2 = "model2";
  QComboBox box;
  QProgressBar bar;
  bar.setMaximum(20);
  bar.setValue(10);
  std::vector<alize::Feature> f_vec = {
    toFeature({0, 1.2, -0.3}),
    toFeature({0, 1.2, -0.3}),
    toFeature({-2.4, 1.2, -0.3})
  };

  LearningControllerMock c;
  BOOST_CHECK_NO_THROW(c.setComboBoxPtr(&box));
  BOOST_CHECK_NO_THROW(c.setProgressBarPtr(&bar));
  shared_ptr<GmmModel> model = make_shared<DiagonalModel>( DISTRIB_CNT,F_SIZE),
      model2 = make_shared<DiagonalModel>( DISTRIB_CNT, F_SIZE);
  model->setName(NAME);
  model2->setName(NAME2);

//  LearningThread t(model);
  LearningThread t2(model2);
//  t.run(make_unique<ExpectationMaximalizationAlgo>(), f_vec,
//        ITER_CNT);
  c.startLearning(model, make_unique<ExpectationMaximalizationAlgo>(), f_vec,
                  ITER_CNT);
  sleep(2);
//  BOOST_REQUIRE(t.isDone());
  BOOST_REQUIRE(!t2.isDone());
  BOOST_REQUIRE(c.getLastThread().isDone());

  c.addLearningThreadToList(std::move(t2));
  //c.addLearningThreadToList(std::move(t ));

  box.addItems({NAME2.c_str()});//dodajemy ręcznie, bo dodawanie nazw modeli uczonych jest przeprowadzzane w startLearning()
  //a jego tu nie wołamy dla t2
  //c.setActModelDisplayed(NAME.c_str());
  BOOST_REQUIRE_EQUAL(box.count(), 2);
  c.removeDoneThreads();
  BOOST_CHECK_EQUAL(box.count(), 1);

}



//BOOST_AUTO_TEST_CASE(correctlyPerformLearningAndUpdateComboBoxAndProgressBar)
//{
//  const uint32_t ITER_CNT = 10, ACT_ITER = 2, DISTRIB_CNT = 10,
//      F_SIZE = 3;
//  const string NAME = "model1", NAME2 = "model2";
//  QComboBox box;
//  QProgressBar bar;
//  bar.setMaximum(20);
//  bar.setValue(10);

//  std::vector<alize::Feature> f_vec = {
//    toFeature({0, 1.2, -0.3}),
//    toFeature({0, 1.2, -0.3}),
//    toFeature({-2.4, 1.2, -0.3})
//  };

//  LearningController c;
//  BOOST_CHECK_NO_THROW(c.setComboBoxPtr(&box));
//  BOOST_CHECK_NO_THROW(c.setProgressBarPtr(&bar));
//  shared_ptr<GmmModel> model = make_shared<DiagonalModel>(F_SIZE, DISTRIB_CNT, NAME),
//      model2 = make_shared<DiagonalModel>(F_SIZE, DISTRIB_CNT, NAME2);

//  BOOST_CHECK_NO_THROW(c.startLearning(model, make_unique<ExpectationMaximalizationAlgo>(),
//                  f_vec, ITER_CNT));
//  BOOST_CHECK_NO_THROW(c.startLearning(model2, make_unique<ExpectationMaximalizationAlgo>(),
//                  f_vec, ITER_CNT));
//  BOOST_CHECK_NE(box.count(), 0);
//  sleep(3);


//}


BOOST_AUTO_TEST_SUITE_END()
