#ifndef RECBASEMANAGER_HPP
#define RECBASEMANAGER_HPP
#include"record-base/RecordDirManager.hpp"

/**
 * @brief The RecBaseManager class Klasa służąca do realizowana dostępu do bazy próbek.
 * Udostępnia operacje dodawania nagrań do zasobów przypisanych do danego modelu,
 * oraz umożliwia uzyskanie przypisanych wcześniej nagrań.
 */
class RecBaseManager
{
public:
  RecBaseManager() = default;
  RecBaseManager(const RecBaseManager &other) = default;
  RecBaseManager& operator=(const RecBaseManager &other) = default;
  RecBaseManager(RecBaseManager &&other) = default;
  RecBaseManager& operator=(RecBaseManager &&other) = default;

  /**
   * @brief setFeatureFolderPath Ustawia ścieżkę do folderu bazy próbek
   * @param path Scieżka do folderu bazy próbek
   * @throw FeatureFolderNotFound Jesli folder o wskazanej ścieżce nie istnieje
   */
  void setFeatureFolderPath(const QString &path);
  /**
   * @brief getFeatureFolderPath Zwraca ścieżkę do folderu bazy próbek
   * @return Ustawiona uprzednio scieżka do folderu bazy próbek
   */
  QString getFeatureFolderPath()const;

  /**
   * @brief getRecordsOfModel Zwraca uchwyty do wszystkich nagrań przypisanych do danego modelu
   * @param model_name Model, którego dotyczy zapytanie
   * @return Wektor uchwytów do nagrań, przypisanych do danego modelu
   * @throw FeatureFolderNotFound Jeśli nie można znaleźć folderu bazy próbek na podstawe jego ścieżki
   */
  const std::vector<Record> getRecordsOfModel(const std::string &model_name)const;

  /**
   * @brief setRecordToBase Przypisuje dane nagranie do danego modelu.
   * Nagranie jest kopiowane do folderu, należącego do danego modelu.
   * @param r Kopiowane nagranie
   * @param model_name Nazwa modelu, którego dotyczy operacja
   * @throw FeatureFolderNotFound Jeśli nie można znaleźć folderu bazy próbek na podstawe jego ścieżki
   * @throw FileNotFound Jeśli nie można znaleźć pliku reprezentowanego przez kopiowane nagranie
   */
  void setRecordToBase(const Record &r, const std::string &model_name);

  /**
   * @brief isRecordExists Sprawdza, czy dane nagranie jest już przypisane do folderu danego mówcy.
   * Poszukiwany jest plik w folderze mówcy o takiej samej nazwie jak nagranie.
   * @param r Nagranie, które sprawdzamy, czy jest już zawarte w folderze danego modelu
   * @param model_name Model, którego dotyczy zapytanie
   * @return True jeśli nagranie jest już zawarte w folderze danego modelu
   * False w przeciwnym razie
   * @throw FeatureFolderNotFound Jeśli nie można znaleźć folderu bazy próbek na podstawe jego ścieżki
   * @throw FileNotFound Jeśli nie można znaleźć pliku reprezentowanego przez kopiowane nagranie
   */
  bool isRecordExists(const Record &r, const std::string &model_name)const;

protected:
  RecordDirManager dir_manager_;
};

#endif // RECBASEMANAGER_HPP
