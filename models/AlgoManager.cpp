#include "AlgoManager.hpp"

std::map<QString,AlgoType > AlgoManager::algos_names_=
{
  {"Expectation-Maximization Algo",EM_ALGO},
  {"em-algo", EM_ALGO}
};

std::unique_ptr<LearningAlgo> AlgoManager::getAlgoByName(const QString &algo_name)
{
  try
  {
    if(AlgoManager::algos_names_.at(algo_name) == EM_ALGO)
    {
      return std::make_unique<ExpectationMaximalizationAlgo>();
    }
  }
  catch(std::out_of_range e)
  {}
  return nullptr;
}

QStringList AlgoManager::getAlgosNames()
{
  QStringList algos_list;
  for(auto elem = algos_names_.cbegin(); elem != algos_names_.cend(); ++elem)
  {
    algos_list.append(elem->first);
  }
  return algos_list;
}


//AlgoManager::AlgoManager()
//{

//}

//std::map<AlgoType, std::unique_ptr<LearningAlgo>> AlgoMap::algos_map_ =
//{
//  {EM_ALGO, std::make_unique<ExpectationMaximalizationAlgo>()}
//};
//const std::map<AlgoType, std::unique_ptr<LearningAlgo>>& AlgoMap::getAlgoMap()
//{
//  return algos_map_;
//}
