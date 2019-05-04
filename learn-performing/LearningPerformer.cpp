#include "LearningPerformer.hpp"

LearningPerformer::LearningPerformer(const LearningPerformer &other):QObject(),
l_thread_list_(other.l_thread_list_), m_()
{

}

LearningPerformer& LearningPerformer::operator=(const LearningPerformer &other)
{
  return *this;
}

LearningPerformer::LearningPerformer(LearningPerformer &&other):
  l_thread_list_(std::move(other.l_thread_list_)), m_()
{

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
  removeDoneThreads();//juz synchronizowane
  std::lock_guard<std::mutex> l(m_);
  if(std::find_if(l_thread_list_.begin(), l_thread_list_.end(),
                 [m](auto t1)->bool{return t1.getModelPtr() == m;}

               ) != l_thread_list_.end())
  {//aktualnie pracuje jakiś wątek uczący model m
    throw RerunningLearningThread(__FILE__ + std::string(", line: ") + std::to_string(__LINE__)
                                  + std::string(" - try to rerunning learning thread, whick is running now"));
  }
  l_thread_list_.push_back(LearningThread(m));
  l_thread_list_.back().run(std::move(algo), f_vec, iter_cnt);//wątek uruchomiony
}


void LearningPerformer::removeDoneThreads()
{
  std::lock_guard<std::mutex> l(m_);
  auto iter = l_thread_list_.begin();

  while(iter != l_thread_list_.end())
  {
    if(iter->isDone())
    {
      iter = l_thread_list_.erase(iter);
    }
    else // gdybysmy usuwali to przejscie na kolejny element by już nastąpiło
    {
      ++iter;
    }
  }
}
