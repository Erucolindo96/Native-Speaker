#ifndef MODELMANAGER_HPP
#define MODELMANAGER_HPP
#include"models/diagonal_model.hpp"
#include"dao/FileModelDao.hpp"
#include"configuration/ConfigManager.hpp"
#include<QObject>

/**
 * @brief The ModelManager class Odpowiada za zapisywanie i wczytywanie modeli z pliku
 * Pobiera ścieżkę do folderu z modelami z ConfigManagera.
 * Pozwala dodać i usunąć model z bazy
 */

class ModelManager: public QObject
{
  Q_OBJECT

protected:
  std::vector<std::unique_ptr<GmmModel>> models_;
  FileModelDao dao_;
  void saveModelToDatabase(const ConfigManager &config_m,
                           std::unique_ptr<GmmModel>& model_to_save);
  void loadModelsFromDatabase(const ConfigManager &config_m);

public:
  ModelManager() = default;
  ModelManager(const ModelManager &other) = default;
  ModelManager& operator=(const ModelManager &other) = default;
  ModelManager(ModelManager &&other) = default;
  ModelManager& operator=(ModelManager &&other) = default;

  void loadModels(const ConfigManager &config_m);
  void addModel(const ConfigManager &config_m,
                std::unique_ptr<GmmModel> &&model_to_add);

  uint32_t getModelsCnt()const;

  std::unique_ptr<GmmModel>& operator[](uint32_t index);


};

#endif // MODELMANAGER_HPP
