#ifndef GMMMODEL_HPP
#define GMMMODEL_HPP

#include <alize/alize.h>
#include<memory>
#include <stdexcept>
#include <vector>
#include "models/learning_algo.hpp"

class IndexOutOfBounds : std::out_of_range
{
public:
  explicit IndexOutOfBounds(std::string msg) : out_of_range(msg)
  {}
};

class InvalidFeatureVectorSize: std::invalid_argument
{
public :
  explicit InvalidFeatureVectorSize(std::string msg):invalid_argument(msg)
  {}
};

class GmmModel
{
public:

  const uint32_t  MIXTURE_IDX = 0, DISTRIB_CNT, FEATURE_SIZE,
  MAX_LLK = 100, MIN_LLK = -100;
  std::unique_ptr<alize::MixtureServer> s_;
  alize::DistribType type_;
  std::vector<alize::Feature> features_;

  virtual void initDefaultMixture(uint32_t distrib_cnt);

public:
  GmmModel() = delete;
  explicit GmmModel(uint32_t distrib_cnt, uint32_t feature_size);
  GmmModel(const GmmModel &other) = delete;
  GmmModel& operator=(const GmmModel &other) = delete;

  GmmModel(GmmModel &&other);
  GmmModel& operator =(GmmModel &&other) = delete;

  void addTrainingFeature(const alize::Feature &feature);
  std::vector<alize::Feature> getTrainingFeatures();

  double countLikehoodWithWeight(const alize::Feature &arg)const;
  double countLikehoodWithWeight(const alize::Feature &arg, uint32_t distrib_idx)const;

  uint32_t getDistribCount()const;
  double getDistribWeight(uint32_t distrib_idx)const;
  void setDistribWeight(uint32_t distrib, double new_weight);

  alize::RealVector<double> getDistribMean(uint32_t distrib)const;
  void setDistribMean(uint32_t distrib, const alize::RealVector<double> &new_mean);

  virtual void setDistribCovariance(uint32_t distrib, const alize::RealVector<double> &diagonal_covariance) = 0;
  virtual void setDistribCovariance(uint32_t distrib, const alize::DoubleMatrix &covariance) = 0;

  uint32_t getFeatureVectorSize()const;

  virtual ~GmmModel() = default;
  static std::vector<alize::Feature> extractAllFeatures(alize::FeatureServer &s);

};

#endif // GMMMODEL_HPP
