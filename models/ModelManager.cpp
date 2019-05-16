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
  //models_.resize(models_from_dao.size());
  std::for_each(models_from_dao.begin(), models_from_dao.end(),
                [this](auto &model_from_dao)->void
  {
    models_[model_from_dao->getName()] = std::move(model_from_dao);
  });

}


void ModelManager::loadModels(const ConfigManager &config_m)
{
  loadModelsFromDatabase(config_m);
}

void ModelManager::addModel(const ConfigManager &config_m,
                            std::unique_ptr<GmmModel> &&model_to_add)
{
  std::string model_name = model_to_add->getName();
  models_[model_name] = std::move(model_to_add);
  saveModelToDatabase(config_m,models_[model_name] );
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
  uint32_t i = 0;
  auto ret = models_.end();
  for(auto iter = models_.begin(); iter !=models_.end(); ++iter, ++i)
  {
    if(i == index)
    {
      ret = iter;
      break;
    }
  }
  return ret->second;
}

std::shared_ptr<GmmModel> ModelManager::operator[](const std::string &model_name)
{
  return models_.at(model_name);
}

std::vector<std::string> ModelManager::getModelsNames()const
{
  std::vector<std::string> ret;
  std::for_each(models_.begin(), models_.end(),
                [&ret](auto map_elem)->void
  {
    ret.push_back(map_elem.second->getName());
  });
  return ret;
}


