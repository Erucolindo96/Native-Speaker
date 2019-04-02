#ifndef FEATUREREADERSILENCECUTTER_HPP
#define FEATUREREADERSILENCECUTTER_HPP
#include "features/FeatureReader.hpp"
#include"exceptions/simple_exceptions.hpp"
class FeatureReaderSilenceCutter : public FeatureReader
{
public:

  const double MIN_ENERGY = -1;
  FeatureReaderSilenceCutter() = default;
  explicit FeatureReaderSilenceCutter(const std::string &feature_dir);
  FeatureReaderSilenceCutter(const FeatureReaderSilenceCutter &other) = default;
  FeatureReaderSilenceCutter& operator=(const FeatureReaderSilenceCutter &other) = default;
  FeatureReaderSilenceCutter(FeatureReaderSilenceCutter &&other) = default;
  FeatureReaderSilenceCutter& operator=(FeatureReaderSilenceCutter &&other) = default;

  std::vector<alize::Feature> readFile(const SPro4File &mfcc_file)const override;

  std::vector<alize::Feature> cutSilenceFeatures(const std::vector<alize::Feature> &f)const;

};

#endif // FEATUREREADERSILENCECUTTER_HPP
