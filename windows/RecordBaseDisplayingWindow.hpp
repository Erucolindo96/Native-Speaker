#ifndef RECORDBASEDISPLAYINGWINDOW_HPP
#define RECORDBASEDISPLAYINGWINDOW_HPP

#include "ui_RecordBaseDisplayingWindow.h"
#include"record-base/RecBaseManager.hpp"
class RecordBaseDisplayingWindow : public QDialog
{
  Q_OBJECT

public:
  explicit RecordBaseDisplayingWindow(RecBaseManager &manager,
                                      QWidget *parent = 0);

  void setModelsList(const std::vector<std::string> &models);


private slots:
  void on_pushButton_released();

  void on_comboBox_model_currentIndexChanged(const QString &arg1);

  void on_pushButton_remove_from_sample_base_released();

private:
  std::vector<std::string> models_list_;
  RecBaseManager &sample_base_man_;
  Ui::RecordBaseDisplayingWindow ui;
};

#endif // RECORDBASEDISPLAYINGWINDOW_HPP
