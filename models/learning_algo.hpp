#ifndef LEARNING_ALGO_HPP
#define LEARNING_ALGO_HPP

#include<vector>
#include<alize/alize.h>
#include"models/gmmmodel.hpp"
#include"utils/utils.hpp"
#include <stdexcept>
#include<cfloat>
#include"exceptions/simple_exceptions.hpp"
using namespace std;

class GmmModel;

enum AlgoType
{
  EM_ALGO,
  MAX_POSTERIORI_ALGO
};


class LearningAlgo {

public:
  LearningAlgo() = default;
  LearningAlgo(const LearningAlgo &other) = delete;
  LearningAlgo(LearningAlgo &&other) = delete;
  LearningAlgo& operator =(const LearningAlgo &other) = delete;
  LearningAlgo& operator =(LearningAlgo &&other) = delete;
  virtual void learnModel(GmmModel &model, const std::vector<alize::Feature> &feature_vec, const uint32_t iterations) = 0;
  virtual ~LearningAlgo() = default;

//  static std::string getAlgoName()
};

class ExpectationMaximalizationAlgo: public LearningAlgo{
protected:
  std::vector<std::vector<double> > aposteriori_propabilities_;
  double posteriori_sum_;
  std::vector<double> sum_posteriori_by_features_;

  inline double getPosterioriPropability(uint32_t feature_idx, uint32_t distrib_idx)const;
  inline void setPosterioriPropability(uint32_t feature_idx, uint32_t distrib_idx, double val);
  inline uint32_t getFeatureCount()const;
  inline uint32_t getDistribCount()const;
  inline double avoidZeroDivide(double dividor)const;
  inline void avoidZeroInCovariance(alize::RealVector<double> &cov)const;



  double sumPosterioriByFeatures(uint32_t distrib_idx, uint32_t feature_cnt)const;
  //double sumPosterioriMatrix()const;
  void countPosterioriSum(uint32_t distrib_cnt, uint32_t feature_cnt);

  void initializePropabilities(uint32_t feature_cnt, uint32_t distrib_cnt);
  void initializePosterioriSum(uint32_t distrib_cnt);

  void clearAfterIteration();

  inline double countOnePropability(const GmmModel &model,
                           const std::vector<alize::Feature> &feature_vec,
                           uint32_t feature_idx, uint32_t distrib_idx,
                           double current_f_lk);


  inline double countWeight(uint32_t distrib_idx)const;
  inline alize::RealVector<double> countMean(uint32_t distrib_idx,
                              const std::vector<alize::Feature> &feature_vec )const;
  inline alize::RealVector<double> countDiagonalCovariance(uint32_t distrib_idx,
                                            const std::vector<alize::Feature> &feature_vec,
                                            const alize::RealVector<double> &mean)const;
  inline alize::DoubleSquareMatrix countFullCovariance(uint32_t distrib_idx,
                                                const std::vector<alize::Feature> &feature_vec,
                                                const alize::RealVector<double> &new_mean)const;

  void expectationStep(const GmmModel &model,
                                  const std::vector<alize::Feature> &feature_vec);
  void maximizationStep(GmmModel &model, const std::vector<alize::Feature> &feature_vec);
  void performOneIteration(GmmModel &model, const std::vector<alize::Feature> &feature_vec );


public:
  ExpectationMaximalizationAlgo()=default;
  ExpectationMaximalizationAlgo(const ExpectationMaximalizationAlgo &other)=default;
  ExpectationMaximalizationAlgo& operator=(const ExpectationMaximalizationAlgo &other)=default;

  ExpectationMaximalizationAlgo(ExpectationMaximalizationAlgo &&other) = default;
  ExpectationMaximalizationAlgo& operator =(ExpectationMaximalizationAlgo &&other) = default;

  void learnModel(GmmModel &model, const std::vector<alize::Feature> &feature_vec, const uint32_t iterations ) override;

  ~ExpectationMaximalizationAlgo()override = default;

};



#endif // LEARNING_ALGO_HPP

