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
   * @brief getRecordElem Zwraca ścieżkę i-tego nagrania, zawartego w liście nagrań pochodzących z filesystemu
   * (RecordsFromMicrophoneController::record_list_)
   * @param i Indeks w liście nagrań z filesystemu
   * @return Ścieżka i-tego nagrania, zawartego w liście nagrań z filesystemu(RecordsFromFilesystemController::record_list_)
   * @throw std::out_of_range Jesli nie istnieje ścieżka do nagrania o takim indeksie(np jest większy niż ilośc nagrań)
   */
  QString getRecordElem(int32_t i) override;


  QListWidgetItem* getRecordsListWidgetElem(int32_t i)override;

  /**
   * @brief connectClearResultList Łączy sygnał kliknięcia w przycisk dodawania i w przycisk usuwania nagrania w listy
   * ze slotem usuwającym zawartośc listy rezultatów weryfikowacji
   * Wołana podczas setResultListPtr()
   * @see setResultListPtr()
   */
  void connectClearResultList()override;


};

#endif // RECORDSFROMMICROPHONEVERIFICATIONCONTROLLER_HPP
