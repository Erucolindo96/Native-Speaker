#ifndef LEARNINGTHREADWIDGET_HPP
#define LEARNINGTHREADWIDGET_HPP

#include "ui_LearningThreadWidget.h"
#include<memory>
#include"models/gmmmodel.hpp"

/**
 * @brief The LearningThreadWidget class Klasa służąca do wyświetlania postępu uczenia danego modelu
 * Nie posiada żadnej logiki - wyświetla po prostu ustawiane w setterach parametry, odpowiednio w etykiecie(nazwe modelu)
 * oraz postep uczenia(aktualną iteracje uczenia na pasku postępu).
 * Posiada również wskazanie do uczonego modelu - sama z niego nie korzysta, aby ustawiać swoje parametry
 * natomiast może to być uzyte, aby zapewnić unikalność obiektu(jeżeli będa 2 modele o tej samej nazwie - do którego modelu odnosi się widget?).
 *
 */
class LearningThreadWidget : public QFrame
{
  Q_OBJECT

public:
  explicit LearningThreadWidget(QWidget *parent = 0);
  LearningThreadWidget(const LearningThreadWidget &other) = default;
  LearningThreadWidget& operator=(const LearningThreadWidget &other) = default;

  LearningThreadWidget(LearningThreadWidget &&other) = default;
  LearningThreadWidget& operator=(LearningThreadWidget &&other) = default;

  /**
   * @brief setIterCnt Ustawia ilośc iteracji, jaką jest uczony model
   * Wartość ta jest wstawiana do QProgressBara jako maksymalna
   * @param iter_cnt Ilość iteracji uczenia danego modelu
   */
  void setIterCnt(uint32_t iter_cnt);
  /**
   * @brief getIterCnt Zwraca wartość ustawioną do QProgressBara jako maksymalną
   * @return Ustawiona uprzednio wartość maksymalna QProgressBara
   */
  uint32_t getIterCnt()const;

  /**
   * @brief setModelName Ustawia etykietę widgetu, wyświetlającą nazwę uczonego modelu
   * @param str Nazwa uczonego modelu
   */
  void setModelName(const QString &str);
  /**
   * @brief getModelName Zwraca wartość etykiety, wyświetlającej nazwę uczonego modelu
   * @return Napis ustawiony w etykiecie nazwy modelu
   */
  QString getModelName()const;

  /**
   * @brief setActualIter Ustawia aktualną wartość paska QProgressBara
   * Czyli numer aktualnie trwającej iteracji uczenia
   * @param act_iter Numer aktualnej iteracji uczenia
   */
  void setActualIter(uint32_t act_iter);
  /**
   * @brief getActualIter Zwraca aktualną wartośc ustawioną dla paska QProgressBara
   * @return Wartość przypisana paskowi QProgressBara - aktualana iteracja uczenia
   */
  uint32_t getActualIter()const;

  /**
   * @brief setModelPtr Ustawia wskazanie do modelu, którego  parametry uczenia wyświetla dany widget
   * Klasa nie ustawia za jego pomocą żadnych własnych parametrów - służy tylko do określenia modelu
   * którego parametry uczenia wyświetla widget
   * @param model Aktualnie uczony model, którego parametry uczenia wyświetla widget
   */
  void setModelPtr(std::shared_ptr<GmmModel> model);
  /**
   * @brief getModelPtr Zwraca wskazanie do modelu, którego  parametry uczenia wyświetla dany widget
   * Klasa nie ustawia za jego pomocą żadnych własnych parametrów - służy tylko do określenia modelu
   * @return Aktualnie uczony model, którego parametry uczenia wyświetla widget
   */
  std::shared_ptr<const GmmModel> getModelPtr()const;

  ~LearningThreadWidget() override  = default;

private:
  Ui::LearningThreadWidget ui;
  std::shared_ptr<const GmmModel> m_;
};

#endif // LEARNINGTHREADWIDGET_HPP
