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
  const uint32_t FIRST_FEATURE = 0;
  return aposteriori_propabilities_[FIRST_FEATURE].size();
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

void ExpectationMaximalizationAlgo::performOneIteration(GmmModel &model, const std::vector<alize::Feature> &feature_vec)
{
  countPosterioriPropabilities(model, feature_vec);
  const uint32_t DISTRIB_CNT = getDistribCount();
  double weight = 0;
  RealVector<double> mean(getFeatureCount());
  RealVector<double> covariance(getFeatureCount());
  for(uint32_t act_distrib; act_distrib < DISTRIB_CNT; ++act_distrib)
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
  double ret = model.getDistribWeight(distrib_idx);
  ret *= model.countLikehoodWithWeight(current, distrib_idx);
  ret /= model.countLikehoodWithWeight(current);
  return ret;
}

double ExpectationMaximalizationAlgo::countWeight(uint32_t distrib_idx)const
{
  double new_weight = sumPosterioriByFeatures(distrib_idx);
  new_weight /= getFeatureCount();
  return new_weight;
}

RealVector<double> ExpectationMaximalizationAlgo::countMean(uint32_t distrib_idx,
                                                    const vector<Feature> &feature_vec )const
{
  RealVector<double> vec(getFeatureCount()), temp(getFeatureCount());
  //suma iloczynów prawdopodobieństw posteriori i wektorów cech
  double posteriori = 0;
  for(uint32_t feature=0; feature < getFeatureCount(); ++feature)
  {
    const Feature& actual = feature_vec[feature];
    posteriori = getPosterioriPropability(feature, distrib_idx);
    temp = utils::convert(actual);
    temp *= posteriori;
    vec += temp;
  }
  //dzielimy sume przez sume p-stw posteriori po wektorach cech
  vec *= 1/sumPosterioriByFeatures(distrib_idx);
  return vec;
}
RealVector<double> ExpectationMaximalizationAlgo::countDiagonalCovariance(uint32_t distrib_idx,
                                                                  const vector<Feature> &feature_vec,
                                                                  const RealVector<double> &mean)const
{
  const uint32_t FEATURE_CNT = getFeatureCount();
  double act_posteriori = 0;
  RealVector<double> diff(FEATURE_CNT), ret(FEATURE_CNT);
  //suma różnicy wektora cech i wektora średniego, pomnożona przez p-stwo posteriori
  for(uint32_t act_feature = 0; act_feature < FEATURE_CNT; ++act_feature)
  {
    act_posteriori = getPosterioriPropability(act_feature, distrib_idx);

    diff = utils::convert(feature_vec[act_feature]);
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
void ExpectationMaximalizationAlgo::learnModel(GmmModel &model, const std::vector<alize::Feature> &feature_vec)
{
  for(uint32_t i=0; i< LEARNING_ITERATION_CNT; ++i)
  {
    performOneIteration(model, feature_vec);
  }

}
