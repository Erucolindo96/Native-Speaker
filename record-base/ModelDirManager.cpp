#include "ModelDirManager.hpp"

//ModelDirManager::ModelDirManager(ConfigManager conf):conf_(conf)
//{}

//void ModelDirManager::setConfig(const ConfigManager &conf)
//{
//  conf_ = conf;
//}

//ConfigManager ModelDirManager::getConfig()const
//{
//  return conf_;
//}

void ModelDirManager::setFeatureFolder(const QString &path)
{

}

QDir ModelDirManager::getFeatureFolder()const
{

}

bool ModelDirManager::isDirExist(const std::string &model_name)const
{
//  QDir model_dir((conf_.getFeatureFolder() + "/" + model_name).c_str());
//  return model_dir.exists();
  throw std::runtime_error("TODO");
}

RecordDir ModelDirManager::createModelDir(const std::string &model_name)
{

}

void ModelDirManager::removeModelDir(const std::string &model_name)
{

}

RecordDir ModelDirManager::getRecordDir(const std::string &model_name)const
{

}
std::vector<RecordDir> ModelDirManager::getAllDirs()const
{

}

//void ModelDirManager::createModelDir(const std::string &model_name)
//{
//  checkFeatureFolder();
//  QDir feature_dir(conf_.getFeatureFolder().c_str() );
//  bool created = feature_dir.mkdir( model_name.c_str());
//  if(!created)
//  {
//    throw UnableToCreateFolder(__FILE__ + std::string(", line: ") + std::to_string(__LINE__)
//                               + std::string(" - unable to create folder named" + model_name));
//  }
//}

//void ModelDirManager::removeModelDir(const std::string &model_name)
//{
//  checkFeatureFolder();

//  QDir feature_dir(conf_.getFeatureFolder().c_str() );
//  bool removed = feature_dir.rmdir(model_name.c_str());
//  if(!removed)
//  {
//    throw UnableToRemoveFolder(__FILE__ + std::string(", line: ") + std::to_string(__LINE__)
//                               + std::string(" - unable to remove folder named" + model_name));
//  }

//}

//void ModelDirManager::cleanModelDir(const std::string &model_name)
//{
//  checkFeatureFolder();
//  QDir model_dir((conf_.getFeatureFolder()+ "/" + model_name).c_str() );
//  if(!isDirExist(model_name))
//  {
//    throw UnableToCleanFolder(__FILE__ + std::string(", line: ") + std::to_string(__LINE__)
//                      + std::string(" - model dir does not exist"));

//  }
//  auto files_to_remove = model_dir.entryList();
//  for(auto file:files_to_remove)
//  {
//    model_dir.remove(file);
//  }
//  model_dir.refresh();
////  const QString this_dir = ".", up_dir = "..";
//  const int32_t EMPTY_DIR_FILES_CNT = 2;// zawiera folder "." i ".."
//  if(model_dir.entryList().size() > EMPTY_DIR_FILES_CNT )
//  {
//    throw UnableToCleanFolder(__FILE__ + std::string(", line: ") + std::to_string(__LINE__)
//                              + std::string(" - unable to clean model folder"));
//  }
//}


//void ModelDirManager::checkFeatureFolder()const
//{
//  QDir feature_dir(conf_.getFeatureFolder().c_str());
//  if(!feature_dir.exists())
//  {
//    throw DirNotFound(__FILE__ + std::string(", line: ") + std::to_string(__LINE__)
//                      + std::string(" - feature folder dir does not exist"));
//  }

//}
