#ifndef FEATUREMANAGER_HPP
#define FEATUREMANAGER_HPP
#include"features/TempDirManager.hpp"

/**
 * @brief The FeatureManager class Klasa, odpowiedzialna za obsługę przetwarzania nagrań do postaci wektorów cech MFCC
 * Zleca odpowiednim klasom przetworzenie wskazanych nagrań, oraz zleca oczyszczanie folderu tymczasowego z plików
 */
class FeatureManager
{
public:
  FeatureManager()=default;
  FeatureManager(const FeatureManager &other)=default;
  FeatureManager& operator=(const FeatureManager &other)=default;
  FeatureManager(FeatureManager &&other)=default;
  FeatureManager& operator=(FeatureManager &&other)=default;
  virtual ~FeatureManager() = default;

  /**
   * @brief setFeatureFolderPath Ustawia ścieżkę do folderu z bazą nagrań
   * @param path Scieżka do folderu z bazą nagrań
   * @throw FeatureFolderNotFound jeżeli wskazana ścieżka nie prowadzi do żadnego folderu
   */
  void setFeatureFolder(const QString &path);
  /**
   * @brief getFeatureFolderPath Zwraca ustawiona uprzednio ścieżkę do folderu bazy nagrań
   * @return Ścieżka do folderu bazy nagrań
   */
  QString getFeatureFolder()const;

  /**
   * @brief convertRecord Przetwarza plik z nagraniem, reprezentowany przez r, na wektory cech MFCC.
   * Wczytywanie do pamięci odbywa się za pomocą wskazanego FeatureReadera.
   * Dzięki temu można manipulować sposobem wczytywania cech do pamięci
   * @param r Nagranie dźwięku, które chcemy przetworzyć do postaci wektorów cech MFCC
   * @param reader Klasa wczytującą wektory cech do pamięci programu.
   * Jeżeli jest nullptrem, to zostanie użyty domyslny FeatureReader, który po prostu wczytuje wszystkie utworzone wektory cech do pamięci.
   * @param f_vec_size Długośc wynikowego wektora cech. Logarytm energii równiez jest wliczany w długość wektora
   * @return Wektory cech, utworzone w wyniku konwersji wskazanego nagrania
   * @throw FeatureFolderNotFound jeżeli nie ustawiono ścieżki do folderu bazy nagrań
   * @throw UnableToConvertToMfcc jeżeli nie ma odpowiedniego konwertera, by przetwarzać wskazane nagranie
   * @throw FileNotFound jeżeli plik reprezentowany przez r nie istnieje
   */
  std::vector<alize::Feature> convertRecord(const Record &r,
                                            uint32_t f_vec_size,
                                            std::unique_ptr<FeatureReader>&& reader = nullptr);
  /**
   * @brief convertRecord Przetwarza pliki z nagraniami, zawartymi w r_vec, na wektory cech MFCC.
   * Wczytywanie do pamięci odbywa się za pomocą wskazanego FeatureReadera.
   * Dzięki temu można manipulować sposobem wczytywania cech do pamięci
   * @param r_vec Wektor nagrań do przetworzenia
   * @param reader Klasa wczytującą wektory cech do pamięci programu.
   * Jeżeli jest nullptrem, to zostanie użyty domyslny FeatureReader, który po prostu wczytuje wszystkie utworzone wektory cech do pamięci.
   * @param f_vec_size Długośc wynikowego wektora cech. Logarytm energii równiez jest wliczany w długość wektora
   * @return Wektory cech, utworzone w wyniku konwersji wskazanego nagrania
   * @throw FeatureFolderNotFound jeżeli nie ustawiono ścieżki do folderu bazy nagrań
   * @throw UnableToConvertToMfcc jeżeli nie ma odpowiedniego konwertera, by przetwarzać wskazane nagranie
   * @throw FileNotFound jeżeli plik reprezentowany przez r nie istnieje
   */
  std::vector<alize::Feature> convertRecord(const std::vector<Record> &r_vec,
                                            uint32_t f_vec_size,
                                            std::unique_ptr<FeatureReader>&& reader = nullptr);
  /**
   * @brief clean Usuwa tworzone przez klasę pliki tymczasowe
   * @throw FeatureFolderNotFound jeżeli nie ustawiono ścieżki do folderu bazy nagrań
   *
   */
  void clean();

protected:
  TempDirManager temp_manager_;


};

#endif // FEATUREMANAGER_HPP
