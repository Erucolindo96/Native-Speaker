#ifndef LEARNINGTHREADMOCK_HPP
#define LEARNINGTHREADMOCK_HPP

#include"learn-performing/LearningThread.hpp"

class LearningThreadMock : public LearningThread
{
  Q_OBJECT
public:
  LearningThreadMock(std::unique_ptr<GmmModel> &m_ref):LearningThread(m_ref)
  {}

  LearningThreadMock(const LearningThreadMock &other):
    LearningThread(other.model_ref_)
  {}


  LearningThreadMock(LearningThreadMock &&other):LearningThread(other)
  {

  }

  void join()
  {
    t_->join();
  }

  ~LearningThreadMock()override = default;

};
#endif // LEARNINGTHREADMOCK_HPP
