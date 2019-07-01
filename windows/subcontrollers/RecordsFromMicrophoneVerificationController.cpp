#include "RecordsFromMicrophoneVerificationController.hpp"



int32_t RecordsFromMicrophoneVerificationController::getRecordsCnt() const
{
  return record_list_->count();
}

QString RecordsFromMicrophoneVerificationController::getRecordElem(int32_t i)
{
  if(record_list_->item(i) == nullptr)
  {
    throw std::out_of_range("File: " + std::string(__FILE__) + " Line :" + std::to_string(__LINE__) +
        ": try to get record elem out of bound!");
  }
  return record_list_->item(i)->text();
}

void RecordsFromMicrophoneVerificationController::connectClearResultList()
{
  connect(add_button_, SIGNAL(released()), result_list_, SLOT(clear()));
  connect(remove_button_, SIGNAL(released()), result_list_, SLOT(clear()));
}

