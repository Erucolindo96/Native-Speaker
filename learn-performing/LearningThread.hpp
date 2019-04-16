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
 * Przetwarzanie modelu odbywa się "w miejscu" - pobierana jest referencja do wskaźnika do modelu.
 * Metody GmmModel powinny być synchronizowane, aby możliwe było ich wołanie z kilku wątków.
 * Po zakończonym uczeniu emitowany jest sygnał learningComplete().
 * Klasa udostępnia metody, pozwalające poznać stan uczenia, tzn czy wątek uczący skończył pracę i która iteracja jest właśnie wykonywana
 * Można ich bezpiecznie używać w kilku wątkach
 */
class LearningThread: public QObject
{
  Q_OBJECT
public:
  /**
   * @brief LearningThread Tworzy klasę, dodając jej referencję do unique_ptra zawierającego GmmModel
   * Unique_ptr musi być koniecznie utworzony na stercie - inaczej nie będzie działać.
   * Może pochodzić np. z jakiejś kolekcji
   * @param m_ref Referencja do unique_ptra z GmmModelem.
   * Unique_ptr musi być koniecznie utworzony na stercie - inaczej nie będzie działać.
   * Może pochodzić np. z jakiejś kolekcji
   */
  LearningThread(std::unique_ptr<GmmModel> &m_ref);

  /**
   * @brief LearningThread Konstruktor kopiujący, działający w ten sposób, że kopiuje referencję do modelu,
   * natomiast nie kopiuje już działającego wątku ani licznika iteracji.
   * @param other Kopiowany obiekt
   */
  LearningThread(const LearningThread &other);
  LearningThread& operator=(const LearningThread &other)=delete;

  /**
   * @brief LearningThread Konstruktor przesuwający. Kopiuje zarówno referencję do modelu,
   * oraz przesuwa obiekt reprezentujący wątek, oraz licznik iteracji.
   * @param other Przesuwany obiekt
   */
  LearningThread(LearningThread &&other);
  LearningThread& operator=(LearningThread &&other)=delete;

  /**
   * @brief learningOperation Wykonywany przez wątek algorytm uczenia
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
   * @brief getModelRef Zwraca referencję do uczonego modelu
   * Jest synchronizowana mutexem
   * @return Referencja do uczonego modelu
   */
  std::unique_ptr<GmmModel>& getModelRef()const;
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


  ~LearningThread() override = default;


protected:
  mutable std::mutex mutex_;
  std::unique_ptr<std::thread> t_;
  std::unique_ptr<GmmModel> &model_ref_;
  std::atomic<uint32_t> act_iter_;
  std::atomic<bool> is_done_;

};

#endif // LEARNINGTHREAD_HPP
