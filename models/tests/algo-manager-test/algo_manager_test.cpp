#include "algo_manager_test.hpp"



BOOST_AUTO_TEST_SUITE( AlgoManagerTest )


BOOST_AUTO_TEST_CASE(getCorrectListOfAlgos )
{
  const uint32_t ALGOS_CNT = 2;//2, bo sa 2 nazwy dla jednego algorytmu
  auto algo_list = AlgoManager::getAlgosNames();
  BOOST_REQUIRE_EQUAL(algo_list.size(),ALGOS_CNT );
  BOOST_CHECK_EQUAL(algo_list[0].toStdString(),"Expectation-Maximization Algo" );
  BOOST_CHECK_EQUAL(algo_list[1].toStdString(),"em-algo" );

}

BOOST_AUTO_TEST_CASE(getCorrectAlgoPtrIfRequireIsEMAlgo )
{
  const QString name1 = "Expectation-Maximization Algo",
      name2 = "em-algo";
  auto algo_ptr1 = AlgoManager::getAlgoByName(name1);
  BOOST_REQUIRE(algo_ptr1 != nullptr );
  BOOST_CHECK(dynamic_cast<ExpectationMaximalizationAlgo*>(algo_ptr1.get())
              !=nullptr );
  auto algo_ptr2 = AlgoManager::getAlgoByName(name2);
  BOOST_REQUIRE(algo_ptr2 != nullptr );
  BOOST_CHECK(dynamic_cast<ExpectationMaximalizationAlgo*>(algo_ptr2.get())
              !=nullptr );
}


BOOST_AUTO_TEST_SUITE_END()

