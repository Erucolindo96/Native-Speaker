#include "models/gmmmodel.hpp"
using namespace alize;
using namespace std;
/*
 * Protected
 */

alize::Config GmmModel::createConfig()const
{
  alize::Config conf;
  conf.setParam("vectSize", std::to_string(FEATURE_SIZE).c_str());
  conf.setParam("mixtureDistribCount", std::to_string(DISTRIB_CNT).c_str());
  conf.setParam("maxLLK", std::to_string(MAX_LLK).c_str());
  conf.setParam("minLLK", std::to_string(MIN_LLK).c_str());
//  conf.setParam("minCov", "1e-10");
  return conf;
}

void GmmModel::initDefaultMixture(uint32_t distrib_cnt)
{
  s_->createMixture(distrib_cnt, type_);

}

alize::Mixture& GmmModel::getMixtureRef()const
{
  const uint32_t M_IDX = 0;
  return s_->getMixture(M_IDX);
}


/*
 * Public
 */
GmmModel::GmmModel(uint32_t distrib_cnt,uint32_t feature_size):QObject(),
  DISTRIB_CNT(distrib_cnt),FEATURE_SIZE(feature_size), features_()
{
  alize::Config conf = createConfig();
  s_ = std::make_unique<alize::MixtureServer>(conf);
}
GmmModel::GmmModel(uint32_t distrib_cnt, uint32_t feature_size, const std::string &name): GmmModel(distrib_cnt, feature_size)
{
  setName(name);
}

GmmModel::GmmModel(GmmModel &&other):GmmModel(other.DISTRIB_CNT, other.FEATURE_SIZE)
{}

void GmmModel::addTrainingFeature(const alize::Feature &feature)
{
  std::lock_guard<std::mutex> l(m_);
  features_.push_back(feature);
}

void GmmModel::addTrainingFeature(const std::vector<alize::Feature> &vec)
{
  std::lock_guard<std::mutex> l(m_);
  features_ = vec;
}

std::vector<alize::Feature> GmmModel::getTrainingFeatures()const
{
  std::lock_guard<std::mutex> l(m_);
  return features_;
}

void GmmModel::setName(const std::string &name)
{
  std::lock_guard<std::mutex> l(m_);
  s_->setServerName(name.c_str());
}

std::string GmmModel::getName()const
{
  std::lock_guard<std::mutex> l(m_);
  return std::string(s_->getServerName().c_str());
}

alize::DistribType GmmModel::getType()const
{
  std::lock_guard<std::mutex> l(m_);
  return type_;
}
const std::unique_ptr<alize::MixtureServer>& GmmModel::getMixtureServerRef()const
{
  std::lock_guard<std::mutex> l(m_);
  return s_;
}



double GmmModel::countLikehoodWithWeight(const alize::Feature &feature)const
{
  double ret = 0;
  const uint32_t DISTRIB_CNT = getDistribCount();
  try
  {
    for(uint32_t i = 0; i < DISTRIB_CNT; ++i)
    {
      ret += countLikehoodWithWeight(feature, i);//metoda juz synchronizowana
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
    if(arg.getVectSize() != FEATURE_SIZE)
    {
      throw InvalidFeatureSize(__FILE__ + std::string(", line: ") + std::to_string(__LINE__)
                               + std::string(" - try to count likehood feature with model,"
                                             " where feature's size's are not equal"));
    }

    double d_lk = 0;
    {
      std::lock_guard<std::mutex> l(m_);
      d_lk = getMixtureRef().getDistrib(distrib_idx).computeLK(arg);
    }
    return d_lk * getDistribWeight(distrib_idx);//metoda getDistribWeght jest synchronizowana

  }
  catch(alize::IndexOutOfBoundsException e)
  {
    throw IndexOutOfBounds(e.toString().c_str());
  }

}

double GmmModel::countLikehoodWithWeight(const std::vector<alize::Feature> &arg)const
{
  double sum = 0;
  for(uint32_t i = 0; i< arg.size(); ++i)
  {
    sum += countLikehoodWithWeight(arg[i]);//metoda juz synchronizowana
  }
  return sum;
}

uint32_t GmmModel::getDistribCount()const
{
  std::lock_guard<std::mutex> l(m_);
  return getMixtureRef().getDistribCount();
}

double GmmModel::getDistribWeight(uint32_t distrib_idx)const
{
  try
  {
    std::lock_guard<std::mutex> l(m_);
    return getMixtureRef().weight(distrib_idx);
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
    std::lock_guard<std::mutex> l(m_);
    getMixtureRef().weight(distrib) = new_weight;
  }
  catch(alize::IndexOutOfBoundsException e)
  {
    throw IndexOutOfBounds(e.toString().c_str());
  }

}

void GmmModel::setDistribMean(uint32_t distrib, const alize::RealVector<double> &new_mean)
{

  if(new_mean.size() != getFeatureVectorSize())
  {
    throw InvalidFeatureSize("File:" + std::string(__FILE__) + " Line :" + std::to_string(__LINE__) +
                                   ": size of new_mean vector is not equal \
                                    to set in configuration of model");
  }
  try
  {
    std::lock_guard<std::mutex> l(m_);
    alize::Distrib& distrib_ref = getMixtureRef().getDistrib(distrib);
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
    std::lock_guard<std::mutex> l(m_);
    return getMixtureRef().getDistrib(distrib).getMeanVect();
  }
  catch(alize::IndexOutOfBoundsException e)
  {
    throw IndexOutOfBounds(e.toString().c_str());
  }
}

uint32_t GmmModel::getFeatureVectorSize()const
{
  std::lock_guard<std::mutex> l(m_);
  return s_->getVectSize();
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

alize::DistribType GmmModel::getDistribTypeOfServer(const alize::MixtureServer &s)
{
  const uint32_t M_IDX = 0;
  return s.getMixture(M_IDX).getType();
}

uint32_t GmmModel::getDistribCountOfServer(const alize::MixtureServer &s)
{
  const uint32_t M_IDX = 0;
  return s.getMixture(M_IDX).getDistribCount();
}



void GmmModel::copyDataFromMixtureServer(const alize::MixtureServer &s, GmmModel &model)
{
  const uint32_t M_IDX = 0;
  if(GmmModel::getDistribTypeOfServer(s) != model.getType())
  {
    throw InvalidModelType(__FILE__ + std::string(", line: ") + std::to_string(__LINE__)
                           + std::string(" - try to copy mixture, which type arent equal with type in model"));
  }
  if(GmmModel::getDistribCountOfServer(s) != model.getDistribCount())
  {
    throw InvalidDistribCount(__FILE__ + std::string(", line: ") + std::to_string(__LINE__)
                              + std::string(" - try to copy mixture, which distrib count arent equal with count in model"));
  }
  if(s.getVectSize() != model.getFeatureVectorSize())
  {
    throw InvalidFeatureSize(__FILE__ + std::string(", line: ") + std::to_string(__LINE__)
                             + std::string(" - try to copy mixture, which feature size arent equal with size in model"));
  }
  const uint32_t D_CNT = model.getDistribCount();
  alize::Config conf = model.createConfig();

  std::lock_guard<std::mutex> l(model.m_);
  model.s_.release();
  model.s_ = make_unique<alize::MixtureServer>(conf);
  model.initDefaultMixture(D_CNT);
  model.getMixtureRef() = s.getMixture(M_IDX);
  model.getMixtureRef().computeAll();
}
