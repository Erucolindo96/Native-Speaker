#ifndef LEARNINGPERFORMER_HPP
#define LEARNINGPERFORMER_HPP
#include<QObject>
#include"models/gmmmodel.hpp"
#include"models/learning_algo.hpp"
#include<thread>
#include<mutex>
#include<memory>
#include<list>
#include"learn-performing/LearningThread.hpp"
#include<algorithm>

/**
 * @brief The LearningPerformer class Klasa zarządzająca wątkami uczącymi.
 * Zleca uczenie modelu na podstawie zadanych parametrów.
 */
class LearningPerformer:public QObject
{
  Q_OBJECT
public:
  LearningPerformer() = default;

  LearningPerformer(const LearningPerformer &other);
  /**
   * @brief operator = Operator nie wywołuje żadnej operacji na obiekcie.
   * Zwraca tylko referencję do obiektu.
   * Istnieje tylko po to, aby nie zaburzać tworzenia defaultowych operatorów= w klasach go używających
   * @param other Inny LearningPerformer
   * @return Referencje do obiektu this
   */
  LearningPerformer& operator=(const LearningPerformer &other);

  LearningPerformer(LearningPerformer &&other);

  /**
   * @brief operator = Operator nie wywołuje żadnej operacji na obiekcie.
   * Zwraca tylko referencję do obiektu
   * Istnieje tylko po to, aby nie zaburzać tworzenia defaultowych operatorów= w klasach go używających
   * @param other Inny LearningPerformer
   * @return Referencje do obiektu this
   */
  LearningPerformer& operator=(LearningPerformer &&other);

  /**
   * @brief startLearning Uruchamia uczenie wskazanego modelu za pomocą zadanych wektorów cech
   * @param m Uczony model
   * @param algo Algorytm uczący
   * @param f_vec Dane uczące
   * @param iter_cnt Ilośc iteracji algorytmu
   * @return Referencję do obiektu uczącego dany model. Pozwala zobaczyć stan uczenia.
   * @throw LearningModelWithoutFeatures jeżeli f_vec nie zawiera żadnych elementów
   * @throw RerunningLearningThread jeżeli zlecamy uczenie modelu, którego wątek uczący właśnie pracuje.
   * Powinnismy poczekać, aż zakończy pracę, i dopiero wtedy ją wznawiać
   *
   */
  void startLearning(std::shared_ptr<GmmModel> m,
                                      std::unique_ptr<LearningAlgo> &&algo,
                                      std::vector<alize::Feature> &f_vec,
                                      uint32_t iter_cnt );

  ~LearningPerformer() override= default;


protected:
  std::list<LearningThread> l_thread_list_;
  //mutable std::mutex m_;
  void removeDoneThreads();
  /**
   * @brief checkForRunningThread Sprawdza, czy nie uruchomiono uczenia aktualnie uczonego modelu
   * @param m Model weryfikowany
   * @throw RerunningLearningThread jeśli właśnie trwa uczenie danego modelu w innym wątku
   */
  void checkForRunningThread(std::shared_ptr<GmmModel> m);

};

#endif // LEARNINGPERFORMER_HPP
