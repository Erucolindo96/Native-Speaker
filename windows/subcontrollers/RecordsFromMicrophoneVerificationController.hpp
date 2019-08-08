#ifndef RECORDSFROMMICROPHONEVERIFICATIONCONTROLLER_HPP
#define RECORDSFROMMICROPHONEVERIFICATIONCONTROLLER_HPP

#include"windows/subcontrollers/VerificationResultController.hpp"
#include"windows/subcontrollers/RecordsFromMicrophoneController.hpp"
class RecordsFromMicrophoneVerificationController:
    public RecordsFromMicrophoneController,
    public VerificationResultController
{
public:
  RecordsFromMicrophoneVerificationController() = default;

  RecordsFromMicrophoneVerificationController
  (const RecordsFromMicrophoneVerificationController &o) = default;

  RecordsFromMicrophoneVerificationController& operator=
  (const RecordsFromMicrophoneVerificationController &o) = default;

  RecordsFromMicrophoneVerificationController
  (RecordsFromMicrophoneVerificationController &&o) = default;

  RecordsFromMicrophoneVerificationController& operator=
  (RecordsFromMicrophoneVerificationController &&o) = default;

protected:
  /**
   * @brief getRecordsCnt Zwraca ilośc elementów, zawartych w liście nagrań pochodzących z mikrofonu
   * (RecordsFromMicrophoneController::record_list_)
   * @return Ilośc elementów, zawartych w liście nagrań pochodzących z filesystemu
   * (RecordsFromMicrophoneController::record_list_)
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

#endif // RECORDSFROMMICROPHONEVERIFICATIONCONTROLLER_HPP
