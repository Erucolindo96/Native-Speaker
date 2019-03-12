#include "model_controller_test.hpp"



BOOST_AUTO_TEST_SUITE( ModelControllerTest )

BOOST_AUTO_TEST_CASE( incrementActPageAtInvoceNextPageIfModelCntIsMoreThanModelsAtPage )
{
  QToolBox box;
  const uint32_t MODELS_CNT = 4, MODELS_AT_PAGE =1;
  ModelController controller(&box, MODELS_AT_PAGE);
  ConfigManager conf;

  conf.setVectSize(12);
  conf.setModelFolder("models");
  controller.loadModels(conf );
  controller.refreshDisplayedModels();

  BOOST_CHECK_EQUAL(controller.getModelsCnt(), MODELS_CNT);
  BOOST_CHECK_EQUAL(controller.getActPage(), 0);
  BOOST_CHECK_EQUAL(box.count(),1);

  BOOST_CHECK_NO_THROW(controller.nextPage());
  BOOST_CHECK_EQUAL(controller.getActPage(), 1);
  BOOST_CHECK_EQUAL(box.count(),1);

  BOOST_CHECK_NO_THROW(controller.nextPage());
  BOOST_CHECK_EQUAL(controller.getActPage(), 2);
  BOOST_CHECK_EQUAL(box.count(),1);

  BOOST_CHECK_NO_THROW(controller.nextPage());
  BOOST_CHECK_EQUAL(controller.getActPage(), 3);
  BOOST_CHECK_EQUAL(box.count(),1);
}


BOOST_AUTO_TEST_CASE( saveCorrectActPageAtInvoceNextPageIfModelCntIsEqualModelsAtPage )
{
  QToolBox box;
  const uint32_t MODELS_CNT = 4, MODELS_AT_PAGE = MODELS_CNT;
  ModelController controller(&box, MODELS_AT_PAGE);
  ConfigManager conf;

  conf.setVectSize(12);
  conf.setModelFolder("models");
  controller.loadModels(conf );
  controller.refreshDisplayedModels();

  BOOST_CHECK_EQUAL(controller.getModelsCnt(), MODELS_CNT);
  BOOST_CHECK_EQUAL(controller.getActPage(), 0);
  BOOST_CHECK_EQUAL(box.count(),MODELS_CNT);

  const uint32_t MAX_ACT_PAGE = 1;
  BOOST_CHECK_NO_THROW(controller.nextPage());
  BOOST_CHECK_EQUAL(controller.getActPage(), MAX_ACT_PAGE);
  BOOST_CHECK_EQUAL(box.count(),0);


  BOOST_CHECK_NO_THROW(controller.nextPage());
  BOOST_CHECK_EQUAL(controller.getActPage(), MAX_ACT_PAGE); //powinna pozostać ta sama
  BOOST_CHECK_EQUAL(box.count(),0);


}

BOOST_AUTO_TEST_CASE( decrementActPageAtInvocePrevPageIfModelCntIsMoreThanModelsAtPage )
{
  QToolBox box;
  const uint32_t MODELS_CNT = 4, MODELS_AT_PAGE =1;
  ModelController controller(&box, MODELS_AT_PAGE);
  ConfigManager conf;

  conf.setVectSize(12);
  conf.setModelFolder("models");
  controller.loadModels(conf );
  controller.refreshDisplayedModels();

  BOOST_CHECK_EQUAL(controller.getModelsCnt(), MODELS_CNT);
  BOOST_CHECK_EQUAL(controller.getActPage(), 0);
  BOOST_CHECK_EQUAL(box.count(),1);

  BOOST_CHECK_NO_THROW(controller.nextPage());
  BOOST_CHECK_EQUAL(controller.getActPage(), 1);
  BOOST_CHECK_EQUAL(box.count(),1);

  BOOST_CHECK_NO_THROW(controller.nextPage());
  BOOST_CHECK_EQUAL(controller.getActPage(), 2);
  BOOST_CHECK_EQUAL(box.count(),1);

  BOOST_CHECK_NO_THROW(controller.prevPage());
  BOOST_CHECK_EQUAL(controller.getActPage(), 1);
  BOOST_CHECK_EQUAL(box.count(),1);

  BOOST_CHECK_NO_THROW(controller.prevPage());
  BOOST_CHECK_EQUAL(controller.getActPage(), 0);
  BOOST_CHECK_EQUAL(box.count(),1);



}


BOOST_AUTO_TEST_CASE( saveCorrectActPageAtInvokePrevPageIfModelCntIsEqualModelsAtPage )
{
  QToolBox box;
  const uint32_t MODELS_CNT = 4, MODELS_AT_PAGE = MODELS_CNT;
  ModelController controller(&box, MODELS_AT_PAGE);
  ConfigManager conf;

  conf.setVectSize(12);
  conf.setModelFolder("models");
  controller.loadModels(conf );
  controller.refreshDisplayedModels();

  BOOST_CHECK_EQUAL(controller.getModelsCnt(), MODELS_CNT);
  BOOST_CHECK_EQUAL(controller.getActPage(), 0);
  BOOST_CHECK_EQUAL(box.count(),MODELS_AT_PAGE);

  BOOST_CHECK_NO_THROW(controller.prevPage());
  BOOST_CHECK_EQUAL(controller.getActPage(), 0);
  BOOST_CHECK_EQUAL(box.count(),MODELS_AT_PAGE);

}

BOOST_AUTO_TEST_CASE( printCorrectWidgetsCountAtToolBoxAfterRefresh )
{
  QToolBox box;
  const uint32_t MODELS_CNT = 4, MODELS_AT_PAGE = MODELS_CNT+1;
  ModelController controller(&box, MODELS_AT_PAGE);
  ConfigManager conf;

  conf.setVectSize(12);
  conf.setModelFolder("models");
  controller.loadModels(conf );
  controller.refreshDisplayedModels();
  BOOST_CHECK_EQUAL(controller.getModelsCnt(), MODELS_CNT);
  BOOST_CHECK_EQUAL(controller.getActPage(), 0);
  BOOST_CHECK_EQUAL(box.count(),MODELS_CNT);


}




BOOST_AUTO_TEST_SUITE_END()
