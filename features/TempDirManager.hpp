#ifndef TEMPDIRMANAGER_HPP
#define TEMPDIRMANAGER_HPP
#include"record-base/RecordDirManager.hpp"
#include"features/TempDir.hpp"

class TempDirManager : protected RecordDirManager
{
public:
  const std::string TEMP_DIR_NAME = "@temp";

  TempDirManager()= default;
  TempDirManager(const TempDirManager &other) = default;
  TempDirManager& operator=(const TempDirManager &other) = default;
  TempDirManager(TempDirManager &&other) = default;
  TempDirManager& operator=(TempDirManager &&other) = default;


  /**
   * @brief setFeatureFolderPath Ustawia klasie folder wskazany jako folder bazy nagrań
   * @param dir Ustawiany folder
   * @throw DirNotFound Jesli taki folder nie istnieje w filesystemie
   */
  void setFeatureFolderPath(const QString &dir_path);

  /**
   * @brief getFeatureFolder Zwraca folder ustawiony jako folder bazy nagrań
   * @return Ścieżka do folderu bazy nagrań
   */
  QString getFeatureFolderPath()const;

  /**
   * @brief isDirExists Zwraca informację, czy folder danego modelu istnieje w bazie nagrań
   * @return True Jesli folder istnieje, w przeciwnym razie false
   * @throw FeatureFolderNotFound Jesli nie ustawiono folderu bazy nagrań
   */
  bool isDirExists()const;

  /**
   * @brief getTempDir Tworzy folder temp(jeśli go jeszze nie ma w bazie)
   * i zwraca klasę-uchwyt do utworzonego folderu
   * @return Uchwyt do utworzonego folderu temp
   * @throw FeatureFolderNotFound Jesli nie ustawiono folderu bazy nagrań
   */
  TempDir getTempDir();
  /**
   * @brief getTempDir Zwraca klasę-uchwyt do folderu temp.
   * Jesli folder nie istnieje, rzuca wyjątek DirNotFound.
   * @return Uchwyt do folderu temp
   * @throw DirNotFound Jeśli nie istnieje folder danego modelu
   * @throw FeatureFolderNotFound Jesli nie ustawiono folderu bazy nagrań
   */
  TempDir getTempDir()const;


};

#endif // TEMPDIRMANAGER_HPP
