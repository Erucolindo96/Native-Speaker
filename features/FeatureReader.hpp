#ifndef FEATUREREADER_HPP
#define FEATUREREADER_HPP
#include<alize.h>
#include<string>
#include<memory>
#include<vector>



/**
 *
 * Klasa czytająca plik w formacie SPRO4 i tworząca na jego podstawie wektor cech
 *
 */
class FeatureReader
{
public:
  FeatureReader();
  FeatureReader(const std::string &feature_dir = "");
  FeatureReader(const FeatureReader &other);
  FeatureReader& operator=(const FeatureReader &other);
  FeatureReader(FeatureReader &&other);
  FeatureReader& operator=(FeatureReader &&other);

  std::string getFeatureDir()const;
  void setFeatureDir(const std::string &dir);

//  uint32_t getFeatureSize()const;
//  void setFeatureCount()const;

  virtual std::vector<alize::Feature> readFile(const std::string &file_name,
                                               const std::string &extention)const = 0;
  virtual double getSampleRate(const std::string &file_name,
                               const std::string &extention)const = 0;


};

class FeatureReaderLinux: public FeatureReader
{
public:
  FeatureReaderLinux();
  FeatureReaderLinux(const std::string &feature_dir);
  FeatureReaderLinux(const FeatureReaderLinux &other);
  FeatureReaderLinux& operator=(const FeatureReaderLinux &other);
  FeatureReaderLinux(FeatureReaderLinux &&other);
  FeatureReaderLinux& operator=(FeatureReaderLinux &&other);


  std::vector<alize::Feature> readFile(const std::string &file_name,
                                       const std::string &extention)const override;
  double getSampleRate(const std::string &file_name,
                       const std::string &extention)const override;


};

#endif // FEATUREREADER_HPP
