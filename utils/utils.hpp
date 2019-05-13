#ifndef UTILS
#define UTILS
#include<alize/alize.h>
#include<vector>
#include<stdexcept>
#include"exceptions/simple_exceptions.hpp"
#include<iostream>
#include<algorithm>

namespace utils
{

  alize::RealVector<double> toRealVector(const alize::Feature &f);
  alize::RealVector<double> toRealVector(const std::vector<double> &vec);
  alize::Feature toFeature(const std::vector<double> &vec);

  alize::RealVector<double> diag(const alize::Matrix<double> &m);

  /**
   * @brief getVectSizeAndDistribCnt Sprawdza, jaka jest wielkość wektora cech
   * i ilość dystrybucji, zapisana w pliku z modelem w XML-u.
   * @param path_to_mixture Ścieżka do badanego pliku z modelem
   * @return Wielkość wektora cech, oraz ilość dystrybucji w danym modelu
   * @throw FileNotFound jeżeli nie znaleziono pliku.
   * @throw NotAModelFile jeżeli plik nie zawiera modelu w formacie XML
   */
  std::pair<uint32_t, uint32_t> getVectSizeAndDistribCnt(const std::string &path_to_mixture);

  bool fileExist(const std::string &path);
  bool dirExist(const std::string &path);

  double avoidNaNInLk(double lk);

}//namespace utils


#endif // UTILS

