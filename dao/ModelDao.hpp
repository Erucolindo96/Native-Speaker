#ifndef MODELDAO_HPP
#define MODELDAO_HPP
#include<alize/alize.h>
#include"models/gmmmodel.hpp"
class ModelDao
{

public:
  ModelDao() = default;
  ModelDao(const ModelDao &other) = default;
  ModelDao& operator =(const ModelDao &other) = default;
  ModelDao(ModelDao &&other) = default;
  ModelDao& operator =(ModelDao &&other) = default;
  virtual ~ModelDao() = default;

  virtual void writeModel(const GmmModel &m)const = 0;
  virtual std::unique_ptr<GmmModel> readModel(const std::string &model_name) = 0;
  virtual std::vector<std::unique_ptr<GmmModel> > readAllModels() = 0;

};



#endif // MODELDAO_HPP
