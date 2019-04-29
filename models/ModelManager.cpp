#include "ModelManager.hpp"

void ModelManager::saveModelToDatabase(const ConfigManager &config_m,
                                       std::shared_ptr<GmmModel> model_to_save)
{
  dao_.setModelsDir(config_m.getModelFolder());
  dao_.setVectSize(config_m.getVectSize());
  dao_.writeModel(*model_to_save);
}

void ModelManager::loadModelsFromDatabase(const ConfigManager &config_m)
{
  models_.clear();
  dao_.setModelsDir(config_m.getModelFolder());
  dao_.setVectSize(config_m.getVectSize());
  auto models_from_dao = dao_.readAllModels();
  models_.resize(models_from_dao.size());
  std::move(models_from_dao.begin(), models_from_dao.end(), models_.begin());

}


void ModelManager::loadModels(const ConfigManager &config_m)
{
  loadModelsFromDatabase(config_m);
}

void ModelManager::addModel(const ConfigManager &config_m,
                            std::unique_ptr<GmmModel> &&model_to_add)
{
  models_.push_back(std::move(model_to_add));
  saveModelToDatabase(config_m, models_.back());
  loadModels(config_m);
}

uint32_t ModelManager::getModelsCnt()const
{
  return models_.size();
}


std::shared_ptr<GmmModel> ModelManager::operator[](uint32_t index)
{
  if(index >= models_.size() )
  {
    throw std::out_of_range("File:" + std::string(__FILE__) + " Line :" + std::to_string(__LINE__) +
                            ": index added to ModelManager::operator[] is out of bound");
  }
  return models_[index];
}


