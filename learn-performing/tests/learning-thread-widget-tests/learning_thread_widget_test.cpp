#include "learning_thread_widget_test.hpp"

using namespace std;
using namespace alize;
using namespace boost;
using namespace utils;


BOOST_AUTO_TEST_SUITE( LearningThreadWidgetTest )

BOOST_AUTO_TEST_CASE(correctlySetGmmModelAndGetPtrToIt)
{
  LearningThreadWidget w;
  const uint32_t F_SIZE = 12, D_CNT  = 20;
  std::shared_ptr<GmmModel> ptr = make_shared<DiagonalModel>(D_CNT, F_SIZE);
  w.setModelPtr(ptr);
  BOOST_CHECK_EQUAL(w.getModelPtr(), ptr);
}

BOOST_AUTO_TEST_CASE(correctlySetModelNameAndGetIt)
{
  LearningThreadWidget w;
  QString name = "model1";
  w.setModelName(name);
  BOOST_CHECK_EQUAL(w.getModelName().toStdString(), name.toStdString());
}

BOOST_AUTO_TEST_CASE(correctlySetIterCntAndGetIt)
{
  LearningThreadWidget w;
  uint32_t iter_cnt = 20;
  w.setIterCnt(iter_cnt);
  BOOST_CHECK_EQUAL(w.getIterCnt(), iter_cnt);
}

BOOST_AUTO_TEST_CASE(correctlySetActIterAndGetItIfIterCntWasSet)
{
  LearningThreadWidget w;
  uint32_t iter_cnt = 20, act_iter = 3;
  w.setIterCnt(iter_cnt);
  w.setActualIter(act_iter);
  BOOST_CHECK_EQUAL(w.getActualIter(), act_iter);
}

//BOOST_AUTO_TEST_CASE(correctlySetActIterIfItWasGreaterThanIterCntAndGetZero)
//{
//  LearningThreadWidget w;
//  uint32_t iter_cnt = 0, act_iter = 25;
//  w.setIterCnt(iter_cnt);
//  w.setActualIter(act_iter);
//  BOOST_CHECK_EQUAL(w.getActualIter(), iter_cnt);
//}






BOOST_AUTO_TEST_SUITE_END()
