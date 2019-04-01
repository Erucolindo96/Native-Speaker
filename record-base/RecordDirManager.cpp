#include "RecordDirManager.hpp"




void RecordDirManager::setFeatureFolder(const QString &dir_path)
{
  feature_folder_path_ = dir_path;
  checkFeatureFolder();
}

QDir RecordDirManager::getFeatureFolder()const
{
  return QDir(feature_folder_path_);
}

bool RecordDirManager::isDirExists(const std::string &model_name)const
{
  checkFeatureFolder();
  QDir checked_dir(feature_folder_path_);
  return checked_dir.cd(model_name.c_str());

}

RecordDir RecordDirManager::getModelDir(const std::string &model_name)
{
  checkFeatureFolder();
  if(!QDir(feature_folder_path_).cd(model_name.c_str()))
  {
    QDir(feature_folder_path_).mkdir(model_name.c_str());
  }
  RecordDir ret;
  QDir getted_dir(feature_folder_path_);
  getted_dir.cd(model_name.c_str());
  ret.setDir(getted_dir);
  return ret;
}

void RecordDirManager::removeModelDir(const std::string &model_name)
{
  checkFeatureFolder();
  RecordDir model_dir;
  QDir removed_dir(feature_folder_path_);
  if(removed_dir.cd(model_name.c_str())) //znaczy, ze folder istnieje i trzeba go usunąć
  {
    model_dir.setDir(removed_dir);
    model_dir.removeAll();
    QDir(feature_folder_path_).rmdir(model_name.c_str());
  }
}

std::vector<RecordDir> RecordDirManager::getAllDirs()const
{
  checkFeatureFolder();
  std::vector<RecordDir> ret;
  RecordDir dir;
  QDir feature_dir(feature_folder_path_);
  feature_dir.setFilter(QDir::AllDirs|QDir::NoDotAndDotDot	);

  for(auto file: feature_dir.entryInfoList())
  {
    dir.setDir(file.absoluteDir());
    ret.push_back(dir);
  }
  return ret;
}

void RecordDirManager::checkFeatureFolder()const
{
  if(feature_folder_path_.isEmpty() || !QDir(feature_folder_path_).exists())
  {
    throw FeatureFolderNotFound(__FILE__ + std::string(", line: ") + std::to_string(__LINE__)
                      + std::string("feature folder path does not point to any real dir in filesystem"));
  }
}
