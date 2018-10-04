
#include "utils/utils.hpp"

namespace utils
{
  const alize::RealVector<double> convert(const alize::Feature &f)
  {
    alize::RealVector<double> vec(f.getVectSize());
    for(uint32_t i = 0; i < f.getVectSize(); ++i)
    {
      vec.addValue(f[i]);
    }
    return vec;
  }

}//namespace utils
