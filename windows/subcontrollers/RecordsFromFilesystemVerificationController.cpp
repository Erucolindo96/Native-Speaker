#include "RecordsFromFilesystemVerificationController.hpp"

int32_t RecordsFromFilesystemVerificationController::getRecordsCnt() const
{
  return record_list_->count();
}


QListWidgetItem* RecordsFromFilesystemVerificationController::
getRecordsListWidgetElem(int32_t i)
{
  if(record_list_->item(i) == nullptr)
  {
    throw std::out_of_range("File: " + std::string(__FILE__) + " Line :" + std::to_string(__LINE__) +
        ": try to get record elem out of bound!");
  }
  return record_list_->item(i);
}



