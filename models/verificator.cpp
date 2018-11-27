#include "verificator.hpp"

Verificator::Verificator(double threshold):threshold_(threshold)
{}


double Verificator::getThreshold() const
{
  return threshold_;
}
void Verificator::setThreshold(double new_threshold)
{
  threshold_ = new_threshold;
}

bool Verificator::verifyModel(const GmmModel &verified,
                 const std::vector<alize::Feature> &record_features,
                 const GmmModel &ubm_model)
{
  if(verified.getFeatureVectorSize() != ubm_model.getFeatureVectorSize())
  {
    throw InvalidFeatureSize(__FILE__ + std::string(", line: ") + std::to_string(__LINE__)
      + std::string(" - verified model and UBM model does not have equal Feature's size's"));
  }
  if(record_features.empty())
  {
    throw VerifyModelWithoutFeatures(__FILE__ + std::string(", line: ") + std::to_string(__LINE__)
                                     + std::string(" - try to verify model with empty Feature Vector"));
  }
  double sum_lk_model = verified.countLikehoodWithWeight(record_features),
      sum_lk_ubm = ubm_model.countLikehoodWithWeight(record_features);

  double llk_model = log(sum_lk_model), llk_ubm = log(sum_lk_ubm);
  if((llk_model - llk_ubm) >= threshold_)
  {
    return true;
  }
  return false;
}
