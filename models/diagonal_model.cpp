#include "models/diagonal_model.hpp"


void DiagonalModel::initDefaultMixture(uint32_t distrib_cnt)
{
  GmmModel::initDefaultMixture(distrib_cnt);
}


DiagonalModel::DiagonalModel(const alize::Config &conf, uint32_t distrib_cnt): GmmModel(conf, distrib_cnt)
{
  GmmModel::type_ = alize::DistribType_GD;
  initDefaultMixture(distrib_cnt);
}

DiagonalModel::DiagonalModel(DiagonalModel &&other):GmmModel(std::move(other))
{}
void DiagonalModel::setDistribCovariance(uint32_t distrib, const alize::RealVector<double> &diagonal_covariance)
{
  alize::DistribGD &distrib_ref = dynamic_cast<alize::DistribGD&>( s_.getMixture(MIXTURE_IDX).getDistrib(distrib));
  distrib_ref.getCovVect() = diagonal_covariance;

}
void DiagonalModel::setDistribCovariance(uint32_t distrib, const alize::DoubleMatrix &covariance)
{
  throw std::runtime_error("Try to set full covariance matrix in DiagonalModel !");
}

alize::RealVector<double> DiagonalModel::getDistribCovariance(uint32_t distrib)const
{
  alize::DistribGD &distrib_ref = dynamic_cast<alize::DistribGD&>( s_.getMixture(MIXTURE_IDX).getDistrib(distrib));
  return distrib_ref.getCovVect();
}



