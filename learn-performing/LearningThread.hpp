#ifndef LEARNINGTHREAD_HPP
#define LEARNINGTHREAD_HPP
#include<QObject>
#include"models/gmmmodel.hpp"
#include"models/learning_algo.hpp"
#include<thread>
#include<mutex>
#include<memory>
#include<atomic>

/**
 * @brief The LearningThread class Klasa odpowiedzialna za uruchomienie uczenia dla zadanego modelu
 * Przetwarzanie modelu odbywa się "w miejscu" - pobierana jest wskazanie shared_ptr do modelu.
 * Metody GmmModel powinny być synchronizowane, aby możliwe było ich wołanie z kilku wątków(np przez wątek wyświetlający parametry modelu w okienku).
 * Klasa udostępnia metody, pozwalające poznać stan uczenia, tzn czy wątek uczący skończył pracę i która iteracja jest właśnie wykonywana
 * Można ich bezpiecznie używać w kilku wątkach
 */
class LearningThread: public QObject
{
  Q_OBJECT

public:
  /**
   * @brief LearningThread Tworzy klasę, dodając shared_ptra zawierającego GmmModel
   * Może pochodzić np. z jakiejś kolekcji
   * @param m_ref Referencja do unique_ptra z GmmModelem.
   * Może pochodzić np. z jakiejś kolekcji
   */
  explicit LearningThread(std::shared_ptr<GmmModel> m_ref = nullptr);

  /**
   * @brief LearningThread Konstruktor kopiujący, działający w ten sposób, że kopiuje shared_ptr do modelu,
   * natomiast nie kopiuje już działającego wątku ani licznika iteracji.
   * @param other Kopiowany obiekt
   */
  LearningThread(const LearningThread &other);

  LearningThread& operator=(const LearningThread &other)=delete;

  /**
   * @brief LearningThread Konstruktor przesuwający. Kopiuje zarówno shared_ptr do modelu,
   * oraz przesuwa obiekt reprezentujący wątek, oraz licznik iteracji.
   * @param other Przesuwany obiekt
   */
  LearningThread(LearningThread &&other);
  /**
   * @brief operator = Operator= przesuwający. Kopiuje zarówno shared_ptr do modelu,
   * oraz przesuwa obiekt reprezentujący wątek, oraz licznik iteracji.
   * @param other Przesuwany obiekt
   * @return Referencje do samego siebie
   */
  LearningThread& operator=(LearningThread &&other);

  /**
   * @brief learningOperation Wykonywany przez wątek algorytm uczenia
   * Po każdej wykonanej iteracji uczenia emitowany jest sygnał iterationComplete(const LearningThread&)
   * @param t Referencja do obiektu wykonującego uczenie
   * @param algo Algorytm uczący
   * @param f_vec Uczące wektory cech
   * @param iters Liczba iteracji uczenia
   * @throw LearningModelWithoutFeatures Jeżeli f_vec jest pusty
   *
   */
  static void learningOperation(LearningThread &t, std::unique_ptr<LearningAlgo> &&algo,
                  std::vector<alize::Feature> f_vec, uint32_t iters);
  /**
   * @brief run Uruchamia wątek, wykonujący uczenie modelu wskazywanego przez klasę
   * @param algo Algorytm uczący
   * @param f_vec Uczące wektory cech
   * @param iters Ilość iteracji uczenia
   * @throw LearningModelWithoutFeatures Jeżeli f_vec jest pusty
   * @throw RerunningLearningThread jesli już poprzednio uruchomiono wątek i próbuje się to zrobić jeszcze raz
   */
  void run(std::unique_ptr<LearningAlgo> &&algo,
           std::vector<alize::Feature> f_vec, uint32_t iters);

  /**
   * @brief getModelPtr Zwraca shared_ptr do uczonego modelu
   * Jest synchronizowana mutexem
   * @return Shared_ptr do uczonego modelu
   */
  std::shared_ptr<GmmModel> getModelPtr()const;
  /**
   * @brief incrementIter Zwiększa licznik iteracji o 1
   * Jest synchronizowana mutexem
   */
  void incrementIter();

  /**
   * @brief isDone Zwraca informację, czy wątek uczący skonczył pracę
   * Jest synchronizowana mutexem
   * @return True jeśli wątek zakończył uczenie,
   * false jeśli nie, lub gdy nie został w ogóle uruchomiony
   */
  bool isDone()const;
  /**
   * @brief getIter Zwraca numer aktualnej iteracji
   * Jest synchronizowana mutexem
   * @return Numer aktualnej iteracji
   */
  uint32_t getIter()const;

  /**
   * @brief setIterCnt Ustawia przez ile iteracji wątek uczący ma uczyć model
   * @param iter_cnt Ilośc iteracji uczenia
   */
  void setIterCnt(uint32_t iter_cnt);

  /**
   * @brief getIterCnt Zwraca ustawioną uprzednio ilość iteracji uczenia
   * @return Ilośc iteracji uczenia
   */
  uint32_t getIterCnt()const;

  ~LearningThread() override=default;


protected:
  mutable std::mutex mutex_;
  std::unique_ptr<std::thread> t_;
  std::shared_ptr<GmmModel> model_ref_;
  std::atomic<uint32_t> act_iter_, iter_cnt_;
  std::atomic<bool> is_done_;

  /**
   * @brief setDone Ustawia flagę is_done_ na true.
   * Jest synchronizowana mutexem
   */
  void setDone();

  signals:
  void iterationComplete(const QString model_name, const qint32 act_iter, const qint32 iter_cnt);
  void learningComplete(QObject *model_ptr);


};


#endif // LEARNINGTHREAD_HPP
