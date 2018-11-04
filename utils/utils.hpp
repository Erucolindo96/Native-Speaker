#ifndef UTILS
#define UTILS
#include<alize/alize.h>
#include<vector>
namespace utils
{
  const alize::RealVector<double> toRealVector(const alize::Feature &f);
  const alize::RealVector<double> toRealVector(const std::vector<double> &vec);
  const alize::Feature toFeature(const std::vector<double> &vec);
}//namespace utils


#endif // UTILS

