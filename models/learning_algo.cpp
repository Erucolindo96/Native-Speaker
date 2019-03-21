#include "models/learning_algo.hpp"
using namespace alize;
using namespace std;


/*
 * Protected
 *
 */


double ExpectationMaximalizationAlgo::getPosterioriPropability(uint32_t feature_idx, uint32_t distrib_idx)const
{
  return aposteriori_propabilities_[feature_idx][distrib_idx];
}
void ExpectationMaximalizationAlgo::setPosterioriPropability(uint32_t feature_idx, uint32_t distrib_idx, double val)
{
  aposteriori_propabilities_[feature_idx][distrib_idx] = val;
}

uint32_t ExpectationMaximalizationAlgo::getFeatureCount()const
{
  return aposteriori_propabilities_.size();
}

uint32_t ExpectationMaximalizationAlgo::getDistribCount()const
{
  const uint32_t FIRST_FEATURE_ROW = 0;
  return aposteriori_propabilities_[FIRST_FEATURE_ROW].size();
}

double ExpectationMaximalizationAlgo::avoidZeroDivide(double dividor)const
{
  if(isinf(1/dividor))//zapobieżenie dzielenia przez zero
    dividor = DBL_EPSILON;
  return dividor;
}

void ExpectationMaximalizationAlgo::avoidZeroInCovariance(alize::RealVector<double> &cov)const
{
  for(uint32_t i = 0; i< cov.size(); ++i)
  {
    if(cov[i] == 0.0)
    {
      cov[i] = DBL_EPSILON;
    }
  }
}




double ExpectationMaximalizationAlgo::sumPosterioriByFeatures(uint32_t distrib_idx, uint32_t feature_cnt)const
{
  double sum = 0;
  for(uint32_t feature = 0; feature < feature_cnt; ++feature)
  {
    sum += getPosterioriPropability(feature, distrib_idx);
  }
  return sum;
}
/*
double ExpectationMaximalizationAlgo::sumPosterioriMatrix()const
{
  double sum = 0;
  for(uint32_t distrib = 0; distrib < getDistribCount(); ++distrib)
  {
    sum += sumPosterioriByFeatures(distrib);
  }
  return sum;
}
*/
void ExpectationMaximalizationAlgo::countPosterioriSum(uint32_t distrib_cnt, uint32_t feature_cnt)
{
  posteriori_sum_ = 0;
  for(uint32_t i = 0; i < distrib_cnt; ++i)
  {
    sum_posteriori_by_features_[i] = sumPosterioriByFeatures(i, feature_cnt);
    posteriori_sum_ += sum_posteriori_by_features_[i];
  }
}

void ExpectationMaximalizationAlgo::initializePropabilities
               (uint32_t feature_cnt, uint32_t distrib_cnt)
{
  aposteriori_propabilities_.clear();
  aposteriori_propabilities_.insert(aposteriori_propabilities_.begin(), feature_cnt, std::vector<double>(distrib_cnt));

}

void ExpectationMaximalizationAlgo::initializePosterioriSum(uint32_t distrib_cnt)
{
  if(sum_posteriori_by_features_.size() != distrib_cnt)
  {
    sum_posteriori_by_features_.resize(distrib_cnt);
  }
}

void ExpectationMaximalizationAlgo::clearAfterIteration()
{

}



double ExpectationMaximalizationAlgo::countOnePropability(const GmmModel &model,
                                                        const std::vector<alize::Feature> &feature_vec,
                                                        uint32_t feature_idx, uint32_t distrib_idx,
                                                          double current_f_lk)
{
  const Feature& current = feature_vec[feature_idx];
  double ret = 0;
  ret = model.countLikehoodWithWeight(current, distrib_idx);
  ret /= current_f_lk;
  return ret;
}



double ExpectationMaximalizationAlgo::countWeight(uint32_t distrib_idx)const
{
  double new_weight = sum_posteriori_by_features_[distrib_idx];

  new_weight /= avoidZeroDivide(posteriori_sum_);
  return new_weight;
}

