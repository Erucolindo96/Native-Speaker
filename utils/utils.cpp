
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


  const alize::RealVector<double> convert(const std::vector<double> &vec)
  {
    alize::RealVector<double> ret(vec.size(), vec.size());
    for(uint32_t i=0; i< vec.size(); ++i)
    {
      ret[i] = vec.at(i);
    }
    return ret;
  }
  const alize::Feature convert(const std::vector<double> vec)
  {
    alize::Feature f(vec.size());
    for(uint32_t i = 0; i < vec.size(); ++i)
    {
      f[i] = vec[i];
    }
  }

}//namespace utils
