#ifndef RECORDBASEDISPLAYINGWINDOW_HPP
#define RECORDBASEDISPLAYINGWINDOW_HPP

#include "ui_RecordBaseDisplayingWindow.h"
#include"record-base/RecBaseManager.hpp"
#include"subcontrollers/RecordsInSampleBaseController.hpp"

class RecordBaseDisplayingWindow : public QDialog
{
  Q_OBJECT

public:
  explicit RecordBaseDisplayingWindow(RecBaseManager &manager,
                                      QWidget *parent = 0);

  void setModelsList(const std::vector<std::string> &models);

  ~RecordBaseDisplayingWindow()override = default;
private slots:
  void on_pushButton_released();

//  void on_comboBox_model_currentIndexChanged(const QString &arg1);

//  void on_pushButton_remove_from_sample_base_released();

private:
  RecordsInSampleBaseController sample_base_controller_;
  RecBaseManager &sample_base_man_;
  Ui::RecordBaseDisplayingWindow ui;

  void initControllers();

};

#endif // RECORDBASEDISPLAYINGWINDOW_HPP
