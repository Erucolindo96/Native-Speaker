#include "TempDirManager.hpp"

void TempDirManager::setFeatureFolderPath(const QString &dir_path)
{
  throw std::runtime_error("TODO");
}

QString TempDirManager::getFeatureFolderPath()const
{
  throw std::runtime_error("TODO");

}

bool TempDirManager::isDirExists()const
{
  throw std::runtime_error("TODO");

}
TempDir TempDirManager::getTempDir()
{
  throw std::runtime_error("TODO");

}

TempDir TempDirManager::getTempDir()const
{
  throw std::runtime_error("TODO");

}



//TempDirManager::TempDirManager(ConfigManager conf):RecordDirManager(conf)
//{}

//void TempDirManager::createTempDir()
//{
//  RecordDirManager::createModelDir(TEMP_DIR_NAME);
//}

//void TempDirManager::cleanTempDir()
//{
//  RecordDirManager::cleanModelDir(TEMP_DIR_NAME);
//}

//void TempDirManager::removeTempDir()
//{
//  RecordDirManager::removeModelDir(TEMP_DIR_NAME);
//}

//void TempDirManager::createModelDir(const std::string &model_name)
//{
//  if(model_name == TEMP_DIR_NAME)
//  {
//    throw UnableToCreateFolder(__FILE__ + std::string(", line: ") + std::to_string(__LINE__)
//                               + std::string(" - trying to create temp folder with bad method"));
//  }
//  RecordDirManager::createModelDir(model_name);
//}

//void TempDirManager::removeModelDir(const std::string &model_name)
//{
//  if(model_name == TEMP_DIR_NAME)
//  {
//    throw UnableToRemoveFolder(__FILE__ + std::string(", line: ") + std::to_string(__LINE__)
//                               + std::string(" - trying to remove temp folder with bad method"));
//  }
//  RecordDirManager::removeModelDir(model_name);

//}
//void TempDirManager::cleanModelDir(const std::string &model_name)
//{
//  if(model_name == TEMP_DIR_NAME)
//  {
//    throw UnableToCleanFolder(__FILE__ + std::string(", line: ") + std::to_string(__LINE__)
//                               + std::string(" - trying to clean temp folder with bad method"));
//  }
//  RecordDirManager::cleanModelDir(model_name);
//}
