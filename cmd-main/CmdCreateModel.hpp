#ifndef CMDCREATEMODEL_HPP
#define CMDCREATEMODEL_HPP

#include"cmd-main/Command.hpp"

class CmdCreateModel : public Command
{
public:
  CmdCreateModel() = default;
  CmdCreateModel(const CmdCreateModel &o) = default;
  CmdCreateModel& operator=(const CmdCreateModel &o) = default;
  CmdCreateModel(CmdCreateModel &&o) = default;
  CmdCreateModel& operator=(CmdCreateModel &&o) = default;

  /**
   * @brief checkSyntax Sprawdza istnienie argumentów i ich poprawność.
   * Woła reakcje na błędy składni argumentów, albo ich błędną wartość
   * Jest wołana przez execute().
   * @throw ErrorCodeException jeśli wystąpił błąd
   * @see execute()
   */
  void checkSyntax()const override;
  /**
   * @brief readArgs Wczytuje argumenty do pół klasy.
   * Zakłada, że ich poprawnośc jest już sprawdzona.
   * Jest wołana przez execute().
   * Implementuje się ją w klasach pochodnych.
   * @throw ErrorCodeException jeśli wystąpił błąd
   * @see execute()
   */
  void readArgs() override;

  /**
   * @brief performCommand Wykonuje funkcjonalność komendy.
   * Zakłada, że argumenty zostały wczytane do pól klasy
   * Jest wołana przez execute();
   * Implementuje się ją w klasach pochodnych.
   *  @throw ErrorCodeException jeśli wystąpił błąd
   * @see execute()
   */
  void performCommand() override;

  void acceptExecutor(const CommandExecutor &executor) override;

protected:
  QString model_name_;
  int32_t d_cnt_;
};

#endif // CMDCREATEMODEL_HPP
