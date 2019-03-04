#include "ConfigManager.hpp"


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
  setParam(PARAM_VECT_SIZE, std::to_string(vect_size).c_str());
}

std::string ConfigManager::getModelFolder()const
{
  return getParam(PARAM_MODEL_DIR).c_str();
}
void ConfigManager::setModelFolder(std::string folder)
{
  setParam(PARAM_MODEL_DIR, folder.c_str());
}

std::string ConfigManager::getUbmFolder()const
{
  return getParam(PARAM_UBM_DIR).c_str();
}

void ConfigManager::setUbmFolder(std::string folder)
{
  setParam(PARAM_UBM_DIR, folder.c_str());
}

std::string ConfigManager::getFeatureFolder()const
{
  return getParam(PARAM_FEATURE_FOLDER).c_str();
}

void ConfigManager::setFeatureFolder(std::string folder)
{
  setParam(PARAM_FEATURE_FOLDER, folder.c_str());
}

void ConfigManager::load(const alize::FileName &f)
{
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
  return existsParam(PARAM_UBM_DIR);
}
bool ConfigManager::haveModelFolder()const
{
  return existsParam(PARAM_MODEL_DIR);
}
bool ConfigManager::haveFeatureFolder()const
{
  return existsParam(PARAM_FEATURE_FOLDER);
}
bool ConfigManager::haveVectSize()const
{
  return existsParam(PARAM_VECT_SIZE);
}
bool ConfigManager::haveAllParams()const
{
  return haveUbmFolder() && haveModelFolder() && haveFeatureFolder()
      && haveVectSize();
}

