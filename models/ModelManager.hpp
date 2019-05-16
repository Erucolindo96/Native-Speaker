#ifndef MODELMANAGER_HPP
#define MODELMANAGER_HPP
#include"models/diagonal_model.hpp"
#include"dao/FileModelDao.hpp"
#include"configuration/ConfigManager.hpp"
#include<QObject>
#include<algorithm>
#include<map>

/**
 * @brief The ModelManager class Odpowiada za zapisywanie i wczytywanie modeli z pliku
 * Pobiera ścieżkę do folderu z modelami z ConfigManagera.
 * Pozwala dodać i usunąć model z bazy
 */

class ModelManager: public QObject
{
  Q_OBJECT

protected:
  //std::vector<std::shared_ptr<GmmModel>> models_;
  std::map<std::string, std::shared_ptr<GmmModel>> models_;
  FileModelDao dao_;
  void saveModelToDatabase(const ConfigManager &config_m,
                           std::shared_ptr<GmmModel> model_to_save);
  void loadModelsFromDatabase(const ConfigManager &config_m);

public:
  ModelManager() = default;
  ModelManager(const ModelManager &other) = default;
  ModelManager& operator=(const ModelManager &other) = default;
  ModelManager(ModelManager &&other) = default;
  ModelManager& operator=(ModelManager &&other) = default;
  virtual ~ModelManager() = default;

  void loadModels(const ConfigManager &config_m);
  void addModel(const ConfigManager &config_m,
                std::unique_ptr<GmmModel> &&model_to_add);

  uint32_t getModelsCnt()const;

  std::shared_ptr<GmmModel> operator[](uint32_t index);

  /**
   * @brief operator [] Wyszukuje wskaźnik do modelu po jego nazwie
   * @param model_name Nazwa modelu, o którego wskaźnik pytamy
   * @return Wskaźnik do modelu o danej nazwie
   * @throw std::out_of_range jesli nie ma modelu o danej nazwie
   */
  std::shared_ptr<GmmModel> operator[](const std::string &model_name);

  /**
   * @brief getModelsNames Zwraca wektor wszystkich nazw modeli, zawartych w managerze
   * @return Wektor wszystkich nazw modeli, zawartych w managerze
   */
  std::vector<std::string> getModelsNames()const;


};

#endif // MODELMANAGER_HPP
