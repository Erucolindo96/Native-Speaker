#ifndef UTILS
#define UTILS
#include<alize/alize.h>
#include<vector>
#include<stdexcept>

class NotSquareMatrix: public std::invalid_argument
{
public:
  NotSquareMatrix(std::string &&msg) : std::invalid_argument(msg)
  {}
};

namespace utils
{

  alize::RealVector<double> toRealVector(const alize::Feature &f);
  alize::RealVector<double> toRealVector(const std::vector<double> &vec);
  alize::Feature toFeature(const std::vector<double> &vec);

  alize::RealVector<double> diag(const alize::Matrix<double> &m);
}//namespace utils


#endif // UTILS

