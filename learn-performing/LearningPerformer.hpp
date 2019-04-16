#ifndef LEARNINGPERFORMER_HPP
#define LEARNINGPERFORMER_HPP
#include<QObject>
#include"models/gmmmodel.hpp"
#include"models/learning_algo.hpp"
#include<thread>
#include<mutex>
#include<memory>
#include"learn-performing/LearningThread.hpp"
class LearningPerformer:public QObject
{
  Q_OBJECT
public:
  LearningPerformer() = default;
  LearningPerformer(const LearningPerformer &other);
  LearningPerformer& operator=(const LearningPerformer &other);

  LearningPerformer(LearningPerformer &&other);
  LearningPerformer& operator=(LearningPerformer &&other);

  const LearningThread& startLearning(std::unique_ptr<GmmModel> &m,
                                      std::unique_ptr<LearningAlgo> &&algo,
                                      std::vector<alize::Feature> &f_vec,
                                      uint32_t iter_cnt );


protected:
  std::vector<LearningThread> vec_;




};

#endif // LEARNINGPERFORMER_HPP
