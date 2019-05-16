#include "ModelController.hpp"

ModelController::ModelController(QToolBox *ptr, const int32_t models_on_page):
  ModelManager::ModelManager(), MODELS_ON_PAGE(models_on_page), act_page_(0),
  toolbox_ptr_(ptr)
{}

void ModelController::setToolBoxPtr(QToolBox *ptr)
{
  toolbox_ptr_ = ptr;
}


uint32_t ModelController::getActPage()const
{
  return act_page_;
}

void ModelController::removeToolBoxItems()
{
  while(toolbox_ptr_->count() != 0)
  {
    QWidget* to_delete = toolbox_ptr_->widget(0);
    toolbox_ptr_->removeItem(0);
    delete to_delete;
  }
}

void ModelController::refreshDisplayedModels()
{
  normalizeActPage();
  removeToolBoxItems();

  uint32_t first_m = (act_page_)*MODELS_ON_PAGE;
  uint32_t last_m = (act_page_+1)*MODELS_ON_PAGE-1;
  auto models_names = getModelsNames();
  for(auto i = first_m; (i <= last_m)&&(i<models_names.size()); ++i)
  {
    auto act_model_name = models_names[i];
    toolbox_ptr_->addItem(new GmmModelWidget(nullptr, act_model_name.c_str(),
                                             models_[act_model_name]->getDistribCount(),
                                             models_[act_model_name]->getType(), ""),
                          act_model_name.c_str() );
  }

}

void ModelController::nextPage()
{
  if(act_page_ + 1 > MAX_PAGE())
  {
    return;
  }
  ++act_page_;
  refreshDisplayedModels();
}

void ModelController::prevPage()
{
  if(act_page_-1 < MIN_PAGE)
  {
    return;
  }
  --act_page_;
  refreshDisplayedModels();
}

void ModelController::normalizeActPage()
{
  if(act_page_ > MAX_PAGE())
  {
    act_page_ = MAX_PAGE();
  }
}

int32_t ModelController::MAX_PAGE()const
{
  uint32_t max_page = (models_.size()/MODELS_ON_PAGE);
  return max_page ;
}

