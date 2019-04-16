#include "LearningThread.hpp"

LearningThread::LearningThread(std::unique_ptr<GmmModel> &m_ref):QObject(),
  model_ref_(m_ref), act_iter_(0), is_done_(false)
{}

LearningThread::LearningThread(const LearningThread &other):
  LearningThread(other.model_ref_)
{}


LearningThread::LearningThread(LearningThread &&other):QObject(),
  t_(std::move(other.t_)),model_ref_(other.model_ref_),
  act_iter_(other.act_iter_.load())
{
  is_done_.store(other.is_done_.load());
}


void LearningThread::learningOperation(LearningThread &t,std::unique_ptr<LearningAlgo> &&algo,
                std::vector<alize::Feature> f_vec, uint32_t iters)
{
  while(t.getIter()< iters)
  {
    algo->learnModel(*t.getModelRef(), f_vec, 1);
    t.incrementIter();
  }
  t.is_done_ = true;
}

void LearningThread::run(std::unique_ptr<LearningAlgo> &&algo,
         std::vector<alize::Feature> f_vec, uint32_t iters)
{
  if(f_vec.empty())
  {
    throw LearningModelWithoutFeatures(__FILE__ + std::string(", line: ") + std::to_string(__LINE__)
                                                + std::string(" - try to learn model with empty feature vector"));
  }
  if(t_ != nullptr)
  {
    throw RerunningLearningThread(__FILE__ + std::string(", line: ") + std::to_string(__LINE__)
                                  + std::string(" - try to rerunning learning thread, whick was run in past"));
  }

  t_ = make_unique<std::thread>(&LearningThread::learningOperation, std::ref(*this),
                                std::move(algo), f_vec, iters );
}

std::unique_ptr<GmmModel>& LearningThread::getModelRef()const
{
  std::lock_guard<std::mutex> l(mutex_);
  return model_ref_;
}

void LearningThread::incrementIter()
{
  std::lock_guard<std::mutex> l(mutex_);
  ++act_iter_;
}

bool LearningThread::isDone()const
{
  std::lock_guard<std::mutex> l(mutex_);
  if(t_ == nullptr)
  {
    return false;
  }
  //jesli tu jestesmy to znaczy, ze wątek został uruchomiony
  return is_done_;
}

uint32_t LearningThread::getIter()const
{
  std::lock_guard<std::mutex> l(mutex_);
  return act_iter_;
}

