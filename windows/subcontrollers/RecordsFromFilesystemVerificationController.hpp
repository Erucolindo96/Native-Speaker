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
  ~RecordsFromFilesystemVerificationController() override =default;

protected:
  /**
   * @brief getRecordsCnt Zwraca ilośc elementów, zawartych w liście nagrań pochodzących z filesystemu
   * (RecordsFromFilesystemController::record_list_)
   * @return Ilośc elementów, zawartych w liście nagrań pochodzących z filesystemu
   * (RecordsFromFilesystemController::record_list_)
   */
  int32_t getRecordsCnt() const override ;
  /**
   * @brief getRecordElem Zwraca element QListWidget, która zawiera ścieżki nagrań weryfikowanych.
   * Konieczne, aby przypisywać im ikonki True i False
   * @param i Indeks w zbiorze nagrań weryfikowanych
   * @return Wskaźnik do elementu QListWidget, zawierającej ścieżkę do nagrania weryfikowanego
   */
  QListWidgetItem* getRecordsListWidgetElem(int32_t i)override;



};

#endif // RECORDSFROMFILESYSTEMVERIFICATIONCONTROLLER_HPP
