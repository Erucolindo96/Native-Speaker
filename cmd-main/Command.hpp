#ifndef COMMAND_HPP
#define COMMAND_HPP

#include<QObject>
#include"configuration/ConfigManager.hpp"
#include"configuration/ConfigValidator.hpp"
#include"models/ModelManager.hpp"
#include"record-base/RecBaseManager.hpp"
#include"features/FeatureManager.hpp"
#include<stdexcept>
#include<QCommandLineParser>
#include"cmd-main/CommandExecutor.hpp"
#include"cmd-main/CommandParamContainer.hpp"
#include<QDebug>
class ErrorCodeException : public std::logic_error
{

public:
  int8_t error_code_;

  ErrorCodeException(const std::string &msg, int8_t error_code):
    std::logic_error(msg), error_code_(error_code)
  {}
};

class NormallyExitException : public std::logic_error
{
public :
  NormallyExitException(const std::string &msg) : std::logic_error(msg)
  {}
};

class Command: public QObject
{
  Q_OBJECT

public:
  Command() = default;
  Command(const Command &o) = default;
  Command& operator=(const Command &o) = default;
  Command(Command &&o) = default;
  Command& operator=(Command &&o) = default;


  /**
   * @brief execute Metoda zlecająca wykonanie komendy.
   * Najpierw sprawdzana jest konfiguracja i jej poprawność, następnie poprawność parametrów komendy,
   * po czym parametry są zapisywane do pół klasy i komenda jest wykonywana
   * Korzysta z metod checkSyntax(), readArgs(), oraz performCommand() - te metody muszą być zaimplementowane w klasach pochodnych
   * Na końcu rzuca wyjątek NormallyExitException - w celu wymuszenia zamknięcia programu
   * @throw NormallyExitException jesli komenda wykonała się poprawnie
   * @throw ErrorCodeException jeśli wystąpił błąd
   */
  virtual void execute();
  /**
   * @brief checkSyntax Sprawdza istnienie argumentów i ich poprawność.
   * Woła reakcje na błędy składni argumentów, albo ich błędną wartość
   * Jest wołana przez execute().
   * Implementuje się ją w klasach pochodnych.
   * @throw ErrorCodeException jeśli wystąpił błąd
   * @see execute()
   */
  virtual void checkSyntax()const = 0;
  /**
   * @brief readArgs Wczytuje argumenty do pół klasy.
   * Zakłada, że ich poprawnośc jest już sprawdzona.
   * Jest wołana przez execute().
   * Implementuje się ją w klasach pochodnych.
   * @throw ErrorCodeException jeśli wystąpił błąd
   * @see execute()
   */
  virtual void readArgs() = 0;

  /**
   * @brief performCommand Wykonuje funkcjonalność komendy.
   * Zakłada, że argumenty zostały wczytane do pól klasy
   * Jest wołana przez execute();
   * Implementuje się ją w klasach pochodnych.
   *  @throw ErrorCodeException jeśli wystąpił błąd
   * @see execute()
   */
  virtual void performCommand() = 0;

  virtual void acceptExecutor(const CommandExecutor &executor) = 0;

  void setFeatureManagerPtr(FeatureManager *ptr);

  void setModelManagerPtr(ModelManager *ptr);

  void setConfigManagerPtr(ConfigManager *ptr);

  void setRecBaseManagerPtr(RecBaseManager *ptr);

  void setCommandLineParserPtr(QCommandLineParser *ptr);
  /**
   * @brief checkConfigExistance Sprawdza, czy konfiguracja została wskazana w argumentach programu
   * oraz czy istnieje jako plik o rozszerzeniu ".conf".
   * Wypisuje info o błędzie w razie jej braku
   * Wołane przez execute().
   * @throw ErrorCodeException jeśli wystąpił błąd
   * @see execute()
   */
  void checkConfigExistance();

  /**
   * @brief readConfig Wczytuje konfigurację
   * Wołane przez execute().
   * @throw ErrorCodeException jeśli wystąpił błąd
   * @see execute()
   */
  void readConfig();

  /**
   * @brief reactOnMistakesInConfig Sprawdza, czy konfiguracja jest cała, tj czy wszystkie wymanage parametry są obecne
   * Jeśli któregoś z parametrów nie ma, albo jest błędny, to wypisuje info o jej braku
   * Wołane przez execute();
   * @throw ErrorCodeException jeśli wystąpił błąd
   * @see execute()
   */
  void reactOnMistakesInConfig();



protected:
  ModelManager *model_man_ptr_;
  FeatureManager *f_manager_ptr_;
  ConfigManager *config_ptr_;
  RecBaseManager *r_base_man_ptr_;
  QCommandLineParser *parser_ptr_;
};



#endif // COMMAND_HPP
