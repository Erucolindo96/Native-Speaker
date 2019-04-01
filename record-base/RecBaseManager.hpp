#ifndef RECBASEMANAGER_HPP
#define RECBASEMANAGER_HPP
#include"record-base/RecordDirManager.hpp"


class RecBaseManager
{
public:
  RecBaseManager() = default;
  RecBaseManager(const RecBaseManager &other) = default;
  RecBaseManager& operator=(const RecBaseManager &other) = default;
  RecBaseManager(RecBaseManager &&other) = default;
  RecBaseManager& operator=(RecBaseManager &&other) = default;

  void setFeatureFolder(const QString &path);
  QDir getFeatureFolder()const;

  const std::vector<Record> getRecordsOfModel(const std::string &model_name)const;
  void setRecordToBase(const Record &r, const std::string &model_name);
  bool isRecordExists(const Record &r, const std::string &model_name)const;

protected:
  RecordDirManager dir_manager_;
};

#endif // RECBASEMANAGER_HPP
