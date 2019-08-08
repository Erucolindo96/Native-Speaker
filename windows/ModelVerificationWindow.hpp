#ifndef MODELVERIFICATIONWINDOW_HPP
#define MODELVERIFICATIONWINDOW_HPP

#include "ui_ModelVerificationWindow.h"
#include"windows/subcontrollers/RecordsFromFilesystemVerificationController.hpp"
#include"windows/subcontrollers/RecordsFromMicrophoneVerificationController.hpp"
#include"models/ModelManager.hpp"
#include"features/FeatureManager.hpp"
#include"models/verificator.hpp"
#include"features/FeatureReaderSilenceCutter.hpp"



class ModelVerificationWindow : public QDialog
{
  Q_OBJECT


public:
  explicit ModelVerificationWindow( ModelManager &models_man_ref,FeatureManager &f_man,
                                    const uint32_t F_SIZE,
                                    QWidget *parent = 0);

protected:
  Ui::ModelVerificationWindow ui;
  RecordsFromFilesystemVerificationController from_fsys_controller_;
  RecordsFromMicrophoneVerificationController from_micro_controller_;
  ModelManager &models_man_ref_;
  FeatureManager &f_man_;
  const uint32_t F_SIZE_;

  void initModelsInComboBox(QComboBox *box);
  std::shared_ptr<GmmModel> getModel(QComboBox *box);

  std::map<QString, std::pair<bool, double>> testRecords(const std::vector<Record> &recs );
  std::vector<std::vector<alize::Feature>> convertRecords(const std::vector<Record> &recs );

  void setSubcontrollers();
  void verifyRecords();


private slots:
  void on_pushButton_verify_released();
  void on_pushButton_cancell_released();
};

#endif // MODELVERIFICATIONWINDOW_HPP
