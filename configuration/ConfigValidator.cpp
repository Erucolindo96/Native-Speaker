#include "ConfigValidator.hpp"


//public

void ConfigValidator::isParamValid(const std::string param_name, const std::string param_val)const
{
  ConfigParam p = paramNameValidation(param_name);
  paramValueValidation(p, param_val);
  //jeśli nie rzuciło wyjątku, to znaczy ze parametr i jego wartośc sa poprawne
}

void ConfigValidator::validateConfiguration(const ConfigManager &conf)const
{
  for(uint32_t i = 0; i<conf.getParamCount(); ++i)
  {
    isParamValid(conf.getParamName(i).c_str(), conf.getParamContent(i).c_str());
  }
}


//protected

ConfigParam ConfigValidator::paramNameValidation(const std::string &param_name)const
{
  for(auto i = ConfigManager::VALID_PARAMS_.cbegin(); i != ConfigManager::VALID_PARAMS_.cend(); ++i)
  {
    if(i->second == param_name)
    {
      return i->first;
    }
  }
  //jak nie znaleziono, to rzucamy wyjątek
  throw ParamNotValid(std::string("Parameter of name: ") +"\"" +param_name+"\""+
                        "doesn't exist");

}

void ConfigValidator::paramValueValidation(ConfigParam p, const  std::string &param_val)const
{
  switch (p)
  {
    case VECT_SIZE:
      vectSizeValidation(param_val);
      break;
    case MODEL_DIR:
      modelDirValidation(param_val);
      break;
    case UBM_DIR:
      ubmDirValidation(param_val);
      break;
    case FEATURE_FOLDER:
      featureFolderValidation(param_val);
      break;
    case IS_DEBUG:
      isDebugValidation(param_val);
      break;
    default:
      return;
  }

}



void ConfigValidator::vectSizeValidation(const std::string &param_val)const
{
  bool is_int = true;
  QString param_val_qt = param_val.c_str();
  int32_t param_val_int = param_val_qt.toInt(&is_int);
  if(!is_int || param_val_int <= 0)
  {
    throw ParamNotValid("Parameter \"vectSize\" is not valid. It must be natural number greather than 0.");
  }
}
void ConfigValidator::modelDirValidation(const std::string &param_val)const
{
  dirExistanceValidation(ConfigManager::VALID_PARAMS_.at(MODEL_DIR), param_val);
}
void ConfigValidator::ubmDirValidation(const std::string &param_val)const
{
  dirExistanceValidation(ConfigManager::VALID_PARAMS_.at(UBM_DIR), param_val);
}

void ConfigValidator::featureFolderValidation(const std::string &param_val)const
{
  dirExistanceValidation(ConfigManager::VALID_PARAMS_.at(FEATURE_FOLDER), param_val);
}
void ConfigValidator::isDebugValidation(const std::string &param_val)const
{
  if(param_val.compare("true") !=0 && param_val.compare("false") !=0 )
  {
    throw ParamNotValid("Param \"debug\" is invalid. It must be true or false.");
  }
}

void ConfigValidator::dirExistanceValidation(const std::string &param_name,
                            const std::string &param_val)const
{
  std::string msg = "Parameter \"";
  msg.append(param_name);
  msg.append("\" is not valid. It isn't a valid path in filesystem.");
  QDir model_dir(param_val.c_str());
  if(!model_dir.exists())
  {
    throw ParamNotValid(msg);
  }
}
