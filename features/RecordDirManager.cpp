#include "RecordDirManager.hpp"

RecordDirManager::RecordDirManager(ConfigManager conf):conf_(conf)
{}

void RecordDirManager::setConfig(const ConfigManager &conf)
{
  conf_ = conf;
}

ConfigManager RecordDirManager::getConfig()const
{
  return conf_;
}

bool RecordDirManager::isDirExist(const std::string &model_name)const
{
  QDir model_dir((conf_.getFeatureFolder() + "/" + model_name).c_str());
  return model_dir.exists();
}

void RecordDirManager::createModelDir(const std::string &model_name)
{
  checkFeatureFolder();
  QDir feature_dir(conf_.getFeatureFolder().c_str() );
  bool created = feature_dir.mkdir( model_name.c_str());
  if(!created)
  {
    throw UnableToCreateFolder(__FILE__ + std::string(", line: ") + std::to_string(__LINE__)
                               + std::string(" - unable to create folder named" + model_name));
  }
}

void RecordDirManager::removeModelDir(const std::string &model_name)
{
  checkFeatureFolder();

  QDir feature_dir(conf_.getFeatureFolder().c_str() );
  bool removed = feature_dir.rmdir(model_name.c_str());
  if(!removed)
  {
    throw UnableToRemoveFolder(__FILE__ + std::string(", line: ") + std::to_string(__LINE__)
                               + std::string(" - unable to remove folder named" + model_name));
  }

}

void RecordDirManager::cleanModelDir(const std::string &model_name)
{
  checkFeatureFolder();
  QDir model_dir((conf_.getFeatureFolder()+ "/" + model_name).c_str() );
  if(!isDirExist(model_name))
  {
    throw UnableToCleanFolder(__FILE__ + std::string(", line: ") + std::to_string(__LINE__)
                      + std::string(" - model dir does not exist"));

  }
  auto files_to_remove = model_dir.entryList();
  for(auto file:files_to_remove)
  {
    model_dir.remove(file);
  }
  model_dir.refresh();
//  const QString this_dir = ".", up_dir = "..";
  const uint32_t EMPTY_DIR_FILES_CNT = 2;// zawiera folder "." i ".."
  if(model_dir.entryList().size() > EMPTY_DIR_FILES_CNT )
  {
    throw UnableToCleanFolder(__FILE__ + std::string(", line: ") + std::to_string(__LINE__)
                              + std::string(" - unable to clean model folder"));
  }
}


void RecordDirManager::checkFeatureFolder()const
{
  QDir feature_dir(conf_.getFeatureFolder().c_str());
  if(!feature_dir.exists())
  {
    throw DirNotFound(__FILE__ + std::string(", line: ") + std::to_string(__LINE__)
                      + std::string(" - feature folder dir does not exist"));
  }

}
