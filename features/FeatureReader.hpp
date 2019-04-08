#ifndef FEATUREREADER_HPP
#define FEATUREREADER_HPP
#include<alize.h>
#include<string>
#include<memory>
#include<vector>
#include"exceptions/simple_exceptions.hpp"
#include"features/SPro4File.hpp"


/**
 *
 * Klasa czytająca plik w formacie SPRO4 i tworząca na jego podstawie wektory cech
 *
 */
class FeatureReader
{

protected:
  alize::Config createConfig(const SPro4File &mfcc_file)const;

public:
  FeatureReader() = default;
  FeatureReader(const FeatureReader &other) = default;
  FeatureReader& operator=(const FeatureReader &other) = default;
  FeatureReader(FeatureReader &&other) = default;
  FeatureReader& operator=(FeatureReader &&other) = default;
  virtual ~FeatureReader() = default;
  /**
   * @brief readFile Wczytuje wektory cech, zapisane w pliku podanym jako parametr
   * @param mfcc_file plik w formacie SPro4, z którego wczytywane są wektory cech
   * @return Wektor wektorów cech, pochodzących z danego pliku
   * @throw FileNotFound jeśli plik reprezentowany przez mfcc_file nie istnieje
   * @throw NotASProFile jeśli plik nie jest plikiem w formacie SPro4
   */
  virtual std::vector<alize::Feature> readFile(const SPro4File &mfcc_file)const;
  /**
   * @brief getSampleRate Zwraca ile wektorów cech na sekundę zawierało nagranie, z którego pochodzi plik z wektorami cech
   * @param mfcc_file Plik zawierający wektory cech
   * @return Ilość wektorów cech na sekundę w pierwotnym nagraniu
   * @throw FileNotFound jeśli plik reprezentowany przez mfcc_file nie istnieje
   * @throw NotASProFile jeśli plik nie jest plikiem w formacie SPro4
   *
   */
  virtual double getSampleRate(const SPro4File &mfcc_file)const;


};
#endif // FEATUREREADER_HPP
