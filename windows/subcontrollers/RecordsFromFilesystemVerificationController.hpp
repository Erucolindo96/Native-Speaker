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
   * @brief getRecordElem Zwraca ścieżkę i-tego nagrania, zawartego w liście nagrań pochodzących z filesystemu
   * (RecordsFromFilesystemController::record_list_)
   * @param i Indeks w liście nagrań z filesystemu
   * @return Ścieżka i-tego nagrania, zawartego w liście nagrań z filesystemu(RecordsFromFilesystemController::record_list_)
   * @throw std::out_of_range Jesli nie istnieje ścieżka do nagrania o takim indeksie(np jest większy niż ilośc nagrań)
   */
  QString getRecordElem(int32_t i) override;
  /**
   * @brief connectClearResultList Łączy sygnał kliknięcia w przycisk dodawania i w przycisk usuwania nagrania w listy
   * ze slotem usuwającym zawartośc listy rezultatów weryfikowacji
   * Wołana podczas setResultListPtr()
   * @see setResultListPtr()
   */
  void connectClearResultList()override;

};

#endif // RECORDSFROMFILESYSTEMVERIFICATIONCONTROLLER_HPP
