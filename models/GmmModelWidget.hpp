#ifndef GMMMODELWIDGET_HPP
#define GMMMODELWIDGET_HPP

#include "ui_GmmModelWidget.h"
#include<alize.h>
#include<QtWidgets/QLabel>
#include<QtWidgets/QTextBrowser>

/**
 * @brief The GmmModelWidget class Klasa wyświetlająca w formie QWidgetu model mówcy.
 * Odpowiada za wyświetlenie danych, pobieranych przez settery
 */
class GmmModelWidget : public QFrame
{
  Q_OBJECT

public:
  explicit GmmModelWidget(QWidget *parent = 0,const QString &name="", const uint32_t cnt=0,
                          alize::DistribType type=alize::DistribType_GD, const QString &desc="");
  void setName(const QString &name);
  void setDistribCnt(const uint32_t cnt);
  void setType(alize::DistribType type);
  void setDescription(const QString &desc);

  virtual ~GmmModelWidget() = default;
private:
  Ui::GmmModelWidget ui;
};

#endif // GMMMODELWIDGET_HPP
