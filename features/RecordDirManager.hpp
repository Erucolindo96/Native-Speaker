#ifndef MODELSDIRMANAGER_HPP
#define MODELSDIRMANAGER_HPP

#include<QDir>
#include"configuration/ConfigManager.hpp"
#include"exceptions/simple_exceptions.hpp"

/**
 * @brief The ModelsDirManager class Zarządza tworzeniem i usuwaniem folderów z nagraniami mówców
 * W tych folderach będą przechowywane nagrania, którymi uczono dane modele
 */
class RecordDirManager
{

public:
  RecordDirManager(ConfigManager conf = ConfigManager());
  RecordDirManager(const RecordDirManager &other) = default;
  RecordDirManager& operator=(const RecordDirManager &other) = default;
  RecordDirManager(RecordDirManager &&other) = default;
  RecordDirManager& operator=(RecordDirManager &&other) = default;

  void setConfig(const ConfigManager &conf);
  ConfigManager getConfig()const;

  virtual bool isDirExist(const std::string &model_name)const;
  virtual void createModelDir(const std::string &model_name);
  virtual void removeModelDir(const std::string &model_name);
  virtual void cleanModelDir(const std::string &model_name);


protected:
  void checkFeatureFolder()const;
  ConfigManager conf_;
};

#endif // MODELSDIRMANAGER_HPP
