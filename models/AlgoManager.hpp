#ifndef ALGOMANAGER_HPP
#define ALGOMANAGER_HPP
#include"learning_algo.hpp"
#include<map>
#include<QStringList>


class AlgoManager
{
public:/*
  explicit AlgoManager();
  AlgoManager(const AlgoManager &other)= default;
  AlgoManager& operator=(const AlgoManager &other)= default;
  AlgoManager(AlgoManager &&other)= default;
  AlgoManager& operator=(AlgoManager &&other)= default;*/

  static std::unique_ptr<LearningAlgo> getAlgoByName(const QString &algo_name);
  static QStringList getAlgosNames();
protected:
  static std::map<QString,AlgoType > algos_names_;



};

//class AlgoMap
//{
//protected:
//  static std::map<AlgoType, std::unique_ptr<LearningAlgo>> algos_map_;

//public:
//  static const std::map<AlgoType, std::unique_ptr<LearningAlgo>>& getAlgoMap();

//};

#endif // ALGOMANAGER_HPP
