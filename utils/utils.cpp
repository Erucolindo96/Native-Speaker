
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


  bool fileExist(const std::string &path)
  {
    ifstream f(path);
    bool ret = f.good();
    f.close();
    return ret;
  }
  bool dirExist(const std::string &path)
  {
    return utils::fileExist(path);
  }

  double avoidNaNInLk(double lk)
  {
    if(std::isnan(lk))
    {
      return 1e-200;//alize::Object::EPS_LK - jest protected, dlatego wklejona sztywna wartośći
    }
    return lk;
  }
  std::vector<alize::Feature> operator+(const std::vector<alize::Feature> &f1,
                                        const std::vector<alize::Feature> &f2)
  {
    const uint32_t RET_L = f1.size() + f2.size();
    std::vector<alize::Feature> ret;
    ret.reserve(RET_L);
    for(auto f: f1)
    {
      ret.push_back(f);
    }
    for(auto f: f2)
    {
      ret.push_back(f);
    }
    return ret;
  }

}//namespace utils
