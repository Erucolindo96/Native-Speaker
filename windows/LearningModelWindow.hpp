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
#include"windows/subcontrollers/RecordsFromSampleBaseController.hpp"
#include"windows/subcontrollers/LearningController.hpp"
#include"windows/AudioRecorderWindow.hpp"
class LearningModelWindow : public QDialog
{
  Q_OBJECT

public:
  explicit LearningModelWindow(ModelManager &models_ref,const ConfigManager &config,
                               RecBaseManager &r_base_ref, FeatureManager &f_man_ref,
                               LearningController &learining_c_ref,
                               QWidget *parent = 0 );
  void setConfig(ConfigManager conf);
  ConfigManager getConfig()const;
  ~LearningModelWindow() override = default;

private slots:

  void on_pushButton_cancell_released();

  void on_pushButton_start_released();

  void on_pushButton_add_fromMicrophone_released();

private:
  Ui::LearningModelWindow ui;
  ConfigManager config_;
  ModelManager &model_man_ref_;
  RecBaseManager &r_base_ref_;
  FeatureManager &f_man_ref_;
  LearningController &learning_c_ref_;
  RecordsFromFilesystemController from_fsys_controller_;
  RecordsFromSampleBaseController from_sample_base_controller_;

  void initModelsInComboBox();
  void initAlgosInComboBox();
  void setSubcontrollers();

  void performLearning();
  void saveRecordsToRecordBase(const std::string &model,
                               const std::vector<Record> &from_filesystem,
                               const std::vector<Record> &from_microphone,
                               const std::vector<Record> &from_sample_base);



};

#endif // LEARNINGMODELWINDOW_HPP
