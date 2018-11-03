﻿#ifndef LEARNING_ALGO_HPP
#define LEARNING_ALGO_HPP

#include<vector>
#include<alize/alize.h>
#include"models/gmmmodel.hpp"
#include"utils/utils.hpp"

using namespace std;


class GmmModel;
class LearningAlgo {


public:
  LearningAlgo() = default;
  LearningAlgo(const LearningAlgo &other) = delete;
  LearningAlgo(LearningAlgo &&other) = delete;
  LearningAlgo& operator =(const LearningAlgo &other) = delete;
  LearningAlgo& operator =(LearningAlgo &&other) = delete;
  virtual void learnModel(GmmModel &model, const std::vector<alize::Feature> &feature_vec) = 0;
  virtual ~LearningAlgo() = default;
};

class ExpectationMaximalizationAlgo: public LearningAlgo{
protected:
  std::vector<std::vector<double> > aposteriori_propabilities_;
  const uint32_t LEARNING_ITERATION_CNT = 32;
  inline double getPosterioriPropability(uint32_t feature_idx, uint32_t distrib_idx)const;
  inline void setPosterioriPropability(uint32_t feature_idx, uint32_t distrib_idx, double val);
  inline uint32_t getFeatureCount()const;
  inline uint32_t getDistribCount()const;
  double sumPosterioriByFeatures(uint32_t distrib_idx)const;

  void clearAfterIteration();
  void countPosterioriPropabilities(const GmmModel &model,
                                  const std::vector<alize::Feature> &feature_vec);
  double countOnePropability(const GmmModel &model,
                           const std::vector<alize::Feature> &feature_vec,
                           uint32_t feature_idx, uint32_t distrib_idx);

  double countWeight(uint32_t distrib_idx)const;
  alize::RealVector<double> countMean(uint32_t distrib_idx,
                              const std::vector<alize::Feature> &feature_vec )const;
  alize::RealVector<double> countDiagonalCovariance(uint32_t distrib_idx,
                                            const std::vector<alize::Feature> &feature_vec,
                                            const alize::RealVector<double> &mean)const;
  alize::DoubleSquareMatrix countFullCovariance(uint32_t distrib_idx,
                                                const std::vector<alize::Feature> &feature_vec,
                                                const alize::RealVector<double> &mean)const;

public:
  ExpectationMaximalizationAlgo()=default;
  ExpectationMaximalizationAlgo(const ExpectationMaximalizationAlgo &other)=default;
  ExpectationMaximalizationAlgo& operator=(const ExpectationMaximalizationAlgo &other)=default;

  ExpectationMaximalizationAlgo(ExpectationMaximalizationAlgo &&other) = default;
  ExpectationMaximalizationAlgo& operator =(ExpectationMaximalizationAlgo &&other) = default;
  void performOneIteration(GmmModel &model, const std::vector<alize::Feature> &feature_vec );

  void learnModel(GmmModel &model, const std::vector<alize::Feature> &feature_vec ) override;

  ~ExpectationMaximalizationAlgo()override = default;

};

#endif // LEARNING_ALGO_HPP

