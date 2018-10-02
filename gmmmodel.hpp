#ifndef GMMMODEL_HPP
#define GMMMODEL_HPP

#include <alize/alize.h>
#include<memory>
#include"learning_algo.hpp"
#include <stdexcept>


class GmmModel
{
protected:
  //friend class LearningAlgo;
  //friend class ExpectationMaximalizationAlgo;

  const uint32_t DISTRIB_COUNT = 512, MIXTURE_IDX = 0;
  alize::Config conf_;
  alize::MixtureServer s_;
  std::unique_ptr<LearningAlgo> algo_;
  alize::DistribType type_;
  alize::FeatureServer features_;


  void reloadConfig();
  void initDefaultMixture();

public:
  GmmModel() = delete;
  explicit GmmModel(const alize::Config &conf);
  GmmModel(const GmmModel &other) = delete;
  GmmModel& operator=(const GmmModel &other) = delete;

  GmmModel(GmmModel &&other);
  GmmModel& operator =(GmmModel &&other);

  void setConfig(const alize::Config &conf);
  alize::Config getConfig()const;

  virtual void addLearnAlgo(std::unique_ptr<LearningAlgo> &&algo_to_set);


  void addFeature(const alize::Feature &feature);

  void learnModel();
  double countLikehood(const alize::Feature &arg);

  virtual ~GmmModel() = default;
  static std::vector<alize::Feature> extractAllFeatures(alize::FeatureServer &s);

};

#endif // GMMMODEL_HPP
