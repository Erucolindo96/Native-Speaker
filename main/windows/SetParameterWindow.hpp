#ifndef SETPARAMETERWINDOW_HPP
#define SETPARAMETERWINDOW_HPP

#include "ui_SetParameterWindow.h"
#include <alize.h>
#include "configuration/ConfigValidator.hpp"
#include"QMessageBox"
#include"QFileDialog"

class SetParameterWindow : public QDialog
{
  Q_OBJECT

public:

  explicit SetParameterWindow(ConfigManager conf, QWidget *parent = 0);
  std::string getParamName()const;
  std::string getParamValue()const;
//  void setConfig(const ConfigManager &conf);
//  ConfigManager getConfig()const;

private slots:
  void on_save_button_released();

  void on_cancel_button_released();

  void on_toolButton_released();

  void on_comboBox_param_name_currentIndexChanged(const QString &arg1);

signals:
  void paramReadyToSave();

private:
  Ui::SetParameterWindow ui;
  std::string param_, value_;
  ConfigManager conf_;

  void initComboBox()const;
  void readParamNameAndValue();
  void setParamValueAtLineEdit(const QString &param_name);

};

#endif // SETPARAMETERWINDOW_HPP
