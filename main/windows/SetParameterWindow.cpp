#include "SetParameterWindow.hpp"

SetParameterWindow::SetParameterWindow(QWidget *parent) :
  QDialog(parent)
{
  ui.setupUi(this);
  initComboBox();
}

std::string SetParameterWindow::getParamName()const
{
  return param_;
}
std::string SetParameterWindow::getParamValue()const
{
  return value_;
}

void SetParameterWindow::on_save_button_released()
{
  readParamNameAndValue();
  try
  {
    ConfigValidator v;
    v.isParamValid(param_, value_);
  }catch(ParamNotValid e)
  {
    QMessageBox::warning(const_cast<SetParameterWindow*>(this),
                         "Param is invalid",
                         e.what() ,QMessageBox::Ok);
    return;
  }
  emit accepted();
  close();
}

void SetParameterWindow::on_cancel_button_released()
{
  close();
}

void SetParameterWindow::on_toolButton_released()
{
  const QString DEF_PATH = "/home";
  QString path = QFileDialog::getExistingDirectory(this, "", DEF_PATH, QFileDialog::ShowDirsOnly);
  ui.lineEdit_param_value->insert(path);
}

void SetParameterWindow::initComboBox()const
{
  for(auto pair_ptr = ConfigManager::VALID_PARAMS_.cbegin();
      pair_ptr != ConfigManager::VALID_PARAMS_.cend(); ++pair_ptr)
  {
    ui.comboBox_param_name->addItem(pair_ptr->second.c_str());
  }
}

void SetParameterWindow::readParamNameAndValue()
{
  param_ = ui.comboBox_param_name->currentText().toStdString();
  value_ = ui.lineEdit_param_value->text().toStdString();

}


