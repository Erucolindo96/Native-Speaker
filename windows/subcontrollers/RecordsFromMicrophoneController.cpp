#include "RecordsFromMicrophoneController.hpp"

void RecordsFromMicrophoneController::addingRecord()
{
  auto window = std::make_unique<AudioRecorderWindow>();
  window->exec();
  auto recs = window->getRegisteredRecords();
  for(Record &r: recs)
  {
    record_list_->addItem(r.getRecordInfo().absoluteFilePath());
  }
}
