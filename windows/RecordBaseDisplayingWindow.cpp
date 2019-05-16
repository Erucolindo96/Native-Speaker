﻿#include "RecordBaseDisplayingWindow.hpp"

RecordBaseDisplayingWindow::RecordBaseDisplayingWindow(RecBaseManager &manager,
                                                       QWidget *parent) :
  QDialog(parent), sample_base_man_(manager)
{
  ui.setupUi(this);
}

void RecordBaseDisplayingWindow::setModelsList(const std::vector<std::string> &models)
{
  ui.comboBox_model->clear();
  models_list_ = models;
  std::for_each(models_list_.begin(), models_list_.end(),
                [this](auto name)->
  void
  {
    ui.comboBox_model->addItem(name.c_str());
  });
}


void RecordBaseDisplayingWindow::on_pushButton_released()
{
    QDialog::close();
}

void RecordBaseDisplayingWindow::on_comboBox_model_currentIndexChanged(const QString &m_displayed)
{
  ui.listWidget_fromFilesystem->clear();
  auto model_recs = sample_base_man_.getRecordsOfModel(m_displayed.toStdString());

  std::for_each(model_recs.begin(), model_recs.end(),
                [this](auto rec)->
  void
  {
    ui.listWidget_fromFilesystem->addItem(rec.getRecordInfo().
                                          absoluteFilePath());
  });
}

void RecordBaseDisplayingWindow::on_pushButton_remove_from_sample_base_released()
{
}
