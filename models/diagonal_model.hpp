﻿#ifndef DIAGONALMODEL_HPP
#define DIAGONALMODEL_HPP

#include "models/gmmmodel.hpp"
#include<alize.h>

class DiagonalModel : public GmmModel
{
  Q_OBJECT
protected:

  void initDefaultMixture(uint32_t distrib_cnt) override;
public:
  DiagonalModel() = delete;
  explicit DiagonalModel(uint32_t distrib_cnt, uint32_t feature_size);
  explicit DiagonalModel(uint32_t distrib_cnt, uint32_t feature_size, const std::string &name);
  DiagonalModel(const DiagonalModel &other) = delete;
  DiagonalModel(DiagonalModel &&other);
  const DiagonalModel& operator =(const DiagonalModel &other) = delete;
  const DiagonalModel& operator =(DiagonalModel &&other) = delete;

  void setDistribCovariance(uint32_t distrib, const alize::RealVector<double> &diagonal_covariance) override;
  void setDistribCovariance(uint32_t distrib, const alize::DoubleMatrix &covariance) override;

  alize::RealVector<double> getDistribCovariance(uint32_t distrib)const override;

  ~DiagonalModel() override = default;

};



#endif // DIAGONALMODEL_HPP
