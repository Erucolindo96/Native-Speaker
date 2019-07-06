#ifndef CMDLEARNMODEL_HPP
#define CMDLEARNMODEL_HPP
#include"cmd-main/Command.hpp"
#include"models/AlgoManager.hpp"
#include"features/FeatureReaderSilenceCutter.hpp"
class CmdLearnModel: public Command
{
  Q_OBJECT
public:
  CmdLearnModel() = default;
  CmdLearnModel(const CmdLearnModel &o) = default;
  CmdLearnModel& operator= (const CmdLearnModel &o) = default;
  CmdLearnModel(CmdLearnModel &&o) = default;
  CmdLearnModel& operator= (CmdLearnModel &&o) = default;

  ~CmdLearnModel() override = default;
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
  QString model_name_, algo_name_;
  QDir record_dir_;
  int32_t iters_cnt_;
  std::unique_ptr<LearningAlgo> algo_ptr_;
  bool iter_is_int_;

  void validateArgs();
};

#endif // CMDLEARNMODEL_HPP
