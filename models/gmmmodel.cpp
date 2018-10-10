#include "models/gmmmodel.hpp"
using namespace alize;
using namespace std;
/*
 * Protected
 */

void GmmModel::reloadConfig()
{
  throw std::runtime_error("TODO");
}
void GmmModel::initDefaultMixture(uint32_t distrib_cnt)
{
  s_.createMixture(distrib_cnt, type_);

}


/*
 * Public
 */

GmmModel::GmmModel(const alize::Config &conf, uint32_t distrib_cnt):
  conf_(conf), s_(conf), features_(conf), DISTRIB_COUNT(distrib_cnt)
{}

GmmModel::GmmModel(GmmModel &&other):GmmModel(other.conf_)
{}

void GmmModel::setConfig(const alize::Config &conf)
{
  conf_ = conf;
  reloadConfig();
}

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
  algo->learnModel(*this, extractAllFeatures(features_) );
}

void GmmModel::learnModel()
{
  algo_->learnModel(*this, extractAllFeatures(features_) );
}

void GmmModel::addTrainingFeature(const alize::Feature &feature)
{
  if(!features_.addFeature(feature))
  {
    throw std::runtime_error("TODO");
  }
}

std::vector<alize::Feature> GmmModel::getTrainingFeatures()
{
  const uint32_t CNT = features_.getFeatureCount();
  std::vector<alize::Feature> vec(CNT);
  for(uint32_t i = 0; i < CNT; ++i)
  {
    features_.readFeature(vec[i]);
  }
  return vec;
}


double GmmModel::countLikehoodWithWeight(const alize::Feature &feature)const
{
  double ret = 0;
  const uint32_t DISTRIB_CNT = s_.getMixture(MIXTURE_IDX).getDistribCount();
  for(uint32_t i = 0; i < DISTRIB_CNT; ++i)
  {
    ret += countLikehoodWithWeight(feature, i);
  }
  return ret;
}

double GmmModel::countLikehoodWithWeight(const alize::Feature &arg, uint32_t distrib_idx)const
{
  return s_.getMixture(MIXTURE_IDX).getDistrib(distrib_idx).computeLK(arg) *
      getDistribWeight(distrib_idx);
}

uint32_t GmmModel::getDistribCount()const
{
  return s_.getDistribCount();
}

uint32_t GmmModel::getDistribWeight(uint32_t distrib_idx)const
{
  return s_.getMixture(MIXTURE_IDX).weight(distrib_idx);
}

void GmmModel::setDistribWeight(uint32_t distrib, double new_weight)
{
  s_.getMixture(MIXTURE_IDX).weight(distrib) = new_weight;
}

void GmmModel::setDistribMean(uint32_t distrib, alize::RealVector<double> new_mean)
{
  alize::Distrib& distrib_ref = s_.getMixture(MIXTURE_IDX).getDistrib(distrib);
  distrib_ref.setMeanVect(new_mean);
}
alize::RealVector<double> GmmModel::getDistribMean(uint32_t distrib)const
{
  return s_.getMixture(MIXTURE_IDX).getDistrib(distrib).getMeanVect();
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
