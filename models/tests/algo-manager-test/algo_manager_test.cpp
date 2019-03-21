#include "algo_manager_test.hpp"



BOOST_AUTO_TEST_SUITE( AlgoManagerTest )


BOOST_AUTO_TEST_CASE(getCorrectListOfAlgos )
{
  const uint32_t ALGOS_CNT = 1;
  auto algo_list = AlgoManager::getAlgosNames();
  BOOST_REQUIRE_EQUAL(algo_list.size(),ALGOS_CNT );
  BOOST_CHECK_EQUAL(algo_list[0].toStdString(),"Expectation-Maximization Algo" );
}

BOOST_AUTO_TEST_CASE(getCorrectAlgoPtrIfRequireIsEMAlgo )
{
  const QString name = "Expectation-Maximization Algo";
  auto algo_ptr = AlgoManager::getAlgoByName(name);
  BOOST_REQUIRE(algo_ptr != nullptr );
  BOOST_CHECK(dynamic_cast<ExpectationMaximalizationAlgo*>(algo_ptr.get())
              !=nullptr );
}


BOOST_AUTO_TEST_SUITE_END()

