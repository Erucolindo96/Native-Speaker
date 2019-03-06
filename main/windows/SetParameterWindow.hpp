#ifndef SETPARAMETERWINDOW_HPP
#define SETPARAMETERWINDOW_HPP

#include "ui_SetParameterWindow.h"
#include <alize.h>
class SetParameterWindow : public QDialog
{
  Q_OBJECT

public:
  class SetParameterValidator
  {
//    Powinna istnieć klasa ConfigValidator, używana przez ConfigManager,
//    rzucająca wyjątek przy wprowadzeniu zlej wartosci parametru
//    Wyjątek bedzie łapany przez MainWindow, ukazując warninga o złej wartości parametru
//    (np. nieistnieniu danego folderu, lub braku wartosci numerycznej dla vectSize)
//    Ponadto ConfigManager powinien zawierać info o dostęonych parametrach
//    które powinny być pobierane przez ConfigValidator i SetParameterValidator
//    i wykorzystywane przy walidacji(parametr inny niż zdefiniowany == błąd)
//    i przy wyborze ustawianego parametru w ComboBoxie
//    (wyswietlana lista w oparciu o zdefiniowane w jednym miejscu nazwy, aby uniknąć powatzrania listy nazw parametrów)

    explicit SetParameterValidator() = default;
    SetParameterValidator(const SetParameterValidator& other) = default;
    SetParameterValidator& operator =(const SetParameterValidator &other) = default;
    SetParameterValidator(SetParameterValidator&& other) = default;
    SetParameterValidator& operator =(SetParameterValidator &&other) = default;

    bool isValid()const;

  };

  explicit SetParameterWindow(QWidget *parent = 0);

private slots:
  void on_save_button_released();

  void on_cancel_button_released();

private:
  Ui::SetParameterWindow ui;
  std::string param_, value_;
};

#endif // SETPARAMETERWINDOW_HPP
