﻿#include "ConfigManager.hpp"

const std::map<ConfigParam, std::string> ConfigManager::VALID_PARAMS_ =
{
  {VECT_SIZE, "vectSize"},
  {UBM_DIR, "ubmDir"},
  {MODEL_DIR, "modelDir"},
  {FEATURE_FOLDER, "featureFolder"},
  {IS_DEBUG, "debug"}
};



ConfigManager& ConfigManager::operator=(const ConfigManager &other)
{
  if(this == &other)
    return *this;
  alize::Config::operator =(other);
  return *this;

}

ConfigManager::ConfigManager(ConfigManager &&other):alize::Config(other)
{}

ConfigManager& ConfigManager::operator=(ConfigManager &&other)
{
  return operator =(other);
}

uint32_t ConfigManager::getVectSize()const
{
  return getParam_vectSize();
}
void ConfigManager::setVectSize(uint32_t vect_size)
{
  setParam(VALID_PARAMS_.at(VECT_SIZE).c_str(), std::to_string(vect_size).c_str());
}

std::string ConfigManager::getModelFolder()const
{
  std::string param_name = VALID_PARAMS_.at(MODEL_DIR).c_str();
  return getParam(param_name.c_str()).c_str();
}
void ConfigManager::setModelFolder(std::string folder)
{
  setParam(VALID_PARAMS_.at(MODEL_DIR).c_str(), folder.c_str());
}

std::string ConfigManager::getUbmFolder()const
{
  return getParam(VALID_PARAMS_.at(UBM_DIR).c_str()).c_str();
}

void ConfigManager::setUbmFolder(std::string folder)
{
  setParam(VALID_PARAMS_.at(UBM_DIR).c_str(), folder.c_str());
}

std::string ConfigManager::getFeatureFolder()const
{
  return getParam(VALID_PARAMS_.at(FEATURE_FOLDER).c_str()).c_str();
}

void ConfigManager::setFeatureFolder(std::string folder)
{
  setParam(VALID_PARAMS_.at(FEATURE_FOLDER).c_str(), folder.c_str());
}

void ConfigManager::load(const alize::FileName &f)
{
  alize::Config::reset();
  alize::Config::load(f);
}

void ConfigManager::save(const alize::FileName &f) const
{
  alize::Config::save(f);
}

bool ConfigManager::isEmpty()const
{
  //cout<<"Param Count: "<<getParamCount()<<endl;
  return getParamCount()==0?true:false;
}

bool ConfigManager::haveUbmFolder()const
{
  return existsParam(VALID_PARAMS_.at(UBM_DIR).c_str());
}
bool ConfigManager::haveModelFolder()const
{
  return existsParam(VALID_PARAMS_.at(MODEL_DIR).c_str());
}
bool ConfigManager::haveFeatureFolder()const
{
  return existsParam(VALID_PARAMS_.at(FEATURE_FOLDER).c_str());
}
bool ConfigManager::haveVectSize()const
{
  return existsParam(VALID_PARAMS_.at(VECT_SIZE).c_str());
}
bool ConfigManager::haveAllParams()const
{
  return haveUbmFolder() && haveModelFolder() && haveFeatureFolder()
      && haveVectSize();
}

std::string ConfigManager::PARAM_UBM_DIR()
{
  return ConfigManager::VALID_PARAMS_.at(UBM_DIR);
}
std::string ConfigManager::PARAM_FEATURE_FOLDER()
{
  return ConfigManager::VALID_PARAMS_.at(FEATURE_FOLDER);
}
std::string ConfigManager::PARAM_MODEL_DIR()
{
  return ConfigManager::VALID_PARAMS_.at(MODEL_DIR);
}
std::string ConfigManager::PARAM_VECT_SIZE()
{
  return ConfigManager::VALID_PARAMS_.at(VECT_SIZE);
}





