#ifndef UTILS
#define UTILS
#include<alize/alize.h>
#include<vector>
#include<stdexcept>
#include"exceptions/simple_exceptions.hpp"


namespace utils
{

  alize::RealVector<double> toRealVector(const alize::Feature &f);
  alize::RealVector<double> toRealVector(const std::vector<double> &vec);
  alize::Feature toFeature(const std::vector<double> &vec);

  alize::RealVector<double> diag(const alize::Matrix<double> &m);


}//namespace utils


#endif // UTILS

