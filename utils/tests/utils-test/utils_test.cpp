#ifndef DIAGONAL_TEST
#define DIAGONAL_TEST

#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE utils_test
#include<boost/test/unit_test.hpp>
#include<alize/alize.h>
#include <typeinfo>
#include <random>
#include<iostream>
#include "utils/utils.hpp"
using namespace boost;
using namespace std;
using namespace alize;
using namespace utils;
const double EPS = 0.00001;

BOOST_AUTO_TEST_SUITE( convertionToAlizeRealVectors )

BOOST_AUTO_TEST_CASE(convertToAlizeRealVectorFromStdVector)
{
  vector<double> sample = {1.0, -5.0, -11.33, -133.52};
  RealVector<double> converted(convert(sample));

  BOOST_CHECK_CLOSE(converted[0], 1.0, EPS);
  BOOST_CHECK_CLOSE(converted[1], -5.0, EPS);
  BOOST_CHECK_CLOSE(converted[2], -11.33, EPS);
  BOOST_CHECK_CLOSE(converted[3], -133.52, EPS);

}


BOOST_AUTO_TEST_SUITE_END()





#endif//DIAGONAL_TEST
