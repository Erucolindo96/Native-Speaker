#ifndef CONFIGVALIDATOR_HPP
#define CONFIGVALIDATOR_HPP

#include"configuration/ConfigManager.hpp"

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

protected:
  ConfigParam paramNameValidation(const std::string &param_name)const;
  void paramValueValidation(ConfigParam p, const  std::string &param_val)const;

  void vectSizeValidation(const std::string &paran_val)const;
  void modelDirValidation(const std::string &paran_val)const;
  void ubmDirValidation(const std::string &paran_val)const;
  void featureFolderValidation(const std::string &paran_val)const;
  void isDebugValidation(const std::string &paran_val)const;

  void dirExistanceValidation(const std::string &param_name,
                              const std::string &param_val)const;
};

#endif // CONFIGVALIDATOR_HPP
