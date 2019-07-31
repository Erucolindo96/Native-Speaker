#ifndef CONFIGVALIDATOR_HPP
#define CONFIGVALIDATOR_HPP

#include"configuration/ConfigManager.hpp"

class ParamDoesNotExists : public std::logic_error
{
public:
  ConfigParam p_;
  std::string param_name_;
  ParamDoesNotExists(ConfigParam p, std::string param_name, std::string msg):
    std::logic_error(msg), p_(p), param_name_(param_name)
  {}
};

class ConfigValidator
{
public:
  ConfigValidator()=default;
  ConfigValidator(const ConfigValidator &other)=default;
  ConfigValidator& operator=(const ConfigValidator &other) = default;
  ConfigValidator(ConfigValidator &&other) = default;
  ConfigValidator& operator=(ConfigValidator &&other) = default;
  virtual ~ConfigValidator() = default;

  void isParamValid(const std::string param_name, const std::string param_val)const;
  void validateConfiguration(const ConfigManager &conf)const;
  /**
   * @brief checkComplexityOfConfig Sprawdza kompletnośc konfiguracji,
   * czyli czy zawiera wszystkie wymagane parametry
   * @param conf Konfiguracja do sprawdzenia
   * @throw ParamDoesNotExists jeśli parametr nie istnieje w badanej konfiguracji
   */
  void checkComplexityOfConfig(const ConfigManager &conf)const;
protected:
  ConfigParam paramNameValidation(const std::string &param_name)const;
  void paramValueValidation(ConfigParam p, const  std::string &param_val)const;

  void vectSizeValidation(const std::string &paran_val)const;
  void modelDirValidation(const std::string &paran_val)const;
//  void ubmDirValidation(const std::string &paran_val)const;
  void featureFolderValidation(const std::string &paran_val)const;
  void isDebugValidation(const std::string &paran_val)const;

  void dirExistanceValidation(const std::string &param_name,
                              const std::string &param_val)const;
};

#endif // CONFIGVALIDATOR_HPP
