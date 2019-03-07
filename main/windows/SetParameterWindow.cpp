#include "SetParameterWindow.hpp"

SetParameterWindow::SetParameterWindow(ConfigManager conf, QWidget *parent) :
  QDialog(parent), conf_(conf)
{
  ui.setupUi(this);
  initComboBox();

  QString first_param = ui.comboBox_param_name->currentText();
  setParamValueAtLineEdit(first_param);
}

std::string SetParameterWindow::getParamName()const
{
  return param_;
}
std::string SetParameterWindow::getParamValue()const
{
  return value_;
}
/*
void SetParameterWindow::setConfig(const ConfigManager &conf)
{
  conf_ = conf;
}

ConfigManager SetParameterWindow::getConfig()const
{
  return conf_;
}
*/

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


void SetParameterWindow::on_comboBox_param_name_currentIndexChanged(const QString &arg1)
{
  setParamValueAtLineEdit(arg1);
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

void SetParameterWindow::setParamValueAtLineEdit(const QString &param_name)
{
  ui.lineEdit_param_value->clear();
  alize::String param_name_alize = param_name.toStdString().c_str();
  if(conf_.existsParam(param_name_alize))
  {
    ui.lineEdit_param_value->insert(conf_.getParam(param_name_alize).c_str());
  }
}

