#include "RecordsFromFilesystemVerificationController.hpp"

int32_t RecordsFromFilesystemVerificationController::getRecordsCnt() const
{
  return record_list_->count();
}
QString RecordsFromFilesystemVerificationController::getRecordElem(int32_t i)
{
  return record_list_->item(i)->text();
}
