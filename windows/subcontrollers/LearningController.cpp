#include "LearningController.hpp"


void LearningController::startLearning(std::shared_ptr<GmmModel> m,
                                      std::unique_ptr<LearningAlgo> &&algo,
                                      std::vector<alize::Feature> &f_vec,
                                      uint32_t iter_cnt )
{
  {;
    removeDoneThreads();
    checkForRunningThread(m);
    l_thread_list_.push_back(LearningThread(m));

  connect(&(l_thread_list_.back()), SIGNAL(iterationComplete(const QString, const qint32,const qint32)),
          this,SLOT(actualizeProgressBarByLearningThread(const QString,const qint32,const qint32)),
          Qt::QueuedConnection );
  connect(&(l_thread_list_.back()), SIGNAL(learningComplete(QObject*)),
          this,SLOT(saveModelLearnedFromLearningThread(QObject*)),
          Qt::QueuedConnection );

  }
  l_thread_combo_box_->addItem(m->getName().c_str());
  l_thread_list_.back().run(std::move(algo), f_vec, iter_cnt);//wątek uruchomiony
  actualizeProgressBarByMainThread();//aby zainicjalizować progress bar
}



void LearningController::setComboBoxPtr(QComboBox *ptr)
{
  l_thread_combo_box_ = ptr;
  connectSignalsAndSlots();
}

void LearningController::setProgressBarPtr(QProgressBar *ptr)
{
  l_thread_prog_bar_ = ptr;
}

void LearningController::setModelManagerPtr(ModelManager *ptr)
{
  model_man_ = ptr;
}

void LearningController::setConfigManagerPtr(ConfigManager *ptr)
{
  conf_man_ = ptr;
}


void LearningController::connectSignalsAndSlots()
{
  if(l_thread_combo_box_ != nullptr)
  {
    connect(l_thread_combo_box_, SIGNAL(currentIndexChanged(QString)),
            this, SLOT(actualizeProgressBarByMainThread()));
  }
}

void LearningController::removeDoneThreads()
{
  for(LearningThread &t: l_thread_list_)
  {
    if(t.isDone())
    {
      findAndRemoveFromComboBox(t.getModelPtr()->getName().c_str());
    }
  }
  LearningPerformer::removeDoneThreads();
}

void LearningController::findAndRemoveFromComboBox(const QString &model_name)
{
  for(int32_t i=0; i< l_thread_combo_box_->count(); ++i)
  {
    if(l_thread_combo_box_->itemText(i) == model_name)
    {
      l_thread_combo_box_->removeItem(i);
    }
  }
}

void LearningController::actualizeProgressBarByLearningThread(const QString model_name,
                                                              const qint32 act_iter,
                                                              const qint32 iter_cnt)
{
  if(model_name == l_thread_combo_box_->currentText())
  {
    l_thread_prog_bar_->setMaximum(iter_cnt);
    l_thread_prog_bar_->setValue(act_iter);
  }
}


void LearningController::actualizeProgressBarByMainThread()//const QString &displayed_model_name)
{

  auto th_iter = std::find_if(l_thread_list_.begin(), l_thread_list_.end(),
               [this](auto t)->bool
  {
    return t.getModelPtr()->getName().c_str() == l_thread_combo_box_->currentText();
  });

  if(th_iter == l_thread_list_.end())
  {
    throw std::runtime_error(__FILE__ + std::string(", line: ") + std::to_string(__LINE__)
                             + std::string(" - no learning thread, which learn model in combo box named "
                                           + l_thread_combo_box_->currentText().toStdString()));
  }
  l_thread_prog_bar_->setMaximum(th_iter->getIterCnt());
  l_thread_prog_bar_->setValue(th_iter->getIter());
}

void LearningController::saveModelLearnedFromLearningThread(QObject *m)
{
  model_man_->addModel(*conf_man_,
                       std::shared_ptr<GmmModel>(dynamic_cast<GmmModel*>(m)));
}
