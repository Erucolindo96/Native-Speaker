#include "LearningModelWindow.hpp"

LearningModelWindow::LearningModelWindow(ModelManager &models_ref,const ConfigManager &config,
                                         RecBaseManager &r_base_ref, FeatureManager &f_man_ref,
                                         LearningPerformer &learining_p_ref,
                                         QWidget *parent ) :
  QDialog(parent), config_(config), model_man_ref_(models_ref), r_base_ref_(r_base_ref),
  f_man_ref_(f_man_ref), learning_p_ref_(learining_p_ref)
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
}



void LearningModelWindow::performLearning()
{
  auto model_ptr = model_man_ref_[
                   ui.comboBox_model_2->currentText().toStdString()];

  auto algo_name = ui.comboBox_algo_2->currentText();
  auto records_filesystem = from_fsys_controller_.getActualRecords();
  auto mfcc_vecs = f_man_ref_.convertRecord(records_filesystem, config_.getVectSize());
  auto iterations = ui.spinBox_iter_2->value();
  cout<<"Mfcc cnt: "<<mfcc_vecs.size()<<endl;
  cout<<"Mfcc size: "<<mfcc_vecs[0].getVectSize();
  cout<<"Model ptr: "<<model_ptr.get()<<endl;
  learning_p_ref_.startLearning(model_ptr, AlgoManager::getAlgoByName(algo_name),
                                mfcc_vecs, iterations);
  cout<<"Learning of model "<<model_ptr->getName()<<"runned! "<<endl;
}

void LearningModelWindow::on_pushButton_start_released()
{
  performLearning();
  close();
}
