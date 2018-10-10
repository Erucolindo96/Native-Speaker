#ifndef GMMMODEL_HPP
#define GMMMODEL_HPP

#include <alize/alize.h>
#include<memory>
#include <stdexcept>
#include <vector>
#include "models/learning_algo.hpp"
class LearningAlgo;

class GmmModel
{
protected:

  const uint32_t DISTRIB_COUNT, MIXTURE_IDX = 0;
  alize::Config conf_;
  alize::MixtureServer s_;
  std::unique_ptr<LearningAlgo> algo_;
  alize::DistribType type_;
  alize::FeatureServer features_;


  void reloadConfig();
  virtual void initDefaultMixture(uint32_t distrib_cnt);

public:
  GmmModel() = delete;
  explicit GmmModel(const alize::Config &conf, uint32_t distrib_cnt = 512);
  GmmModel(const GmmModel &other) = delete;
  GmmModel& operator=(const GmmModel &other) = delete;

  GmmModel(GmmModel &&other);
  GmmModel& operator =(GmmModel &&other) = delete;

  void setConfig(const alize::Config &conf);
  alize::Config getConfig()const;

  virtual void addLearnAlgo(std::unique_ptr<LearningAlgo> &&algo_to_set);
  virtual std::unique_ptr<LearningAlgo>& getLearnAlgo();
  virtual void learnModelUsingLearnAlgo(std::unique_ptr<LearningAlgo> &algo);
  void learnModel();

  void addTrainingFeature(const alize::Feature &feature);
  std::vector<alize::Feature> getTrainingFeatures();

  double countLikehoodWithWeight(const alize::Feature &arg)const;
  double countLikehoodWithWeight(const alize::Feature &arg, uint32_t distrib_idx)const;

  uint32_t getDistribCount()const;
  uint32_t getDistribWeight(uint32_t distrib_idx)const;
  void setDistribWeight(uint32_t distrib, double new_weight);

  alize::RealVector<double> getDistribMean(uint32_t distrib)const;
  void setDistribMean(uint32_t distrib, alize::RealVector<double> new_mean);

  virtual void setDistribCovariance(uint32_t distrib, const alize::RealVector<double> &diagonal_covariance) = 0;
  virtual void setDistribCovariance(uint32_t distrib, const alize::DoubleMatrix &covariance) = 0;



  virtual ~GmmModel() = default;
  static std::vector<alize::Feature> extractAllFeatures(alize::FeatureServer &s);

};

#endif // GMMMODEL_HPP
