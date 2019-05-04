#ifndef LEARNINGCONTROLLER_HPP
#define LEARNINGCONTROLLER_HPP

#include"learn-performing/LearningPerformer.hpp"
#include"learn-performing/LearningThreadWidget.hpp"
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
  using thread_tuple = std::tuple<std::shared_ptr<GmmModel>, uint32_t, uint32_t>;//model_ptr, act_iter, iter_cnt
  using thread_tuple_vec = std::vector<thread_tuple>;

  LearningController() = default;
  LearningController(const LearningController & other) = default;
  LearningController& operator=(const LearningController & other) = default;
  LearningController(LearningController && other) = default;
  LearningController& operator=(LearningController && other) = default;



  /**
   * @brief displayThreadLoop Pętla, w której wykonuje się wątek aktualizujący widgety
   * Wątek przechodzi po liście LearningThreadów, i na jej podstawie aktualizuje
   * pasek postępu w widgetach, oraz usuwa te widgety, których wątki uczące się już zakonczyły
   */
  void displayThreadLoop();
  /**
   * @brief runDisplayThread Uruchamia wątek aktualizujący widgety
   * @throw RerunningThread jeśli wątek już został uruchomiony
   */
  void runDisplayThread();


  void setComboBoxPtr(QComboBox *ptr);
  void setProgressBarPtr(QProgressBar *ptr);



  /**
   * @brief setListWidgetPtr Ustawia wskazanie do tabeli, w której maja być wyświetlanie widgety opisujące postęp uczenia modeli
   * @param ptr Wskaźnik do tabelki
   */
  //void setListWidgetPtr(QListWidget *ptr);
  /**
   * @brief getListWidgetPtr Zwraca wskazanie do tabelki, w której maja być wyświetlanie widgety opisujące postęp uczenia modeli
   * @return Wskaźnik do tabelki
   */
  //QListWidget* getListWidgetPtr()const;


  ~LearningController() override = default;
protected:
  //QListWidget* l_thread_list_widget_ptr_;
  QComboBox *l_thread_combo_box_;
  QProgressBar *l_thread_prog_bar_;
  std::unique_ptr<std::thread> t_;
  shared_ptr<GmmModel> act_displayed_learning_;


  void actualizeComboBox();
  void actualizeProgressBar();
  void connectSignalsAndSlots();

public slots:
  void updateDisplayedLearning();
};

//Q_DECLARE_METATYPE(std::shared_ptr<GmmModel>)
//Q_DECLARE_METATYPE(GmmModel*)

#endif // LEARNINGCONTROLLER_HPP
