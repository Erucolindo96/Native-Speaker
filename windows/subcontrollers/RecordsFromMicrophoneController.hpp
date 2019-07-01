#ifndef RECORDSFROMMICROPHONECONTROLLER_HPP
#define RECORDSFROMMICROPHONECONTROLLER_HPP

#include"windows/subcontrollers/RecordsFromFilesystemController.hpp"
#include"windows/AudioRecorderWindow.hpp"
class RecordsFromMicrophoneController: public RecordsFromFilesystemController
{
public:
  RecordsFromMicrophoneController() = default;
  RecordsFromMicrophoneController(const RecordsFromMicrophoneController &o) = default;
  RecordsFromMicrophoneController& operator=
  (const RecordsFromMicrophoneController &o) = default;
  RecordsFromMicrophoneController(RecordsFromMicrophoneController &&o) = default;
  RecordsFromMicrophoneController& operator=
  (RecordsFromMicrophoneController &&o) = default;

  void addingRecord()   override;
};

#endif // RECORDSFROMMICROPHONECONTROLLER_HPP
