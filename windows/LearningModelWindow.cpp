#include "LearningModelWindow.hpp"

LearningModelWindow::LearningModelWindow(ModelManager &models_ref,const ConfigManager &config,
                                         QWidget *parent ) :
  QDialog(parent), model_man_ref_(models_ref), config_(config)
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
  for(uint32_t i=0; i<model_man_ref_.getModelsCnt(); ++i)
  {
    QString model_name = model_man_ref_[i]->getName().c_str();
    models_box->insertItem(i,model_name);
  }
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

