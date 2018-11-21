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
  Verificator() = default;
  explicit Verificator(double threshold);
  Verificator(const Verificator &other) = default;
  Verificator& operator=(const Verificator &other) = default;
  Verificator(Verificator &&other) = default;
  Verificator& operator=(Verificator &&other) = default;

  double getThreshold() const;
  void setThreshold(double new_threshold);

  bool verifyModel(const GmmModel &verified,
                   std::vector<alize::Feature> record_features);

};

#endif // VERIFICATOR_HPP
