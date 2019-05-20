#include "LearningThread.hpp"

LearningThread::LearningThread(std::shared_ptr<GmmModel> m_ref):QObject(),
  model_ref_(m_ref), act_iter_(0),iter_cnt_(0), is_done_(false)
{}

LearningThread::LearningThread(const LearningThread &other):
  LearningThread(other.model_ref_)
{}

LearningThread& LearningThread::operator=(LearningThread &&other)
{
  if(&other == this)
    return *this;

  act_iter_.store(other.act_iter_.load());
  iter_cnt_.store(other.iter_cnt_.load());
  is_done_.store(other.is_done_.load());

  std::lock_guard<std::mutex> l(mutex_);
  t_ = std::move(other.t_);
  model_ref_ = other.model_ref_;

  return *this;
}


LearningThread::LearningThread(LearningThread &&other):QObject(),
  t_(std::move(other.t_)),model_ref_(other.model_ref_),
  act_iter_(other.act_iter_.load()), iter_cnt_(other.iter_cnt_.load()),
  is_done_(other.is_done_.load())
{}


void LearningThread::learningOperation(LearningThread &t,std::unique_ptr<LearningAlgo> &&algo,
                std::vector<alize::Feature> f_vec, uint32_t iters)
{
  t.setIterCnt(iters);
  while(t.getIter()< t.getIterCnt())
  {
    algo->learnModel(*t.getModelPtr(), f_vec, 1);
    t.incrementIter();
    emit t.iterationComplete(t.getModelPtr()->getName().c_str(),
                             t.getIter(), t.getIterCnt());
  }
  t.setDone();
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
  t_->detach();
}

std::shared_ptr<GmmModel> LearningThread::getModelPtr()const
{
  std::lock_guard<std::mutex> l(mutex_);
  return model_ref_;
}

void LearningThread::incrementIter()
{
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

void LearningThread::setIterCnt(uint32_t iter_cnt)
{
  iter_cnt_.store(iter_cnt);
}

uint32_t LearningThread::getIterCnt()const
{
  return iter_cnt_.load();
}

void LearningThread::setDone()
{
  std::lock_guard<std::mutex> l(mutex_);
  is_done_ = true;
}

