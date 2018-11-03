#include "models/gmmmodel.hpp"
using namespace alize;
using namespace std;
/*
 * Protected
 */


void GmmModel::initDefaultMixture(uint32_t distrib_cnt)
{
  s_.createMixture(distrib_cnt, type_);

}


/*
 * Public
 */

GmmModel::GmmModel(const alize::Config &conf):
  conf_(conf), s_(conf), features_()
{}

GmmModel::GmmModel(GmmModel &&other):GmmModel(other.conf_)
{}


alize::Config GmmModel::getConfig()const
{
  return conf_;
}

void GmmModel::addLearnAlgo(std::unique_ptr<LearningAlgo> &&algo_to_set)
{
  algo_ = std::move(algo_to_set);
}
std::unique_ptr<LearningAlgo>& GmmModel::getLearnAlgo()
{
  return algo_;
}

void GmmModel::learnModelUsingLearnAlgo(std::unique_ptr<LearningAlgo> &algo)
{
  algo->learnModel(*this, features_ );
}

void GmmModel::learnModel()
{
  algo_->learnModel(*this, features_ );
}

void GmmModel::addTrainingFeature(const alize::Feature &feature)
{
  features_.push_back(feature);
/*  if(!features_.addFeature(feature))
  {
    throw std::runtime_error("TODO");
  }
*/
}

std::vector<alize::Feature> GmmModel::getTrainingFeatures()
{
  return features_;
  /*
  const uint32_t CNT = features_.size();
  std::vector<alize::Feature> vec(CNT);
  for(uint32_t i = 0; i < CNT; ++i)
  {
    features_.readFeature(vec[i]);
  }
  return vec;
  */
}


double GmmModel::countLikehoodWithWeight(const alize::Feature &feature)const
{
  double ret = 0;
  const uint32_t DISTRIB_CNT = getDistribCount();
  try
  {
    for(uint32_t i = 0; i < DISTRIB_CNT; ++i)
    {
      ret += countLikehoodWithWeight(feature, i);
    }
  }
  catch(alize::IndexOutOfBoundsException e)
  {
    throw IndexOutOfBounds(e.toString().c_str());
  }

  return ret;
}

double GmmModel::countLikehoodWithWeight(const alize::Feature &arg, uint32_t distrib_idx)const
{
  try
  {
    return s_.getMixture(MIXTURE_IDX).getDistrib(distrib_idx).computeLK(arg) *
      getDistribWeight(distrib_idx);

  }
  catch(alize::IndexOutOfBoundsException e)
  {
    throw IndexOutOfBounds(e.toString().c_str());
  }
}
uint32_t GmmModel::getDistribCount()const
{
  return s_.getMixture(MIXTURE_IDX).getDistribCount();
}

double GmmModel::getDistribWeight(uint32_t distrib_idx)const
{
  try
  {
    return s_.getMixture(MIXTURE_IDX).weight(distrib_idx);

  }
  catch(alize::IndexOutOfBoundsException e)
  {
    throw IndexOutOfBounds(e.toString().c_str());
  }
}
void GmmModel::setDistribWeight(uint32_t distrib, double new_weight)
{
  try
  {
    s_.getMixture(MIXTURE_IDX).weight(distrib) = new_weight;
  }
  catch(alize::IndexOutOfBoundsException e)
  {
    throw IndexOutOfBounds(e.toString().c_str());
  }

}

void GmmModel::setDistribMean(uint32_t distrib, const alize::RealVector<double> &new_mean)
{
  if(new_mean.size() != getFeatureVectorSize())
    throw InvalidFeatureVectorSize("File:" + std::string(__FILE__) + " Line :" + std::to_string(__LINE__) +
                                   ": size of new_mean vector is not equal \
                                    to set in configuration of model");
  try
  {
    alize::Distrib& distrib_ref = s_.getMixture(MIXTURE_IDX).getDistrib(distrib);
    distrib_ref.setMeanVect(new_mean);
    distrib_ref.computeAll();
  }
  catch(alize::IndexOutOfBoundsException e)
  {
    throw IndexOutOfBounds(e.toString().c_str());
  }
}
alize::RealVector<double> GmmModel::getDistribMean(uint32_t distrib)const
{
  try
  {
    return s_.getMixture(MIXTURE_IDX).getDistrib(distrib).getMeanVect();

  }
  catch(alize::IndexOutOfBoundsException e)
  {
    throw IndexOutOfBounds(e.toString().c_str());
  }
}

uint32_t GmmModel::getFeatureVectorSize()const
{
  return s_.getVectSize();
}

std::vector<alize::Feature> GmmModel::extractAllFeatures(alize::FeatureServer &s)
{
  Feature f;
  std::vector<Feature> ret(s.getFeatureCount());
  const uint32_t FIRST = 0;
  s.seekFeature(FIRST);
  for(uint32_t i=FIRST; i < s.getFeatureCount(); ++i)
  {
    s.readFeature(f);
    ret.push_back(f);
  }
  s.seekFeature(FIRST);
  return ret;
}