RealVector<double> ExpectationMaximalizationAlgo::countMean(uint32_t distrib_idx,
                                                    const vector<Feature> &feature_vec )const
{

  const uint32_t FEATURE_SIZE = feature_vec[0].getVectSize(), FEATURE_CNT = getFeatureCount();
  RealVector<double> new_mean(FEATURE_SIZE, FEATURE_SIZE),
      temp(FEATURE_SIZE, FEATURE_SIZE);
  //suma iloczynów prawdopodobieństw posteriori i wektorów cech
  new_mean.setAllValues(0.0);
  temp.setAllValues(0.0);
  double posteriori = 0;
  for(uint32_t f_idx = 0; f_idx < FEATURE_CNT; ++f_idx)
  {
    const Feature& actual = feature_vec[f_idx];
    posteriori = getPosterioriPropability(f_idx, distrib_idx);
    temp = utils::toRealVector(actual);
    temp *= posteriori;
    new_mean += temp;
  }

  //dzielimy sume przez sume p-stw posteriori po wektorach cech

  new_mean *= 1/avoidZeroDivide(sum_posteriori_by_features_[distrib_idx]);
  return new_mean;

}
RealVector<double> ExpectationMaximalizationAlgo::countDiagonalCovariance(uint32_t distrib_idx,
                                                                  const vector<Feature> &feature_vec,
                                                                  const RealVector<double> &new_mean)const
{
  const uint32_t FEATURE_CNT = getFeatureCount(),
      FEATURE_SIZE = feature_vec[0].getVectSize();
  RealVector<double> ret(FEATURE_SIZE, FEATURE_SIZE)
      ,diff(FEATURE_SIZE, FEATURE_SIZE);
  ret.setAllValues(0.0);

  unique_ptr<Matrix<double>> f_and_mean_diff, f_and_mean_transpoze;
  Matrix<double> temp(FEATURE_SIZE, FEATURE_SIZE);
  double act_posteriori = 0;
  //obliczanie sumy iloczynów macierzy (f_j - u_i)*(f_j - u_i)^T * posteriori(j,i)
  for(uint32_t act_f = 0; act_f < FEATURE_CNT; ++act_f)
  {
    diff = utils::toRealVector(feature_vec[act_f]);
    diff -= new_mean;
    act_posteriori = getPosterioriPropability(act_f, distrib_idx);
    f_and_mean_transpoze = make_unique<Matrix<double>>(diff);
    f_and_mean_diff  = make_unique<Matrix<double>>(diff);
    f_and_mean_diff->transpose();
    /*ponieważ w ALIZE wektor jest interpretowany jako wektor wierszowy, nie kolumnowy
    to musimy transponować różnicę, a nie jej transpozycję*/
    temp = (*f_and_mean_diff) * (*f_and_mean_transpoze);//opertory *, bo to wskaźniki
    temp*= act_posteriori;
    ret += utils::diag(temp);
  }
  avoidZeroInCovariance(ret);

  ret *= 1/avoidZeroDivide(sum_posteriori_by_features_[distrib_idx]);
  return ret;
}
DoubleSquareMatrix ExpectationMaximalizationAlgo::countFullCovariance(uint32_t distrib_idx,
                                                                      const vector<Feature> &feature_vec,
                                                                      const RealVector<double> &mean)const
{
  throw std::runtime_error("TODO");
}


void ExpectationMaximalizationAlgo::expectationStep(const GmmModel &model,
                                                                 const vector<Feature> &feature_vec)
{
  double val = 0, curr_f_lk = 0;
  uint32_t DISTRIB_CNT = model.getDistribCount(),
      FEATURE_CNT = feature_vec.size();

  for(uint32_t i_f = 0;i_f < FEATURE_CNT; ++i_f)
  {
    curr_f_lk = model.countLikehoodWithWeight(feature_vec[i_f]);
    for(uint32_t i_d = 0; i_d < DISTRIB_CNT; ++i_d )
    {
      val = countOnePropability(model, feature_vec, i_f, i_d, curr_f_lk);
      setPosterioriPropability(i_f, i_d, val);
    }
  }


}

void ExpectationMaximalizationAlgo::maximizationStep(GmmModel &model, const std::vector<alize::Feature> &feature_vec)
{


  const uint32_t DISTRIB_CNT = getDistribCount(), FEATURE_CNT = getFeatureCount();
  countPosterioriSum(DISTRIB_CNT, FEATURE_CNT);//obliczenie sum posteriori - by nie liczyć ich za każdym razem

  RealVector<double> prev_mean(FEATURE_CNT);
  for(uint32_t act_d = 0; act_d < DISTRIB_CNT; ++act_d)
  {

    prev_mean = model.getDistribMean(act_d);

    model.setDistribWeight(act_d, countWeight(act_d));
    model.setDistribMean(act_d,countMean(act_d, feature_vec));
    model.setDistribCovariance(act_d, countDiagonalCovariance(act_d, feature_vec,
                                                              prev_mean));

  }
}


void ExpectationMaximalizationAlgo::performOneIteration(GmmModel &model,
                                                        const std::vector<alize::Feature> &feature_vec)
{
  expectationStep(model, feature_vec);
  maximizationStep(model, feature_vec);
  clearAfterIteration();
}

/*
 *Public
 *
 */
void ExpectationMaximalizationAlgo::learnModel(GmmModel &model,
                                               const std::vector<alize::Feature> &feature_vec,
                                               const uint32_t iterations)
{
  if(feature_vec.empty())
  {
    throw LearningModelWithoutFeatures(__FILE__ + std::string(", line: ") + std::to_string(__LINE__)
                                                + std::string(" - try to learn model empty feature vector"));
  }

  initializePropabilities(feature_vec.size(), model.getDistribCount());
  initializePosterioriSum(model.getDistribCount());
  for(uint32_t i=0; i< iterations; ++i)
  {
    performOneIteration(model, feature_vec);
  }

}



