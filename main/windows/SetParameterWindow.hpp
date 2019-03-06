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

  explicit SetParameterWindow(QWidget *parent = 0);
  std::string getParamName()const;
  std::string getParamValue()const;

private slots:
  void on_save_button_released();

  void on_cancel_button_released();

  void on_toolButton_released();

signals:
  void paramReadyToSave();

private:
  Ui::SetParameterWindow ui;
  std::string param_, value_;

  void initComboBox()const;
  void readParamNameAndValue();

};

#endif // SETPARAMETERWINDOW_HPP
