#ifndef FEATUREMANAGER_HPP
#define FEATUREMANAGER_HPP
#include"features/TempDirManager.hpp"

class FeatureManager
{
public:
  FeatureManager()=default;
  FeatureManager(const FeatureManager &other)=default;
  FeatureManager& operator=(const FeatureManager &other)=default;
  FeatureManager(FeatureManager &&other)=default;
  FeatureManager& operator=(FeatureManager &&other)=default;


  std::vector<alize::Feature> convertRecord(const Record &r);
  std::vector<alize::Feature> convertRecordWithoutSilence(const Record &r);


};

#endif // FEATUREMANAGER_HPP
