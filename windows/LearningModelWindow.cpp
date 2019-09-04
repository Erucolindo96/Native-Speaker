#include "LearningModelWindow.hpp"

LearningModelWindow::LearningModelWindow(ModelManager &models_ref,const ConfigManager &config,
                                         RecBaseManager &r_base_ref, FeatureManager &f_man_ref,
                                         LearningController &learining_c_ref,
                                         QWidget *parent ) :
  QDialog(parent), config_(config), model_man_ref_(models_ref), r_base_ref_(r_base_ref),
  f_man_ref_(f_man_ref), learning_c_ref_(learining_c_ref)
{
  ui.setupUi(this);

  initModelsInComboBox();
  initAlgosInComboBox();
  setSubcontrollers();
}


void LearningModelWindow::on_pushButton_cancell_released()
{
  QDialog::close();
}

void LearningModelWindow::initModelsInComboBox()
{
  QComboBox* models_box = ui.comboBox_model_2;
  auto models_name_list =model_man_ref_.getModelsNames();
  std::for_each(models_name_list.begin(), models_name_list.end(),
                [models_box](auto name)->
  void
  {
    models_box->addItem(name.c_str());
  });
}

void LearningModelWindow::initAlgosInComboBox()
{
  const uint32_t FIRST_POS = 0;
  auto algos_list = AlgoManager::getAlgosNames();
  ui.comboBox_algo_2->insertItems(FIRST_POS, algos_list);

}

void LearningModelWindow::setSubcontrollers()
{
  from_fsys_controller_.setAddButtonPtr(ui.pushButton_add_fromFilesystem);
  from_fsys_controller_.setRemoveButtonPtr(ui.pushButton_remove_fromFilesystem);
  from_fsys_controller_.setRecordListPtr(ui.listWidget_fromFilesystem);

  from_microphone_controller_.setAddButtonPtr(ui.pushButton_add_fromMicrophone);
  from_microphone_controller_.setRemoveButtonPtr(ui.pushButton_remove_fromMicrophone);
  from_microphone_controller_.setRecordListPtr(ui.listWidget_fromMicrophone);

  from_sample_base_controller_.setAddButtonPtr(ui.pushButton_add_fromSampleBase);
  from_sample_base_controller_.setRemoveButtonPtr(ui.pushButton_remove_fromSampleBase);
  from_sample_base_controller_.setRecordListPtr(ui.listWidget_fromSampleBase);
  from_sample_base_controller_.setDisplayedModelComboBox(ui.comboBox_from_sample_base_which_model);
  from_sample_base_controller_.setFeatureFolderPath(f_man_ref_.getFeatureFolder());
  from_sample_base_controller_.initComboBox(model_man_ref_.getModelsNames());

}



void LearningModelWindow::performLearning()
{
  using namespace utils;
  auto model_ptr = model_man_ref_[
                   ui.comboBox_model_2->currentText().toStdString()];

  auto algo_name = ui.comboBox_algo_2->currentText();
  try
  {
    auto records_filesystem = from_fsys_controller_.getActualRecords(),
        records_sample_base = from_sample_base_controller_.getActualRecords(),
        records_microphone = from_microphone_controller_.getActualRecords();

    auto mfcc_vecs_fs = f_man_ref_.convertRecord(records_filesystem,
                                                 config_.getVectSize()),
        mfcc_vecs_micro = f_man_ref_.convertRecord(records_microphone,
                                                   config_.getVectSize()),
        mfcc_vecs_base = f_man_ref_.convertRecord(records_sample_base,
                                                  config_.getVectSize());

    saveRecordsToRecordBase(model_ptr->getName(), records_filesystem,
                            records_microphone, records_sample_base);

    auto all_mfcc =  mfcc_vecs_fs + mfcc_vecs_micro + mfcc_vecs_base   ;
    auto iterations = ui.spinBox_iter_2->value();

    learning_c_ref_.startLearning(model_ptr, AlgoManager::getAlgoByName(algo_name),
                                  all_mfcc, iterations);

  }
  catch(UnableToConvertToMfcc &e)
  {
    QMessageBox::warning(this, "Cannot convert records",
                         "Records cannot be converted to MFCC. Maybe there are no sfbcep program to run ?", QMessageBox::Ok);
    return;
  }
  catch(FileNotFound &e)
  {
    QMessageBox::warning(this, "File not found",
                         "Records to convert cannot be found.", QMessageBox::Ok);
    return;
  }
}

void LearningModelWindow::saveRecordsToRecordBase(const std::string &model,
                                                  const std::vector<Record> &from_filesystem,
                                                  const std::vector<Record> &from_microphone,
                                                  const std::vector<Record> &from_sample_base
                                                  )
{

  for(auto rec : from_filesystem)
  {
    r_base_ref_.setRecordToBase(rec, model);
  }

  for(auto rec: from_microphone)
  {
    r_base_ref_.setRecordToBase(rec, model);
  }
  for(auto rec: from_sample_base)
  {
    r_base_ref_.setRecordToBase(rec, model);
  }


}



void LearningModelWindow::on_pushButton_start_released()
{
  performLearning();
  close();
}

//void LearningModelWindow::on_pushButton_add_fromMicrophone_released()
//{
//  std::unique_ptr<AudioRecorderWindow> w = make_unique<AudioRecorderWindow>();
//  w->exec();
//  for(auto r: w->getRegisteredRecords())
//  {
//    ui.listWidget_fromMicrophone->addItem(r.getRecordInfo().absoluteFilePath());
//  }

//}
