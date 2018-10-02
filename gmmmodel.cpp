#include "gmmmodel.hpp"
using namespace alize;
using namespace std;
/*
 * Protected
 */

void GmmModel::reloadConfig()
{
  throw std::runtime_error("TODO");
}
void GmmModel::initDefaultMixture()
{
  s_.createMixture(DISTRIB_COUNT, type_);

}

/*
 * Public
 */

GmmModel::GmmModel(const alize::Config &conf):conf_(conf), s_(conf), features_(conf)
{
  initDefaultMixture();
}

GmmModel::GmmModel(GmmModel &&other):conf_(other.conf_), s_(conf_), features_(conf_)
{
  initDefaultMixture();
  throw std::runtime_error("TODO");
}

GmmModel& GmmModel::operator=(GmmModel &&other){

  throw std::runtime_error("Todo");
  initDefaultMixture();
}

void GmmModel::setConfig(const alize::Config &conf)
{
  conf_ = conf;
  reloadConfig();
  initDefaultMixture();
}

alize::Config GmmModel::getConfig()const
{
  return conf_;
}

void GmmModel::addLearnAlgo(std::unique_ptr<LearningAlgo> &&algo_to_set)
{
  algo_ = std::move(algo_to_set);
}


void GmmModel::addFeature(const alize::Feature &feature)
{
  if(!features_.addFeature(feature))
  {
    throw std::runtime_error("TODO");
  }
}

void GmmModel::learnModel()
{
  algo_->LearnModel(*this, extractAllFeatures(features_) );
}


double GmmModel::countLikehood(const alize::Feature &feature)
{
  Mixture &mix = s_.getMixture(MIXTURE_IDX);
  double ret = 0;
  for(uint32_t i = 0; i < mix.getDistribCount(); ++i)
  {
    ret +=mix.getDistrib(i).computeLK(feature);
  }
  return ret;
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
