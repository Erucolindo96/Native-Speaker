#ifndef CONFIGMANAGER_HPP
#define CONFIGMANAGER_HPP
#include<alize.h>
#include<map>
#include<string>
#include"exceptions/simple_exceptions.hpp"
#include<QtCore/QString>
#include<QtCore/QDir>
enum ConfigParam
{
  VECT_SIZE,
  MODEL_DIR,
  UBM_DIR,
  FEATURE_FOLDER,
  IS_DEBUG
};


class ConfigManager: protected alize::Config
{

public:
  friend class ConfigValidator;
  static const std::map<ConfigParam, std::string> VALID_PARAMS_;

  ConfigManager()=default;
  ConfigManager(const ConfigManager &other)=default;
  ConfigManager& operator=(const ConfigManager &other);
  ConfigManager(ConfigManager &&other);
  ConfigManager& operator=(ConfigManager &&other);

  uint32_t getVectSize()const;
  void setVectSize(uint32_t vect_size);

  std::string getModelFolder()const;
  void setModelFolder(std::string folder);

  std::string getUbmFolder()const;
  void setUbmFolder(std::string folder);

  std::string getFeatureFolder()const;
  void setFeatureFolder(std::string folder);

  void load(const alize::FileName &f);
  void save(const alize::FileName &f) const;

  void setParam(const alize::String &name, const alize::String &content);

  bool isEmpty()const;
  bool haveUbmFolder()const;
  bool haveModelFolder()const;
  bool haveFeatureFolder()const;
  bool haveVectSize()const;
  bool haveAllParams()const;

  static std::string PARAM_UBM_DIR();
  static std::string PARAM_FEATURE_FOLDER();
  static std::string PARAM_MODEL_DIR();
  static std::string PARAM_VECT_SIZE();

  virtual ~ConfigManager()=default;

};

#endif // CONFIGMANAGER_HPP
