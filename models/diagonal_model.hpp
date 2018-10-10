#ifndef DIAGONALMODEL_HPP
#define DIAGONALMODEL_HPP

#include "models/gmmmodel.hpp"
#include<alize/alize.h>

class DiagonalModel : public GmmModel
{
protected:

  void initDefaultMixture(uint32_t distrib_cnt) override;
public:
  DiagonalModel() = delete;
  DiagonalModel(const alize::Config &conf, uint32_t distrib_cnt=512);
  DiagonalModel(const DiagonalModel &other) = delete;
  DiagonalModel(DiagonalModel &&other);
  const DiagonalModel& operator =(const DiagonalModel &other) = delete;
  const DiagonalModel& operator =(DiagonalModel &&other) = delete;

  void setDistribCovariance(uint32_t distrib, const alize::RealVector<double> &diagonal_covariance) override;
  void setDistribCovariance(uint32_t distrib, const alize::DoubleMatrix &covariance) override;

  alize::RealVector<double> getDistribCovariance(uint32_t distrib)const;



};

#endif // DIAGONALMODEL_HPP
