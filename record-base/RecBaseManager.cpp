#include "RecBaseManager.hpp"

void RecBaseManager::setFeatureFolder(const QString &path)
{
  throw std::runtime_error("TODO");
}

QDir RecBaseManager::getFeatureFolder()const
{
  throw std::runtime_error("TODO");
}

const std::vector<Record> RecBaseManager::getRecordsOfModel(const std::string &model_name)const
{
  throw std::runtime_error("TODO");
}

void RecBaseManager::setRecordToBase(const Record &r, const std::string &model_name)
{
  throw std::runtime_error("TODO");
}

bool RecBaseManager::isRecordExists(const Record &r, const std::string &model_name)const
{
  throw std::runtime_error("TODO");
}
