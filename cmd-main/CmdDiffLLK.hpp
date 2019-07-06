#ifndef CMDDIFFLLK_HPP
#define CMDDIFFLLK_HPP

#include"cmd-main/Command.hpp"
#include"models/AlgoManager.hpp"
#include"features/FeatureReaderSilenceCutter.hpp"
#include"models/verificator.hpp"

class CmdDiffLLK: public Command
{
public:
  CmdDiffLLK() = default;
  CmdDiffLLK(const CmdDiffLLK &o) = default;
  CmdDiffLLK& operator=(const CmdDiffLLK &o) = default;
  CmdDiffLLK(CmdDiffLLK &&o) = default;
  CmdDiffLLK& operator=(CmdDiffLLK &&o) = default;

  ~CmdDiffLLK() override = default;

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
  QString model_name_, ubm_name_;
  QFileInfo record_path_;

  void validateArgs();

};

#endif // CMDDIFFLLK_HPP
