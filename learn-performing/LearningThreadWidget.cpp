#include "LearningThreadWidget.hpp"

LearningThreadWidget::LearningThreadWidget(QWidget *parent) :
  QFrame(parent)
{
  ui.setupUi(this);
}


void LearningThreadWidget::setIterCnt(uint32_t iter_cnt)
{
  ui.progressBar_learningProgress->setMaximum(iter_cnt);
}

uint32_t LearningThreadWidget::getIterCnt()const
{
  return ui.progressBar_learningProgress->maximum();
}

void LearningThreadWidget::setModelName(const QString &str)
{
  ui.label_modelName->setText(str);
}

QString LearningThreadWidget::getModelName()const
{
  return ui.label_modelName->text();
}

void LearningThreadWidget::setActualIter(uint32_t act_iter)
{
  ui.progressBar_learningProgress->setValue(act_iter);
}

uint32_t LearningThreadWidget::getActualIter()const
{
  return ui.progressBar_learningProgress->value();
}

void LearningThreadWidget::setModelPtr(std::shared_ptr<GmmModel> model)
{
  m_ = model;
}

std::shared_ptr<const GmmModel> LearningThreadWidget::getModelPtr()const
{
  return m_;
}
