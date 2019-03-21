#ifndef LEARNINGMODELWINDOW_HPP
#define LEARNINGMODELWINDOW_HPP

#include "ui_LearningModelWindow.h"
#include"configuration/ConfigManager.hpp"
#include"models/ModelManager.hpp"
#include"models/AlgoManager.hpp"
#include"windows/subcontrollers/RecordsFromFilesystemController.hpp"
class LearningModelWindow : public QDialog
{
  Q_OBJECT

public:
  explicit LearningModelWindow(ModelManager &models_ref,const ConfigManager &config,
                               QWidget *parent = 0 );
  void setConfig(ConfigManager conf);
  ConfigManager getConfig()const;

private slots:

  void on_pushButton_cancell_released();

private:
  Ui::LearningModelWindow ui;
  ConfigManager config_;
  ModelManager &model_man_ref_;

  RecordsFromFilesystemController from_fsys_controller_;

  void initModelsInComboBox();
  void initAlgosInComboBox();
  void setSubcontrollers();

};

#endif // LEARNINGMODELWINDOW_HPP
