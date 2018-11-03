#ifndef UTILS
#define UTILS
#include<alize/alize.h>
#include<vector>
namespace utils
{
  const alize::RealVector<double> convert(const alize::Feature &f);
  const alize::RealVector<double> convert(const std::vector<double> &vec);
  const alize::Feature convert(const std::vector<double> vec);
}//namespace utils


#endif // UTILS

