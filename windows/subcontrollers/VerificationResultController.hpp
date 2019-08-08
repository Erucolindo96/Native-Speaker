#ifndef VERIFICATIONRESULTCONTROLLER_HPP
#define VERIFICATIONRESULTCONTROLLER_HPP
#include<QListWidget>
#include<tuple>
/**
 * @brief The VerificationResultController class Klasa, odpowiadająca za wyświetlanie wyników weryfikacji
 * Za pomocą metody setResult można zlecić jej wyświetlenie zadanych wyników, będących mapą String->bool
 * (pokazuje które nagranie dało jaki wynik weryfikacji)
 */
class VerificationResultController
{
public:

  const QString TRUE_ICON_PATH  = "resources/true.png";
  const QString FALSE_ICON_PATH = "resources/false.png";
  VerificationResultController()=default;
  VerificationResultController(const VerificationResultController &other) = default;

  VerificationResultController& operator=
  (const VerificationResultController &other) = default;

  VerificationResultController(VerificationResultController &&other) = default;

  VerificationResultController& operator=
  (VerificationResultController &&other) = default;

  virtual ~VerificationResultController()  = default;
  /**
   * @brief setResultListPtr Ustawia wskazanie do listy, w której klasa będzie wyświetlać wyniki
   * Po dodaniu ptra do klasy wołana jest metoda connectClearResultList().
   * Powinna być załowana jako ostatnia metoda dodająca ptry do używanych elementów ui(tam, gdzie będziemy używać jej klas pochodnych)
   * aby połączenia sygnałów i slotów zostały wykonane poprawnie
   * @param result_list_ptr Wskaźnik do listy, w której klasa będzie wyświetlać wyniki
   */
  void setResultListPtr(QListWidget *result_list_ptr);

  /**
   * @brief setResults Wyświetla podane jako parametr wyniki weryfikacji.
   * Pobiera wyniki weryfikacji w postaci mapy nazwa_pliku->wynik.
   * Używa metod getRecordElem() i getRecordsCnt(), aby uzyskać nazwę i-tego weryfikowanego pliku
   * i przypisać jej, z pomocą mapy, wynik rozpoznawania
   * @param results Wyniki rozpoznawania w postaci mapy nazwa_pliku_weryfikowanego->wynik_weryfikacji
   * @throw std::out_of_range jeśli dla pewnej nazwy pliku, zwracanej przez getRecordElem(),
   * nie istnieje wartość mapy results
   * @see getRecordElem()
   * @see getRecordsCnt()
   */
  void setResults(const std::map<QString, std::pair<bool, double>> &results);

  /**
   * @brief clearResultList Usuwa zawartość listy wyników weryfikacji
   */
  void clearResultList();

protected:
  QListWidget *result_list_;
  /**
   * @brief getRecordsCnt Metoda implementowana w podklasach, zwracająca ilość nagrań weryfikowanych
   * (zawartych w liście nagrań weryfikowanych)
   * @return Ilość nagrań weryfikowanych(zawartych w liście nagrań weryfikowanych)
   */
  virtual int32_t getRecordsCnt()const = 0;
  /**
   * @brief getRecordElem Zwraca ścieżkę i-tego nagrania weryfikowanego(zawartego w liście nagrań weryfikowanych)
   * Implementowane w podklasach
   * @param i Indeks w zbiorze nagrań weryfikowanych
   * @return I-te nagranie weryfikowane(zawarte w liście nagrań weryfikowanych)
   */
  virtual QString getRecordElem(int32_t i) = 0;

  /**
   * @brief getRecordElem Zwraca element QListWidget, która zawiera ścieżki nagrań weryfikowanych.
   * Konieczne, aby przypisywać im ikonki True i False
   * @param i Indeks w zbiorze nagrań weryfikowanych
   * @return Wskaźnik do elementu QListWidget, zawierającej ścieżkę do nagrania weryfikowanego
   */
  virtual QListWidgetItem* getRecordsListWidgetElem(int32_t i) = 0;

  /**
   * @brief connectClearResultList Łączy sygnał pochodzący od list z weryfikowanymi nagraniami, informujący o dodaniu nowego elementu
   * ze slotem usuwającym zawartośc listy rezultatów weryfikowacji
   * Implementowana w klasach pochodnych.
   * Wołana w metodzie setResultListPtr()
   * @see setResultListPtr()
   */
  virtual void connectClearResultList() = 0;
};

#endif // VERIFICATIONRESULTCONTROLLER_HPP
