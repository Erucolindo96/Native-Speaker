﻿#include "models/diagonal_model.hpp"


void DiagonalModel::initDefaultMixture(uint32_t distrib_cnt)
{
  GmmModel::initDefaultMixture(distrib_cnt);
}


DiagonalModel::DiagonalModel(const alize::Config &conf): GmmModel(conf)
{
  GmmModel::type_ = alize::DistribType_GD;
  initDefaultMixture(stoi(conf_.getParam("mixtureDistribCount").c_str()));
}

DiagonalModel::DiagonalModel(DiagonalModel &&other):GmmModel(std::move(other))
{}
void DiagonalModel::setDistribCovariance(uint32_t distrib, const alize::RealVector<double> &diagonal_covariance)
{
  if (diagonal_covariance.size() != getFeatureVectorSize())
    throw InvalidFeatureVectorSize("File:" + std::string(__FILE__) + " Line :" + std::to_string(__LINE__) +
                                   ": size of diagonal_covariance vector is not equal \
                                    to set in configuration of model");
  try
  {
    alize::DistribGD &distrib_ref = dynamic_cast<alize::DistribGD&>( s_.getMixture(MIXTURE_IDX).getDistrib(distrib));
    distrib_ref.getCovVect() = diagonal_covariance;
    distrib_ref.computeAll();
  }
  catch(alize::IndexOutOfBoundsException e)
  {
    throw IndexOutOfBounds(e.toString().c_str());
  }
}
void DiagonalModel::setDistribCovariance(uint32_t distrib, const alize::DoubleMatrix &covariance)
{
  throw std::runtime_error("Try to set full covariance matrix in DiagonalModel !");
}

alize::RealVector<double> DiagonalModel::getDistribCovariance(uint32_t distrib)const
{
  try
  {
    alize::DistribGD &distrib_ref = dynamic_cast<alize::DistribGD&>( s_.getMixture(MIXTURE_IDX).getDistrib(distrib));
    return distrib_ref.getCovVect();
  }
  catch(alize::IndexOutOfBoundsException e)
  {
    throw IndexOutOfBounds(e.toString().c_str());
  }
}



