#include "ModelManager.hpp"

void ModelManager::saveModelToDatabase(const ConfigManager &config_m,
                                       std::unique_ptr<GmmModel> &model_to_save)
{
  dao_.setModelsDir(config_m.getModelFolder());
  dao_.setVectSize(config_m.getVectSize());
  dao_.writeModel(*model_to_save);
}

void ModelManager::loadModelsFromDatabase(const ConfigManager &config_m)
{
  dao_.setModelsDir(config_m.getModelFolder());
  dao_.setVectSize(config_m.getVectSize());
  models_ = dao_.readAllModels();
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
}

uint32_t ModelManager::getModelsCnt()const
{
  return models_.size();
}


std::unique_ptr<GmmModel>& ModelManager::operator[](uint32_t index)
{
  return models_[index];
}


