#ifndef MODELSDIRMANAGER_HPP
#define MODELSDIRMANAGER_HPP

#include<QDir>
#include<QFile>
#include<QList>
#include"configuration/ConfigManager.hpp"
#include"exceptions/simple_exceptions.hpp"
#include"record-base/RecordDir.hpp"
/**
 * @brief The RecordDirManager class Zarządza tworzeniem i usuwaniem folderów z nagraniami mówców
 * W tych folderach będą przechowywane nagrania, którymi uczono dane modele
 */
class RecordDirManager
{

public:
  RecordDirManager()=default;
  RecordDirManager(const RecordDirManager &other) = default;
  RecordDirManager& operator=(const RecordDirManager &other) = default;
  RecordDirManager(RecordDirManager &&other) = default;
  RecordDirManager& operator=(RecordDirManager &&other) = default;

  /**
   * @brief setFeatureFolder Ustawia klasie folder wskazany jako folder bazy nagrań
   * @param dir Ustawiany folder
   * @throw DirNotFound Jesli taki folder nie istnieje w filesystemie
   */
  void setFeatureFolder(const QString &dir_path);

  /**
   * @brief getFeatureFolder Zwraca folder ustawiony jako folder bazy nagrań
   * @return Ścieżka do folderu bazy nagrań
   */
  QString getFeatureFolder()const;

  /**
   * @brief isDirExists Zwraca informację, czy folder danego modelu istnieje w bazie nagrań
   * @param model_name Nazwa modelu, o którego folder pytamy
   * @return True Jesli folder istnieje, w przeciwnym razie false
   * @throw FeatureFolderNotFound Jesli nie ustawiono folderu bazy nagrań
   */
  bool isDirExists(const std::string &model_name)const;

  /**
   * @brief getModelDir Tworzy folder nagrań dla wskazanego w parametrze modelu(jeśli go jeszze nie ma w bazie)
   * i zwraca klasę-uchwyt do utworzonego folderu
   * @param model_name Model, którego folder chcemy utworzyć
   * @return Uchwyt do utworzonego folderu
   * @throw FeatureFolderNotFound Jesli nie ustawiono folderu bazy nagrań
   */
  RecordDir getModelDir(const std::string &model_name);

  /**
   * @brief removeModelDir Usuwa folder nagrań wskazanego w parametrze modelu(jeśli istnieje)
   * @param model_name Model, którego folder chcemy usunąć
   * @throw FeatureFolderNotFound Jesli nie ustawiono folderu bazy nagrań
   */
  void removeModelDir(const std::string &model_name);


  /**
   * @brief getAllDirs Zwraca uchwyty do wszystkich folderów utworzonych w bazie próbek
   * @return Uchwyty do folderów z nagraniami modeli, które istnieja aktualnie w bazie
   * @throw FeatureFolderNotFound Jeśli nie ustawiono folderu bazy nagrań
   */
  std::vector<RecordDir> getAllDirs()const;

protected:
  void checkFeatureFolder()const;
  QString feature_folder_path_;

};

#endif // MODELSDIRMANAGER_HPP
