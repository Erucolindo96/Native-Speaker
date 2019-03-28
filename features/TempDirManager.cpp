#include "TempDirManager.hpp"

//TempDirManager::TempDirManager(ConfigManager conf):ModelDirManager(conf)
//{}

//void TempDirManager::createTempDir()
//{
//  ModelDirManager::createModelDir(TEMP_DIR_NAME);
//}

//void TempDirManager::cleanTempDir()
//{
//  ModelDirManager::cleanModelDir(TEMP_DIR_NAME);
//}

//void TempDirManager::removeTempDir()
//{
//  ModelDirManager::removeModelDir(TEMP_DIR_NAME);
//}

//void TempDirManager::createModelDir(const std::string &model_name)
//{
//  if(model_name == TEMP_DIR_NAME)
//  {
//    throw UnableToCreateFolder(__FILE__ + std::string(", line: ") + std::to_string(__LINE__)
//                               + std::string(" - trying to create temp folder with bad method"));
//  }
//  ModelDirManager::createModelDir(model_name);
//}

//void TempDirManager::removeModelDir(const std::string &model_name)
//{
//  if(model_name == TEMP_DIR_NAME)
//  {
//    throw UnableToRemoveFolder(__FILE__ + std::string(", line: ") + std::to_string(__LINE__)
//                               + std::string(" - trying to remove temp folder with bad method"));
//  }
//  ModelDirManager::removeModelDir(model_name);

//}
//void TempDirManager::cleanModelDir(const std::string &model_name)
//{
//  if(model_name == TEMP_DIR_NAME)
//  {
//    throw UnableToCleanFolder(__FILE__ + std::string(", line: ") + std::to_string(__LINE__)
//                               + std::string(" - trying to clean temp folder with bad method"));
//  }
//  ModelDirManager::cleanModelDir(model_name);
//}
