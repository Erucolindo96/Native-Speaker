#include "RecordsInSampleBaseController.hpp"


RecordsInSampleBaseController::RecordsInSampleBaseController():
  RecordsFromFilesystemController(),
  model_box_ptr_(nullptr), sample_base_(nullptr)
{}

void RecordsInSampleBaseController::
setRemoveButtonPtr(QAbstractButton *ptr)
{
  RecordsFromFilesystemController::setRemoveButtonPtr(ptr);
}

void RecordsInSampleBaseController::setComboBoxPtr(QComboBox *ptr)
{

  if(model_box_ptr_!=nullptr)
  {
    model_box_ptr_->disconnect(this, SLOT(displayRecordsOfModel(QString)));
  }
  model_box_ptr_ = ptr;
  connect(model_box_ptr_,SIGNAL(currentIndexChanged(const QString&)),
          this, SLOT(displayRecordsOfModel(const QString&)) );

}

void RecordsInSampleBaseController::setRecordListPtr(QListWidget *ptr)
{
  RecordsFromFilesystemController::setRecordListPtr(ptr);
}

void RecordsInSampleBaseController::
setSampleBaseManPtr(RecBaseManager *ptr)
{
  sample_base_ = ptr;
}



void RecordsInSampleBaseController::
setModelsList(const std::vector<std::string> &models)
{
  model_box_ptr_->clear();
  std::for_each(models.begin(), models.end(),
                [this](auto name)->
  void
  {
    model_box_ptr_->addItem(name.c_str());
  });
}

void RecordsInSampleBaseController::
displayRecordsOfModel(const QString &model_name)
{
  record_list_->clear();
  auto model_recs = sample_base_->getRecordsOfModel(model_name.toStdString());

  std::for_each(model_recs.begin(), model_recs.end(),
                [this](auto rec)->
  void
  {
    record_list_->addItem(rec.getRecordInfo().
                                          absoluteFilePath());
  });
}

void RecordsInSampleBaseController::removingRecord()
{
  auto recs_to_remove = record_list_->selectedItems();
  std::for_each(recs_to_remove.begin(), recs_to_remove.end(),
                [this](auto list_elem)->
  void
  {
    Record r;
    r.setPath(list_elem->text());
    r.remove();
  });
  RecordsFromFilesystemController::removingRecord();//usun jeszcze z samej listy elementy
}

