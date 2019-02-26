#include "CreateModelWindow.hpp"

CreateModelWindow::CreateModelWindow(QWidget *parent) :
  QDialog(parent)
{
  ui.setupUi(this);
  connect(ui.cancell_button, SIGNAL (clicked()), this, SLOT(close()));

}


  void CreateModelWindow::close()
  {
    QDialog::close();
  }


std::unique_ptr<GmmModel> CreateModelWindow::getCreatedGmmModel()
{
  return std::move(created_model_);
}

void CreateModelWindow::setConfig(ConfigManager conf)
{
  config_ = conf;
}

ConfigManager CreateModelWindow::getConfig()const
{
  return config_;
}

void CreateModelWindow::on_create_button_released()
{
  //TODO - zrobic walidacje
  auto model_name = ui.textEdit_model_name->document()->firstBlock().text();
  cout<<model_name.toStdString()<<endl;
  auto distrib_cnt = ui.textEdit_distrib_cnt->document()->firstBlock().text().toInt();
  cout<<distrib_cnt<<endl;
  auto description = ui.textEdit_description->document()->firstBlock().text();
  const std::map<string, alize::DistribType> distrib_type_mapping
  {
    {ui.comboBox_distrib_type->itemText(0).toStdString(), alize::DistribType_GD},
    {ui.comboBox_distrib_type->itemText(1).toStdString(), alize::DistribType_GF}
  };
  alize::DistribType type = distrib_type_mapping.at
                            (ui.comboBox_distrib_type->currentText().toStdString());
  cout<<type<<endl;
  createModel(model_name, type, description, distrib_cnt, config_.getVectSize());
  emit accepted();
  close();
}


void CreateModelWindow::createModel(QString model_name,alize::DistribType type,
                 QString description, uint32_t distrib_cnt, uint32_t vect_size)
{
  if(type == alize::DistribType_GD)
  {
    created_model_ = make_unique<DiagonalModel>(
                       distrib_cnt,vect_size, model_name.toStdString());
  }
  else
  {
    throw std::runtime_error("TODO");
  }

}
