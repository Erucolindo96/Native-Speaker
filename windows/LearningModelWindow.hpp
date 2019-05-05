#ifndef LEARNINGMODELWINDOW_HPP
#define LEARNINGMODELWINDOW_HPP

#include "ui_LearningModelWindow.h"
#include"configuration/ConfigManager.hpp"
#include"models/ModelManager.hpp"
#include"models/AlgoManager.hpp"
#include"windows/subcontrollers/RecordsFromFilesystemController.hpp"
#include"features/FeatureManager.hpp"
#include"learn-performing/LearningPerformer.hpp"
#include"record-base/RecBaseManager.hpp"
class LearningModelWindow : public QDialog
{
  Q_OBJECT

public:
  explicit LearningModelWindow(ModelManager &models_ref,const ConfigManager &config,
                               RecBaseManager &r_base_ref, FeatureManager &f_man_ref,
                               LearningPerformer &learining_p_ref,
                               QWidget *parent = 0 );
  void setConfig(ConfigManager conf);
  ConfigManager getConfig()const;
  ~LearningModelWindow() override = default;

private slots:

  void on_pushButton_cancell_released();

  void on_pushButton_start_released();

private:
  Ui::LearningModelWindow ui;
  ConfigManager config_;
  ModelManager &model_man_ref_;
  RecBaseManager &r_base_ref_;
  FeatureManager &f_man_ref_;
  LearningPerformer &learning_p_ref_;
  RecordsFromFilesystemController from_fsys_controller_;

  void initModelsInComboBox();
  void initAlgosInComboBox();
  void setSubcontrollers();

  void performLearning();


};

#endif // LEARNINGMODELWINDOW_HPP
