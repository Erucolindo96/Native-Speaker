#ifndef VERIFICATOR_HPP
#define VERIFICATOR_HPP
#include"models/diagonal_model.hpp"
#include<alize.h>
#include<cmath>

class Verificator
{
protected:
  double threshold_;
public:
//  Verificator() = default;
  explicit Verificator(double threshold = 0.0);
  Verificator(const Verificator &other) = default;
  Verificator& operator=(const Verificator &other) = default;
  Verificator(Verificator &&other) = default;
  Verificator& operator=(Verificator &&other) = default;

  double getThreshold() const;
  void setThreshold(double new_threshold);

  bool verifyModel(const GmmModel &verified,
                   const std::vector<alize::Feature> &record_features,
                   const GmmModel &ubm_model)const;

  double countLogLikehood(const GmmModel &model,
                          const std::vector<alize::Feature> &record_features)const;

};

#endif // VERIFICATOR_HPP
