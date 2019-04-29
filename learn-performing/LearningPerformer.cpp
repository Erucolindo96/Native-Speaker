#include "LearningPerformer.hpp"


LearningPerformer& LearningPerformer::operator=(const LearningPerformer &other)
{
  return *this;
}

LearningPerformer& LearningPerformer::operator=(LearningPerformer &&other)
{
  return *this;
}

void LearningPerformer::startLearning(std::shared_ptr<GmmModel> m,
                                    std::unique_ptr<LearningAlgo> &&algo,
                                    std::vector<alize::Feature> &f_vec,
                                    uint32_t iter_cnt )
{
  removeDoneThreads();
  if(std::find_if(list_.begin(), list_.end(),
                 [m](auto t1)->bool{return t1.getModelPtr() == m;}

               ) != list_.end())
  {//aktualnie pracuje jakiś wątek uczący model m
    throw RerunningLearningThread(__FILE__ + std::string(", line: ") + std::to_string(__LINE__)
                                  + std::string(" - try to rerunning learning thread, whick is running now"));
  }
  list_.push_back(LearningThread(m));
  list_.back().run(std::move(algo), f_vec, iter_cnt);//wątek uruchomiony
}


void LearningPerformer::removeDoneThreads()
{
  auto iter = list_.begin();

  while(iter != list_.end())
  {
    if(iter->isDone())
    {
      iter = list_.erase(iter);
    }
    else // gdybysmy usuwali to przejscie na kolejny element by już nastąpiło
    {
      ++iter;
    }
  }
}
