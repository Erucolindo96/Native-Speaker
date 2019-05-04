#include "LearningController.hpp"

using thread_tuple_vec = LearningController::thread_tuple_vec;
using thread_tuple = LearningController::thread_tuple;



void LearningController::displayThreadLoop()
{
  while(1)
  {

    actualizeComboBox();
    actualizeProgressBar();

    this_thread::sleep_for(std::chrono::milliseconds(500));
  }

}

void LearningController::runDisplayThread()
{
  t_ = std::make_unique<std::thread>(&LearningController::displayThreadLoop, std::ref(*this));
}

void LearningController::setComboBoxPtr(QComboBox *ptr)
{
  std::lock_guard<std::mutex> l(m_);
  l_thread_combo_box_ = ptr;
  connectSignalsAndSlots();
}

void LearningController::setProgressBarPtr(QProgressBar *ptr)
{
  std::lock_guard<std::mutex> l(m_);
  l_thread_prog_bar_ = ptr;
}

void LearningController::actualizeComboBox()
{
  std::lock_guard<std::mutex> l(m_);
  l_thread_combo_box_->clear();
  for(auto l_thread: l_thread_list_)
  {
//    QVariant model_ptr = QVariant::fromValue
//                         <std::shared_ptr<GmmModel>>(l_thread.getModelPtr());
        QVariant model_ptr = QVariant::fromValue
                             <int>((int)l_thread.getModelPtr().get());

    l_thread_combo_box_->addItem(l_thread.getModelPtr()->getName().c_str(),
                                 model_ptr);
  }
}

void LearningController::actualizeProgressBar()
{
  auto act_model = std::atomic_load(&act_displayed_learning_);
  std::lock_guard<std::mutex> l(m_);

  auto thread_iter = std::find_if(l_thread_list_.begin(), l_thread_list_.end(),
               [act_model](auto t1)->bool{return t1.getModelPtr() == act_model;}
  );
  if(thread_iter != l_thread_list_.end())//znaleźliśmy wątek uczący który mamy wyswietlic
  {
    l_thread_prog_bar_->setMaximum(thread_iter->getIterCnt());
    l_thread_prog_bar_->setValue(thread_iter->getIter());
  }
  else
  {
    l_thread_prog_bar_->setValue(0);
  }

}

void LearningController::updateDisplayedLearning()
{
  std::lock_guard<std::mutex> l(m_);
  if(l_thread_combo_box_->count() != 0)
  {
    auto combo_box_idx = l_thread_combo_box_->currentIndex();
    QVariant model_ptr = l_thread_combo_box_->itemData(combo_box_idx);
    //std::atomic_store(&act_displayed_learning_, model_ptr.value<std::shared_ptr<GmmModel>>());
    std::atomic_store(&act_displayed_learning_,
                      std::shared_ptr<GmmModel>((GmmModel*)model_ptr.value<int>()));
  }
}

void LearningController::connectSignalsAndSlots()
{
  if(l_thread_combo_box_ != nullptr)
  {
    connect(l_thread_combo_box_, SIGNAL(currentIndexChanged(int)),
            this, SLOT(updateDisplayedLearning()));
  }
}


