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



double ExpectationMaximalizationAlgo::sumPosterioriByFeatures(uint32_t distrib_idx)const
{
  double sum = 0;
  for(uint32_t feature = 0; feature < getFeatureCount(); ++feature)
  {
    sum += getPosterioriPropability(feature, distrib_idx);
  }
  return sum;
}

double ExpectationMaximalizationAlgo::sumPosterioriMatrix()const
{
  double sum = 0;
  for(uint32_t distrib = 0; distrib < getDistribCount(); ++distrib)
  {
    sum += sumPosterioriByFeatures(distrib);
  }
  return sum;
}

void ExpectationMaximalizationAlgo::initializePropabilities
               (uint32_t feature_cnt, uint32_t distrib_cnt)
{
  aposteriori_propabilities_.clear();
  aposteriori_propabilities_.insert(aposteriori_propabilities_.begin(), feature_cnt, std::vector<double>(distrib_cnt));

}

void ExpectationMaximalizationAlgo::clearAfterIteration()
{

}

void ExpectationMaximalizationAlgo::countPosterioriPropabilities(const GmmModel &model,
                                                                 const vector<Feature> &feature_vec)
{
  double val = 0;
  for(uint32_t i_f = 0;i_f < feature_vec.size(); ++i_f)
  {
    for(uint32_t i_d = 0; i_d < model.getDistribCount(); ++i_d )
    {
      val = countOnePropability(model, feature_vec, i_f, i_d);
      setPosterioriPropability(i_f, i_d, val);
    }
  }
}



double ExpectationMaximalizationAlgo::countOnePropability(const GmmModel &model,
                                                        const std::vector<alize::Feature> &feature_vec,
                                                        uint32_t feature_idx, uint32_t distrib_idx)
{
  const Feature& current = feature_vec[feature_idx];
  double ret = 0;//model.getDistribWeight(distrib_idx);
  ret = model.countLikehoodWithWeight(current, distrib_idx);
  ret /= model.countLikehoodWithWeight(current);
  return ret;
}

void ExpectationMaximalizationAlgo::performOneIteration(GmmModel &model,
                                                        const std::vector<alize::Feature> &feature_vec)
{
  countPosterioriPropabilities(model, feature_vec);//expectation step
  const uint32_t DISTRIB_CNT = getDistribCount();
  double weight = 0;
  RealVector<double> mean(getFeatureCount());
  RealVector<double> covariance(getFeatureCount());
  for(uint32_t act_distrib = 0; act_distrib < DISTRIB_CNT; ++act_distrib)//maximization step
  {
    weight = countWeight(act_distrib);
    mean = countMean(act_distrib, feature_vec);
    covariance = countDiagonalCovariance(act_distrib, feature_vec,
                                         mean);
    model.setDistribWeight(act_distrib, weight);
    model.setDistribMean(act_distrib,mean);
    model.setDistribCovariance(act_distrib, covariance);
  }
  clearAfterIteration();
}


double ExpectationMaximalizationAlgo::countWeight(uint32_t distrib_idx)const
{
  double new_weight = sumPosterioriByFeatures(distrib_idx);
  new_weight /= sumPosterioriMatrix();
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
  for(uint32_t f_idx = 0; f_idx < getFeatureCount(); ++f_idx)
  {
    const Feature& actual = feature_vec[f_idx];
    posteriori = getPosterioriPropability(f_idx, distrib_idx);
    temp = utils::toRealVector(actual);
    temp *= posteriori;
    new_mean += temp;
  }

  //dzielimy sume przez sume p-stw posteriori po wektorach cech
  double sum_posteriori = sumPosterioriByFeatures(distrib_idx);
  if(isinf(1/sum_posteriori))//zapobieżenie dzielenia przez zero
    sum_posteriori = FLT_EPSILON;
  new_mean *= 1/sum_posteriori;
  return new_mean;

}
RealVector<double> ExpectationMaximalizationAlgo::countDiagonalCovariance(uint32_t distrib_idx,
                                                                  const vector<Feature> &feature_vec,
                                                                  const RealVector<double> &mean)const
{
  const uint32_t FEATURE_CNT = getFeatureCount(),
      FEATURE_SIZE = feature_vec[0].getVectSize();
  double act_posteriori = 0;
  RealVector<double> diff(FEATURE_SIZE, FEATURE_SIZE), ret(FEATURE_SIZE, FEATURE_SIZE);
  //suma różnicy wektora cech i wektora średniego, pomnożona przez p-stwo posteriori
  for(uint32_t act_feature = 0; act_feature < FEATURE_CNT; ++act_feature)
  {
    act_posteriori = getPosterioriPropability(act_feature, distrib_idx);

    diff = utils::toRealVector(feature_vec[act_feature]);
    diff -= mean;
    diff *= act_posteriori;
    ret += diff;
  }
  //teraz dzielimy całość przez sume p-stw posteriori
  ret *= 1/sumPosterioriByFeatures(distrib_idx);
  return ret;
}
DoubleSquareMatrix ExpectationMaximalizationAlgo::countFullCovariance(uint32_t distrib_idx,
                                                                      const vector<Feature> &feature_vec,
                                                                      const RealVector<double> &mean)const
{
  throw std::runtime_error("TODO");
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
    throw LearningModelWithoutFeaturesException(__FILE__ + std::string(", line: ") + std::to_string(__LINE__)
                                                + std::string(" - try to learn model empty feature vector"));
  }

  initializePropabilities(feature_vec.size(), model.getDistribCount());
  for(uint32_t i=0; i< iterations; ++i)
  {
    performOneIteration(model, feature_vec);
  }

}

