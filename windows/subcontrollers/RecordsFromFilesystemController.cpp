#include "RecordsFromFilesystemController.hpp"

RecordsFromFilesystemController::RecordsFromFilesystemController()
  :record_list_(nullptr), add_button_(nullptr), remove_button_(nullptr)
{

}


void RecordsFromFilesystemController::setRemoveButtonPtr(QAbstractButton *ptr)
{
  if(remove_button_ != nullptr)
  {
    remove_button_->disconnect(this, SLOT(removingRecord()));
  }
  remove_button_ = ptr;
  connect(remove_button_,SIGNAL(released()), this, SLOT(removingRecord()) );

}

void RecordsFromFilesystemController::setAddButtonPtr(QAbstractButton *ptr)
{
  if(add_button_!=nullptr)
  {
    add_button_->disconnect(this, SLOT(addingRecord()));
  }
  add_button_ = ptr;
  connect(add_button_,SIGNAL(released()), this, SLOT(addingRecord()) );

}

void RecordsFromFilesystemController::setRecordListPtr(QListWidget *ptr)
{
  record_list_ = ptr;
}

std::vector<Record> RecordsFromFilesystemController::getActualRecords()const
{
  std::vector<Record> ret;
  for(int32_t i = 0; i < record_list_->count(); ++i)
  {
    Record rec;
    rec.setPath(record_list_->item(i)->text());
    ret.push_back(rec);
  }
  return ret;
}



//void RecordsFromFilesystemController::bindSlots()
//{
//  connect(add_button_,SIGNAL(released()), this, SLOT(addingRecord()) );
//  connect(remove_button_,SIGNAL(released()), this, SLOT(removingRecord()) );
//}

void RecordsFromFilesystemController::addingRecord()
{
  const QString title = "Add record", def_dir, filters=
      "Records (*.wav *.mp3);;All Files (*)";
  QStringList record_files = QFileDialog::getOpenFileNames(nullptr,title,def_dir, filters);
  if(record_files.empty())
  {
    return;
  }
  record_list_->addItems(record_files);
}

void RecordsFromFilesystemController::removingRecord()
{
   auto selected_items = record_list_->selectedItems();
   for(auto item:selected_items)
   {
      delete item;
   }
}

