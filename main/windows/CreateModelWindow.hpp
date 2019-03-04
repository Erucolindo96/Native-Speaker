﻿#ifndef CREATEMODELWINDOW_HPP
#define CREATEMODELWINDOW_HPP

#include "ui_CreateModelWindow.h"
#include"models/gmmmodel.hpp"
#include"models/diagonal_model.hpp"
#include<utils/Runnable.hpp>
#include<QTextBlock>
#include<map>
#include<alize.h>
#include<configuration/ConfigManager.hpp>
#include<QMessageBox>

class CreateModelWindow : public QDialog//, public Runnable
{
  Q_OBJECT

public:
  class CreateModelValidator
    {
  public:
      const QList<QChar> invalid_chars_model_name_ = {'/', '\\', '\'', '\'', ' ', '\t'};

      explicit CreateModelValidator() = default;
      CreateModelValidator(const CreateModelValidator& other) = default;
      CreateModelValidator& operator =(const CreateModelValidator &other) = default;
      CreateModelValidator(CreateModelValidator&& other) = default;
      CreateModelValidator& operator =(CreateModelValidator &&other) = default;


      bool isModelValid(const QString &model_name)const;
      bool isDescriptionValid(const QString &desc)const;
      bool isDistribCntValid(const QString &distrib_cnt)const;
    // brak walidacji typu, jeśli wystąpi wyjątek to znaczy, ze cos jest nie tak w kodzie -
    //taka sytuacja nie powinna wystąpic, bo tam mamy liste z której user wybiera elementy
    //bool isTypeValid(const QString &type, std::map<string, alize::DistribType> &mapping)const;
    };
  explicit CreateModelWindow(QWidget *parent = 0);
  std::unique_ptr<GmmModel> getCreatedGmmModel();
  void setConfig(ConfigManager conf);
  ConfigManager getConfig()const;
  ~CreateModelWindow() override = default ;

  public slots:
  void close();

signals:
  void modelCreated();


private slots:
  void on_create_button_released();

private:
  Ui::CreateModelWindow ui;
  std::unique_ptr<GmmModel> created_model_;
  ConfigManager config_;
  CreateModelValidator validator_;

  void createModel(QString model_name,alize::DistribType type,
                   QString description, uint32_t distrib_cnt, uint32_t vect_size);
  bool reactOnInvalidModelName(const QString &model_name)const;
  bool reactOnInvalidDescription(const QString  &desc)const;
  bool reactOnInvalidDistribCnt(const QString &distrib_cnt)const;
  // brak walidacji typu, jeśli wystąpi wyjątek to znaczy, ze cos jest nie tak w kodzie -
  //taka sytuacja nie powinna wystąpic, bo tam mamy liste z której user wybiera elementy
//  bool reactOnInvalidType(const QString &distrib_cnt);


};



#endif // CREATEMODELWINDOW_HPP
