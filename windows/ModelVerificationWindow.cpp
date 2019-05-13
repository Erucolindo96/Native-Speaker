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
 // QComboBox* models_box = ui.comboBox_model;
  for(uint32_t i=0; i<models_man_ref_.getModelsCnt(); ++i)
  {
    QString model_name = models_man_ref_[i]->getName().c_str();
    QObject *model_ptr = models_man_ref_[i].get();
    box->insertItem(i,model_name,QVariant::fromValue<QObject*>(model_ptr) );
  }
}

std::shared_ptr<GmmModel> ModelVerificationWindow::getModel(QComboBox *box)
{
  return std::shared_ptr<GmmModel>(dynamic_cast<GmmModel*>(
        box->itemData(box->currentIndex()).value<QObject*>()
        ));
}

std::map<QString, bool> ModelVerificationWindow::testRecords
(const std::vector<Record> &recs )
{
  std::map<QString, bool> ret;
  std::vector<std::vector<alize::Feature>> records_mfcc = convertRecords(recs);
  Verificator v;
  v.setThreshold(ui.doubleSpinBox_threshold->value());

  std::shared_ptr<GmmModel> model = getModel(ui.comboBox_model),
      ubm = getModel(ui.comboBox_ubm);

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
}
void ModelVerificationWindow::verifyRecords()
{
  auto recs = from_fsys_controller_.getActualRecords();
  if(!recs.empty())
  {
    auto results = testRecords(recs);
    from_fsys_controller_.setResults(results);
  }
}

void ModelVerificationWindow::on_pushButton_verify_released()
{
  verifyRecords();
}

void ModelVerificationWindow::on_pushButton_cancell_released()
{
  QDialog::close();
}
