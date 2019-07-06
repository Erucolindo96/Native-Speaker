#ifndef CMDVERIFYMODEL_HPP
#define CMDVERIFYMODEL_HPP

#include"cmd-main/CmdDiffLLK.hpp"

class CmdVerifyModel: public CmdDiffLLK
{
public:
  CmdVerifyModel() = default;
  CmdVerifyModel(const CmdVerifyModel &o) = default;
  CmdVerifyModel& operator=(const CmdVerifyModel &o) = default;
  CmdVerifyModel(CmdVerifyModel &&o) = default;
  CmdVerifyModel& operator=(CmdVerifyModel &&o) = default;

  ~CmdVerifyModel() override = default;

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
   * @throw ErrorCodeException jeśli wystąpił błąd
   * @see execute()
   */
  void performCommand() override;

  void acceptExecutor(const CommandExecutor &executor) override;


protected:
  double threshold_;
  bool is_threshold_double_;
  void validateArgs();


};

#endif // CMDVERIFYMODEL_HPP
