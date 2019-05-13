#ifndef RECORDSFROMFILESYSTEMVERIFICATIONCONTROLLER_HPP
#define RECORDSFROMFILESYSTEMVERIFICATIONCONTROLLER_HPP

#include"windows/subcontrollers/RecordsFromFilesystemController.hpp"
#include"windows/subcontrollers/VerificationResultController.hpp"

class RecordsFromFilesystemVerificationController: public RecordsFromFilesystemController,
    public VerificationResultController
{
  Q_OBJECT
public:

  RecordsFromFilesystemVerificationController()=default;
  RecordsFromFilesystemVerificationController(const RecordsFromFilesystemVerificationController &other) = default;

  RecordsFromFilesystemVerificationController& operator=
  (const RecordsFromFilesystemVerificationController &other) = default;

  RecordsFromFilesystemVerificationController(RecordsFromFilesystemVerificationController &&other) = default;

  RecordsFromFilesystemVerificationController& operator=
  (RecordsFromFilesystemVerificationController &&other) = default;

protected:
  int32_t getRecordsCnt() const override ;
  QString getRecordElem(int32_t i) override;

};

#endif // RECORDSFROMFILESYSTEMVERIFICATIONCONTROLLER_HPP
