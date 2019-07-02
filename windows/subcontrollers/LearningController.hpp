#ifndef LEARNINGCONTROLLER_HPP
#define LEARNINGCONTROLLER_HPP

#include"learn-performing/LearningPerformer.hpp"
#include"learn-performing/LearningThreadWidget.hpp"
#include"models/ModelManager.hpp"
#include"configuration/ConfigManager.hpp"
#include<QComboBox>
#include<QVBoxLayout>
#include<thread>
#include<mutex>
#include<QListWidget>

/**
 * @brief The LearningController class Klasa obsługująca wyświetlanie statusu uczenia modeli w menu głównym
 * Obsługuje wyświetlanie postępu uczenia aktualnie uczonych modeli.
 * Osobny wątek aktualizuje tabelę Widgetów, wyświetlanych w Menu głównym. Aktualizuje informację o aktualnej iteracji
 * Dodaje widgety opisujące nowe wątki uczące
 * Oraz usuwa widgety nieaktualne(których wątki uczące się zakonczyły)
 */

class LearningController: public LearningPerformer
{
  Q_OBJECT

public:

  LearningController() = default;
  LearningController(const LearningController & other) = default;
  LearningController& operator=(const LearningController & other) = default;
  LearningController(LearningController && other) = default;
  LearningController& operator=(LearningController && other) = default;

  /**
   * @brief setComboBoxPtr Ustawia wskazanie do obsługiwanego przez klasę comboBoxa
   * Po przypisaniu wskazania łączone są sygnały od comboBoxa ze slotami klasy
   * @param ptr Wskazanie do obsługiwanego comboBoxa
   */
  void setComboBoxPtr(QComboBox *ptr);
  /**
   * @brief setProgressBarPtr Ustawia wskazanie do obsługiwanego przezz klasę progressBara
   * @param ptr Wskazanie do osbługiwanego przez klasę progressBara
   */
  void setProgressBarPtr(QProgressBar *ptr);

  /**
   * @brief setModelManagerPtr Ustawia wskazanie do ModelManagera.
   * Konieczne, aby zapisywać każdorazowo model po ukonczeniu uczenia - ModelManager kieruje zapisem modeli do pliku
   * @param ptr Wskazanie do MainWindow
   */
  void setModelManagerPtr(ModelManager *ptr);

  /**
   * @brief setConfigManagerPtr Ustawia wskazanie do Konfiguracji.
   * Konieczne, aby zapisywać każdorazowo model po ukończeniu uczenia - ModelManager pobiera z konfiguracji ściezkę do bazy modeli
   * @param ptr Wskazanie do konfiguracji
   */
  void setConfigManagerPtr(ConfigManager *ptr);



  /**
   * @brief startLearning Uruchamia uczenie modelu
   * Wykonuje to, co LearningPerformer, ale dodatkowo wstawia nazwę uczonego modelu do comboBoxa
   * oraz łączy sygnał ukończenia iteracji pochodzący od uczącego wątku, z odpowiednim slotem klasy
   * @param m Uczony Model
   * @param algo Algorytm którym będzie uczony model
   * @param f_vec Wektory cech, którymi będziemy uczyc model
   * @param iter_cnt Ilośc iteracji uczenia
   */
  void startLearning(std::shared_ptr<GmmModel> m,
                                        std::unique_ptr<LearningAlgo> &&algo,
                                        std::vector<alize::Feature> &f_vec,
                                        uint32_t iter_cnt );


  ~LearningController() override = default;
protected:

  QComboBox *l_thread_combo_box_;
  QProgressBar *l_thread_prog_bar_;
  ModelManager *model_man_;
  ConfigManager *conf_man_;

  /**
   * @brief removeDoneThreads Usuwa ukończone wątki z listy wątków uczących.
   * Dodatkowo usuwa z comboBoxa wątki ukończone(aby nie mogly być już wyświetlane)
   */
  void removeDoneThreads();
  /**
   * @brief findAndRemoveFromComboBox Usuwa z comboBoxa element o danej nazwie
   * @param model_name Nazwa modelu, którego element chcemy usunąć z comboBoxa
   */
  void findAndRemoveFromComboBox(const QString &model_name);
  /**
   * @brief connectSignalsAndSlots Podłącza sygnały, pochodzące od comboBoxa, z odpowiednimi slotami klasy
   */
  void connectSignalsAndSlots();

protected slots:
  /**
   * @brief actualizeProgressBarByLearningThread Obsługa sygnały iterationComplete, pochodząca od wątku uczącego
   * Sprawdza, czy w combo boxie jest aktualnie wyświetlany model, którego uczy dany wątek uczący.
   * Jeśli tak, to aktualizuje iterację uczenia w progressBarze
   * @param model_name Nazwa modelu, którego iteracja uczenia się właśnie zakończyła
   * @param act_iter Iteracja uczenia modelu, która się właśnie zakończyła
   * @param iter_cnt Ilość wszystkich iteracji uczenia danego modelu
   */
  void actualizeProgressBarByLearningThread(const QString model_name,
                                            const qint32 act_iter,
                                            const qint32 iter_cnt);
  /**
   * @brief actualizeProgressBarByMainThread Aktualizuje progressBar po zmianie wybranego modelu w comboBoxie.
   * Wyświetla w progress barze iterację uczenia modelu, wskazanego w comboBoxie
  */
  void actualizeProgressBarByMainThread();

  /**
   * @brief saveModelLearnedFromLearningThread Zapisuje model, którego uczenie zostało właśnie ukończone
   * @param m Model, którego uczenie zostało ukonczone
   */
  void saveModelLearnedFromLearningThread(QObject *m);

};


#endif // LEARNINGCONTROLLER_HPP
