#include "RecordsFromFilesystemController.hpp"

RecordsFromFilesystemController::RecordsFromFilesystemController(
    QListWidget *record_list, QAbstractButton* add_button,
    QAbstractButton *remove_button)
  :record_list_(record_list), add_button_(add_button), remove_button_(remove_button)
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

