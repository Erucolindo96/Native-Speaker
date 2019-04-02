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
class TempDir : public RecordDir
{
public:
  TempDir(const TempDir &other) = default;
  TempDir& operator=(const TempDir &other) = default;
  TempDir(TempDir &&other) = default;
  TempDir& operator=(TempDir &&other) = default;

  void setFeatureReader(std::unique_ptr<FeatureReader> &&reader);

  std::vector<alize::Feature> convertToMfcc(const Record &rec_to_convert);


protected:
  TempDir() = default;
  std::unique_ptr<FeatureReader> f_reader_;



};

#endif // TEMPDIR_HPP
