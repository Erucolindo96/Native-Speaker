#ifndef TEMPDIR_HPP
#define TEMPDIR_HPP

#include"record-base/RecordDir.hpp"
#include"features/FeatureReader.hpp"
/**
 * @brief The TempDir class Klasa reprezentująca folder, w którym przeprowadzana będzie konwersja nagrania do postaci wektorów cech.
 * Odpowiedzialna jest za przeprowadzenie konwersji nagrania do postaci MFCC.
 * Najpierw kopiuje nagranie do siebie, następnie pobiera odpowiedniego Convertera i za jego pomocą konwertuje nagranie.
 * Następnie nakazuje FeatureReaderowi wczytanie wektorów cech do pamięci.
 * @see FeatureReader
 * @see MfccConverter
 * @see Record
 */
class TempDir : protected RecordDir
{
public:
  TempDir(const TempDir &other) = default;
  TempDir& operator=(const TempDir &other) = default;
  TempDir(TempDir &&other) = default;
  TempDir& operator=(TempDir &&other) = default;
  ~TempDir() override = default;

  /**
   * @brief setFeatureReader Ustawia instancję klasy FeatureReader, która ma wczytać do pamięci przekonwerowane wektory cech
   * Jeżeli nie zostanie ustawiona - do konwersji zostanie używa klasa bazowa, FeatureReader
   * @param reader Instancja klasy FeatureReader, która ma być użyta do wczytania wektorów cech do pamięci programu
   * @throw DirNotFound jeśli nie istnieje folder reprezentowany przez klasę
   */
  void setFeatureReader(std::unique_ptr<FeatureReader> &&reader);
  /**
   * @brief getFeatureReaderRef Zwraca referencje do obiektu ustawionego jako FeatureReader
   * @return Const referencja do obiektu ustawionego jako FeatureReader
   * @throw DirNotFound jeśli nie istnieje folder reprezentowany przez klasę
   */
  const std::unique_ptr<FeatureReader>& getFeatureReaderRef()const;

  /**
   * @brief convertToMfcc Konwertuje wskazane nagranie i wczytuje uzyskane w wyniku konwersji wektory cech
   * @param rec_to_convert Konwertowane nagranie
   * @return  Wektory cech uzyskane z danego nagrania
   * @throw FileNotFound Jeśli plik wskazywany przez rec_to_convert nie istenieje
   * @throw UnableToConvertToMfcc Jesli nie jesteśmy w stanie przekonwertować danego pliku
   * @throw DirNotFound jeśli nie istnieje folder reprezentowany przez klasę
   */
  std::vector<alize::Feature> convertToMfcc(const Record &rec_to_convert,
                                            uint32_t f_vec_size);

  /**
   * @brief cleanDir Usuwa wszystkie pliki znajdujące się w folderze
   * @throw DirNotFound jeśli nie istnieje folder reprezentowany przez klasę
   */
  void cleanDir();

  /**
   * @brief exists Zwraca informację, czy folder którego reprezentuje klasa istnieje
   * @return True jeśli istnieje, false jesli nie istnieje
   */
  bool exists()const;



protected:
  TempDir() = default;
  std::unique_ptr<FeatureReader> f_reader_;

  friend class TempDirManager;

};

#endif // TEMPDIR_HPP
