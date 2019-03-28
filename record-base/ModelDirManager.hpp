#ifndef MODELSDIRMANAGER_HPP
#define MODELSDIRMANAGER_HPP

#include<QDir>
#include<QFile>
#include<QList>
#include"configuration/ConfigManager.hpp"
#include"exceptions/simple_exceptions.hpp"
#include"record-base/RecordDir.hpp"
/**
 * @brief The ModelsDirManager class Zarządza tworzeniem i usuwaniem folderów z nagraniami mówców
 * W tych folderach będą przechowywane nagrania, którymi uczono dane modele
 */
class ModelDirManager
{

public:
  ModelDirManager() = default;
  ModelDirManager(const ModelDirManager &other) = default;
  ModelDirManager& operator=(const ModelDirManager &other) = default;
  ModelDirManager(ModelDirManager &&other) = default;
  ModelDirManager& operator=(ModelDirManager &&other) = default;

//  void setConfig(const ConfigManager &conf);
//  ConfigManager getConfig()const;

  void setFeatureFolder(const QString &path);
  QDir getFeatureFolder()const;

  bool isDirExist(const std::string &model_name)const;
  RecordDir createModelDir(const std::string &model_name);
  void removeModelDir(const std::string &model_name);
  RecordDir getRecordDir(const std::string &model_name)const;
  std::vector<RecordDir> getAllDirs()const;


//  virtual bool isDirExist(const std::string &model_name)const;
//  virtual void createModelDir(const std::string &model_name);
//  virtual void removeModelDir(const std::string &model_name);
//  virtual void cleanModelDir(const std::string &model_name);

 // virtual void writeRecord(const std::string &model_name, const QFile &file_to_write);
 // virtual void removeRecord(const std::string &model_name, const QFile &file_to_remove);
 // virtual QList<QFile> listModelDir(const std::string &model_dir);
  //  virtual void readRecord(const std::string &model_name, const QFile file_to_read, QString dest_path)

protected:
  void checkFeatureFolder()const;
  //ConfigManager conf_;
  QDir feature_folder_;
};

#endif // MODELSDIRMANAGER_HPP
