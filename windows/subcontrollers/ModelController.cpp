#include "ModelController.hpp"

ModelController::ModelController(QToolBox *ptr):
  ModelManager::ModelManager(), toolbox_ptr_(ptr)
{}

void ModelController::setToolBoxPtr(QToolBox *ptr)
{
  toolbox_ptr_ = ptr;
}

void ModelController::refreshDisplayedModels()
{
  normalizeActPage();
  removeToolBoxItems();
  auto first_m = models_.cbegin(), last_m=models_.cbegin()+MODELS_ON_PAGE-1;
  first_m+=(act_page_-1)*MODELS_ON_PAGE;
  last_m+=(act_page_-1)*MODELS_ON_PAGE;
  for(auto i = first_m; i != last_m; ++i)
  {
    GmmModel& model = *(*i);
    toolbox_ptr_->addItem(new GmmModelWidget(toolbox_ptr_, model.getName().c_str(),
                                             model.getDistribCount(),
                                             model.getType(), ""),model.getName().c_str() );
  }

}

void ModelController::nextPage()
{
  if(act_page_+1 > MAX_PAGE())
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

void ModelController::removeToolBoxItems()
{
  for(int32_t i = 0; i < toolbox_ptr_->count(); ++i)
  {
    toolbox_ptr_->removeItem(i);
  }
}
/*
std::pair<uint32_t, uint32_t> ModelController::getIndexFirstAndLastModelAtPage(
    uint32_t act_page)const
{
  uint32_t all_models_cnt = models_.size(), first_elem = 0,
      last_elem = MODELS_ON_PAGE;
  if((act_page-1) >= all_models_cnt/MODELS_ON_PAGE)
  {
    throw std::runtime_error("TODO");
  }
  first_elem = (act_page-1) * MODELS_ON_PAGE;
  last_elem = first_elem + MODELS_ON_PAGE -1;
  return std::pair<uint32_t, uint32_t>(first_elem, last_elem);
}
*/
uint32_t ModelController::MAX_PAGE()const
{
  return (models_.size()/MODELS_ON_PAGE) + 1;
}

