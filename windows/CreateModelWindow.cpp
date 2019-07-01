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
  const std::map<string, alize::DistribType> DISTRIB_TYPE_MAP
  {
    {ui.comboBox_distrib_type->itemText(0).toStdString(), alize::DistribType_GD},
    {ui.comboBox_distrib_type->itemText(1).toStdString(), alize::DistribType_GF}
  };

  auto model_name = ui.lineEdit_model_name->text();//ui.textEdit_model_name->document()->firstBlock().text();
  auto distrib_cnt_str = ui.lineEdit_distrib_cnt->text();//ui.textEdit_distrib_cnt->document()->firstBlock().text();
  auto description = ui.textEdit_description->document()->toPlainText();
  alize::DistribType type = DISTRIB_TYPE_MAP.at
                            (ui.comboBox_distrib_type->currentText().toStdString());

  if(!reactOnInvalidModelName(model_name) ||
     !reactOnInvalidDescription(description) ||
     !reactOnInvalidDistribCnt(distrib_cnt_str))
  {
    return;
  }

  createModel(model_name, type, description, distrib_cnt_str.toInt(), config_.getVectSize());
  accept();
}


void CreateModelWindow::createModel(QString model_name,alize::DistribType type,
                 QString description, uint32_t distrib_cnt, uint32_t vect_size)
{
  if(type == alize::DistribType_GD)
  {
    created_model_ = make_unique<DiagonalModel>(
                       distrib_cnt,vect_size);
    created_model_->setName(model_name.toStdString());
  }
  else
  {
    throw std::runtime_error("TODO");
  }

}

bool CreateModelWindow::reactOnInvalidModelName(const QString &model_name)const
{
  if(!validator_.isModelValid(model_name))
  {
    QString msg = QString("Model name is invalid. "
                                "Please remove from model name spaces and "
                                "characters: ");
    foreach (auto character, validator_.invalid_chars_model_name_)
    {
      msg.append(character);
      msg.append(", ");
    }
    msg.append(".");
    QMessageBox::warning(const_cast<CreateModelWindow*>(this),
                         "Invalid Data",
                         msg ,QMessageBox::Ok);
    return false;
  }
  return true;
}

bool CreateModelWindow::reactOnInvalidDescription(const QString  &desc)const
{
  if(!validator_.isDescriptionValid(desc))
  {
    QString msg = QString("Description is invalid. Please correct them.");
    QMessageBox::warning(const_cast<CreateModelWindow*>(this),
                       "Invalid Data",
                       msg ,QMessageBox::Ok);
    return false;
  }
  return true;
}

bool CreateModelWindow::reactOnInvalidDistribCnt(const QString &distrib_cnt)const
{
  if(!validator_.isDistribCntValid(distrib_cnt))
  {
    QString msg = QString("Distrib count is invalid. It must be non-zero positive number.");
    QMessageBox::warning(const_cast<CreateModelWindow*>(this),
                       "Invalid Data",
                       msg ,QMessageBox::Ok);
    return false;
  }
  return true;
}






bool CreateModelWindow::CreateModelValidator::isModelValid(const QString &model_name)const
{
  bool ret = true;
  if(model_name.isEmpty())
  {
    ret = false;
  }
  foreach (QChar elem, invalid_chars_model_name_)
  {
    if(model_name.contains(elem))
    {
      ret = false;
    }
  }
  return ret;
}
bool CreateModelWindow::CreateModelValidator::isDescriptionValid(const QString &desc)const
{
  return true;
}
bool CreateModelWindow::CreateModelValidator::isDistribCntValid(const QString &distrib_cnt)const
{
  bool is_int = false;
  int distrib_cnt_int = distrib_cnt.toInt(&is_int);
  if(!is_int || distrib_cnt_int <= 0)
  {
    return false;
  }
  return true;
}
/*
bool CreateModelWindow::CreateModelValidator::isTypeValid(const QString &type,
                                                          std::map<string, alize::DistribType> &mapping)const
{
  try
  {
      alize::DistribType conv_type = mapping.at(type.toStdString());
  }
  catch(std::out_of_range e)
  {
    return false;
  }
  return true;
}
*/
