#ifndef FEATUREREADER_HPP
#define FEATUREREADER_HPP
#include<alize.h>
#include<string>
#include<memory>
#include<vector>
#include"exceptions/simple_exceptions.hpp"



/**
 *
 * Klasa czytająca plik w formacie SPRO4 i tworząca na jego podstawie wektor cech
 *
 */
class FeatureReader
{

protected:
  std::string dir_;
  alize::Config createConfig(const std::string & file_ext)const;

public:
  FeatureReader() = default;
  explicit FeatureReader(const std::string &feature_dir);
  FeatureReader(const FeatureReader &other) = default;
  FeatureReader& operator=(const FeatureReader &other) = default;
  FeatureReader(FeatureReader &&other) = default;
  FeatureReader& operator=(FeatureReader &&other) = default;

  std::string getFeatureDir()const;
  void setFeatureDir(const std::string &dir);

  virtual std::vector<alize::Feature> readFile(const std::string &file_name,
                                               const std::string &extention)const;
  virtual double getSampleRate(const std::string &file_name,
                               const std::string &extention)const;


};
#endif // FEATUREREADER_HPP
