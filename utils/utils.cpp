
#include "utils/utils.hpp"

namespace utils
{

  alize::RealVector<double> toRealVector(const alize::Feature &f)
  {
    alize::RealVector<double> vec(f.getVectSize());
    for(uint32_t i = 0; i < f.getVectSize(); ++i)
    {
      vec.addValue(f[i]);
    }
    return vec;
  }


  alize::RealVector<double> toRealVector(const std::vector<double> &vec)
  {
    alize::RealVector<double> ret(vec.size(), vec.size());
    for(uint32_t i=0; i< vec.size(); ++i)
    {
      ret[i] = vec.at(i);
    }
    return ret;
  }
  alize::Feature toFeature(const std::vector<double> &vec)
  {
    alize::Feature f(vec.size());
    for(uint32_t i = 0; i < vec.size(); ++i)
    {
      f[i] = vec[i];
    }
    return f;
  }

  alize::RealVector<double> diag(const alize::Matrix<double> &m)
  {
    if(m.cols() != m.rows())
    {
      throw NotSquareMatrix("File:" + std::string(__FILE__) + " Line :" + std::to_string(__LINE__)
                            + std::string(": Matrix in argument is not square matrix"));
    }
    alize::RealVector<double> ret(m.cols(), m.cols());
    for(uint32_t i = 0; i< m.cols(); ++i)
    {
      ret[i] = m(i,i);
    }
    return ret;
  }



}//namespace utils
