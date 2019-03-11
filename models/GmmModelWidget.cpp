#include "GmmModelWidget.hpp"

GmmModelWidget::GmmModelWidget(QWidget *parent, const QString &name, const uint32_t cnt,
                               alize::DistribType type, const QString &desc) :
  QFrame(parent)
{
  ui.setupUi(this);
  setName(name);
  setDistribCnt(cnt);
  setType(type);
  setDescription(desc);
}

void GmmModelWidget::setName(const QString &name)
{
  ui.label_name_val->setText(name);
}

void GmmModelWidget::setDistribCnt(const uint32_t cnt)
{
  QString cnt_str = to_string(cnt).c_str();
  ui.label_dstrib_cnt_val->setText(cnt_str);
}

void GmmModelWidget::setType(alize::DistribType type)
{
  if(type == alize::DistribType_GD)
  {
    ui.label_type_val->setText("Diagonal");
  }
  else
  {
    ui.label_type_val->setText("Full Cov");
  }
}
void GmmModelWidget::setDescription(const QString &desc)
{
  ui.textBrowser_desc->setText(desc);
}
