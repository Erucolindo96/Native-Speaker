#include "models/diagonal_model.hpp"


void DiagonalModel::initDefaultMixture()
{
  GmmModel::initDefaultMixture();
}


DiagonalModel::DiagonalModel(const alize::Config &conf): GmmModel(conf)
{
  GmmModel::type_ = alize::DistribType_GD;
  initDefaultMixture();
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

