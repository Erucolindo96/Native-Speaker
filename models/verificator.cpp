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

bool verifyModel(const GmmModel &verified,
                 std::vector<alize::Feature> record_features)
{
  throw std::runtime_error("TODO");
  return false;
}
