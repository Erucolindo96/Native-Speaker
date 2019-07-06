#include "RecBaseManager.hpp"

void RecBaseManager::setFeatureFolderPath(const QString &path)
{
  dir_manager_.setFeatureFolder(path);
}

QString RecBaseManager::getFeatureFolderPath()const
{
  return dir_manager_.getFeatureFolder();
}

const std::vector<Record> RecBaseManager::getRecordsOfModel(const std::string &model_name)const
{
  if(!dir_manager_.isDirExists(model_name))
  {
    return std::vector<Record>();
  }
  return dir_manager_.getModelDir(model_name).list();
}

void RecBaseManager::setRecordToBase(const Record &r, const std::string &model_name)
{
  auto model_dir = dir_manager_.getModelDir(model_name);
  model_dir.addRecord(r);
}

bool RecBaseManager::isRecordExists(const Record &r, const std::string &model_name)const
{

  if(!dir_manager_.isDirExists(model_name))
  {
    return false;
  }
  return dir_manager_.getModelDir(model_name).haveRecord(r);

}

QString RecBaseManager::getModelPath(const QString &model_name, const QString &feature_folder_path)
{
  return feature_folder_path + "/" + model_name;
}


std::vector<Record> RecBaseManager::getWavRecordsFromDir(const QString &dir_path)
{
  std::vector<Record> recs;

  QDir records(dir_path);
  records.setFilter(QDir::NoDotAndDotDot| QDir::Files);
  records.setNameFilters({"*.wav"});

  Record r;
  for(auto file: records.entryInfoList())
  {
    r.setPath(file.absoluteFilePath());
    recs.push_back(r);
  }
  return recs;
}

