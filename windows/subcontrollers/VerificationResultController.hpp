#ifndef VERIFICATIONRESULTCONTROLLER_HPP
#define VERIFICATIONRESULTCONTROLLER_HPP
#include<QListWidget>
#include<tuple>
#include"resource-container/ResourceContainer.hpp"
/**
 * @brief The VerificationResultController class Klasa, odpowiadająca za wyświetlanie wyników weryfikacji
 * Za pomocą metody setResult można zlecić jej wyświetlenie zadanych wyników, będących mapą String->bool
 * (pokazuje które nagranie dało jaki wynik weryfikacji)
 */
class VerificationResultController
{
public:


  VerificationResultController()=default;
  VerificationResultController(const VerificationResultController &other) = default;

  VerificationResultController& operator=
  (const VerificationResultController &other) = default;

  VerificationResultController(VerificationResultController &&other) = default;

  VerificationResultController& operator=
  (VerificationResultController &&other) = default;

  virtual ~VerificationResultController()  = default;

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


protected:
  QListWidget *result_list_;
  /**
   * @brief getRecordsCnt Metoda implementowana w podklasach, zwracająca ilość nagrań weryfikowanych
   * (zawartych w liście nagrań weryfikowanych)
   * @return Ilość nagrań weryfikowanych(zawartych w liście nagrań weryfikowanych)
   */
  virtual int32_t getRecordsCnt()const = 0;

  /**
   * @brief getRecordElem Zwraca element QListWidget, która zawiera ścieżki nagrań weryfikowanych.
   * Konieczne, aby przypisywać im ikonki True i False
   * Implementowane w podklasach
   * @param i Indeks w zbiorze nagrań weryfikowanych
   * @return Wskaźnik do elementu QListWidget, zawierającej ścieżkę do nagrania weryfikowanego
   */
  virtual QListWidgetItem* getRecordsListWidgetElem(int32_t i) = 0;

};

#endif // VERIFICATIONRESULTCONTROLLER_HPP
