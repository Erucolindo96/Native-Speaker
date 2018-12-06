


#include"utils/tests/utils-test/utils_test.hpp"
using namespace boost;
using namespace std;
using namespace alize;
using namespace utils;
const double EPS = 0.00001;

BOOST_AUTO_TEST_SUITE( convertionToAlizeStructures )

BOOST_AUTO_TEST_CASE(convertToAlizeRealVectorFromFeature)
{
  const uint32_t FEATURE_SIZE = 4;
  Feature sample(FEATURE_SIZE);
  sample[0] = 1.0;
  sample[1] = -5.0;
  sample[2] = -11.33;
  sample[3] = -133.52;
  RealVector<double> converted = toRealVector(sample);
  BOOST_REQUIRE_EQUAL(converted.size(), FEATURE_SIZE);

  BOOST_CHECK_CLOSE(converted[0], 1.0, EPS);
  BOOST_CHECK_CLOSE(converted[1], -5.0, EPS);
  BOOST_CHECK_CLOSE(converted[2], -11.33, EPS);
  BOOST_CHECK_CLOSE(converted[3], -133.52, EPS);

}



BOOST_AUTO_TEST_CASE(convertToAlizeRealVectorFromStdVector)
{
  const uint32_t FEATURE_SIZE = 4;
  vector<double> sample = {1.0, -5.0, -11.33, -133.52};
  RealVector<double> converted(toRealVector(sample));
  BOOST_REQUIRE_EQUAL(converted.size(), FEATURE_SIZE);

  BOOST_CHECK_CLOSE(converted[0], 1.0, EPS);
  BOOST_CHECK_CLOSE(converted[1], -5.0, EPS);
  BOOST_CHECK_CLOSE(converted[2], -11.33, EPS);
  BOOST_CHECK_CLOSE(converted[3], -133.52, EPS);

}

BOOST_AUTO_TEST_CASE(convertToFeatureFromStdDoubleVector)
{
  const uint32_t FEATURE_SIZE = 4;
  vector<double> sample = {1.0, -5.0, -11.33, -133.52};
  Feature converted(toFeature(sample));
  BOOST_REQUIRE_EQUAL(converted.getVectSize(), FEATURE_SIZE);

  BOOST_CHECK_CLOSE(converted[0], 1.0, EPS);
  BOOST_CHECK_CLOSE(converted[1], -5.0, EPS);
  BOOST_CHECK_CLOSE(converted[2], -11.33, EPS);
  BOOST_CHECK_CLOSE(converted[3], -133.52, EPS);

}

BOOST_AUTO_TEST_CASE(throwExceptionNotSquareMatrixIfDiagonalizeNotSquareMatrix)
{
  RealVector<double> vec = toRealVector({0.011, -29.29, -0.29});
  Matrix<double> m(vec);
  BOOST_CHECK_THROW(utils::diag(m), NotSquareMatrix);

}

BOOST_AUTO_TEST_CASE(getDiagonalOfMatrixIfMatrixIsSquare)
{
  Matrix<double> m(4,4);
  m(0,0) = 1.0;
  m(1,1) = -1.5;
  m(2,2) = -100;
  m(3,3) = 182.287;

  RealVector<double> diagonal = utils::diag(m);
  double eps = 0.0001;
  BOOST_CHECK_CLOSE(diagonal[0], 1.0, eps);
  BOOST_CHECK_CLOSE(diagonal[1], -1.5, eps);
  BOOST_CHECK_CLOSE(diagonal[2], -100, eps);
  BOOST_CHECK_CLOSE(diagonal[3], 182.287, eps);
}

BOOST_AUTO_TEST_CASE(returnTrueIfFileExist)
{
  const std::string real_path = "samples/mp3/inwokacja.mp3";
  BOOST_CHECK(utils::fileExist(real_path));
}

BOOST_AUTO_TEST_CASE(returnTrueIfDirExist)
{
  const std::string real_dir = "samples/mp3";
  BOOST_CHECK(utils::dirExist(real_dir));
}

BOOST_AUTO_TEST_CASE(returnFalseIfFileNotExist)
{
  const std::string fake_path = "samples/mp3/not_a_file.mp3";
  BOOST_CHECK(!utils::fileExist(fake_path));
}

BOOST_AUTO_TEST_CASE(returnFalseIfDirNotExist)
{
  const std::string fake_dir = "not_a_dir/";
  BOOST_CHECK(!utils::dirExist(fake_dir));
}






BOOST_AUTO_TEST_SUITE_END()






