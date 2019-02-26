#ifndef CREATEMODELWINDOW_HPP
#define CREATEMODELWINDOW_HPP

#include "ui_CreateModelWindow.h"
#include"models/gmmmodel.hpp"
#include"models/diagonal_model.hpp"
#include<utils/Runnable.hpp>
#include<QTextBlock>
#include<map>
#include<alize.h>
#include<configuration/ConfigManager.hpp>
class CreateModelWindow : public QDialog//, public Runnable
{
  Q_OBJECT

public:
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
  void createModel(QString model_name,alize::DistribType type,
                   QString description, uint32_t distrib_cnt, uint32_t vect_size);

};



#endif // CREATEMODELWINDOW_HPP
