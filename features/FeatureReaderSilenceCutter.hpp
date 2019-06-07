#ifndef FEATUREREADERSILENCECUTTER_HPP
#define FEATUREREADERSILENCECUTTER_HPP
#include "features/FeatureReader.hpp"
#include"exceptions/simple_exceptions.hpp"
class FeatureReaderSilenceCutter : public FeatureReader
{
public:

  const double MIN_ENERGY = 0;
  FeatureReaderSilenceCutter() = default;
  FeatureReaderSilenceCutter(const FeatureReaderSilenceCutter &other) = default;
  FeatureReaderSilenceCutter& operator=(const FeatureReaderSilenceCutter &other) = default;
  FeatureReaderSilenceCutter(FeatureReaderSilenceCutter &&other) = default;
  FeatureReaderSilenceCutter& operator=(FeatureReaderSilenceCutter &&other) = default;
  ~FeatureReaderSilenceCutter() override = default;

  std::vector<alize::Feature> readFile(const SPro4File &mfcc_file)const override;

  std::vector<alize::Feature> cutSilenceFeatures(const std::vector<alize::Feature> &f)const;

  uint32_t countIndexOfLogEnergy(uint32_t f_lenght, bool with_diff_vec)const;
};

#endif // FEATUREREADERSILENCECUTTER_HPP
