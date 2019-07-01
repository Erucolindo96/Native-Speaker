#include "windows/ModelVerificationWindow.hpp"


ModelVerificationWindow::ModelVerificationWindow(ModelManager &models_man_ref,
                                                 FeatureManager &f_man,const uint32_t F_SIZE,
                                                 QWidget *parent) :
  QDialog(parent), models_man_ref_(models_man_ref), f_man_(f_man), F_SIZE_(F_SIZE)
{
  ui.setupUi(this);
  initModelsInComboBox(ui.comboBox_model);
  initModelsInComboBox(ui.comboBox_ubm);
  setSubcontrollers();

}

void ModelVerificationWindow::initModelsInComboBox(QComboBox *box)
{
  box->clear();
  auto models_names = models_man_ref_.getModelsNames();
  std::for_each(models_names.begin(), models_names.end(),
                [box](auto name)->
  void
  {
    box->addItem(name.c_str());
  });
}

std::shared_ptr<GmmModel> ModelVerificationWindow::getModel(QComboBox *box)
{
  return models_man_ref_[box->currentText().toStdString()];
}

std::map<QString, bool> ModelVerificationWindow::testRecords
(const std::vector<Record> &recs )
{
  std::map<QString, bool> ret;
  std::shared_ptr<GmmModel> model = getModel(ui.comboBox_model),
      ubm = getModel(ui.comboBox_ubm);
  std::vector<std::vector<alize::Feature>> records_mfcc = convertRecords(recs);
  Verificator v;
  v.setThreshold(ui.doubleSpinBox_threshold->value());


  for(uint32_t i=0; i<recs.size(); ++i)
  {
    Record act_rec = recs[i];
    auto mfcc = records_mfcc[i];
    ret[act_rec.getRecordInfo().absoluteFilePath()] = v.verifyModel(*model,mfcc, *ubm );
  }
  return ret;

}

std::vector<std::vector<alize::Feature>> ModelVerificationWindow::convertRecords
(const std::vector<Record> &recs )
{
  std::vector<std::vector<alize::Feature>> records_mfcc;
  for(auto rec: recs)
  {
    records_mfcc.push_back(f_man_.convertRecord(rec, F_SIZE_));
  }
  return records_mfcc;

}

void ModelVerificationWindow::setSubcontrollers()
{
  from_fsys_controller_.setAddButtonPtr(ui.pushButton_add_rec_filesystem_2);
  from_fsys_controller_.setRemoveButtonPtr(ui.pushButton_remove_filesystem_2);
  from_fsys_controller_.setRecordListPtr(ui.listWidget_records_filesystem_2);
  from_fsys_controller_.setResultListPtr(ui.listWidget_results_filesystem_2);

  from_micro_controller_.setAddButtonPtr(ui.pushButton_add_rec_microphone);
  from_micro_controller_.setRemoveButtonPtr(ui.pushButton_remove_microphone);
  from_micro_controller_.setRecordListPtr(ui.listWidget_records_microphone);
  from_micro_controller_.setResultListPtr(ui.listWidget_results_microphone);

}
void ModelVerificationWindow::verifyRecords()
{
  auto recs_fs = from_fsys_controller_.getActualRecords(),
      recs_micro = from_micro_controller_.getActualRecords();
  if(!recs_fs.empty())
  {
    auto results = testRecords(recs_fs);
    from_fsys_controller_.setResults(results);
  }

  if(!recs_micro.empty())
  {
    auto results = testRecords(recs_micro);
    from_micro_controller_.setResults(results);
  }
}

void ModelVerificationWindow::on_pushButton_verify_released()
{
  from_fsys_controller_.clearResultList();
  from_micro_controller_.clearResultList();
  verifyRecords();
}

void ModelVerificationWindow::on_pushButton_cancell_released()
{
  QDialog::close();
}
