#ifndef MAINWINDOW_HPP
#define MAINWINDOW_HPP

#include "ui_MainWindow.h"
#include <alize.h>
#include<QFileDialog>
#include<QMessageBox>
#include"main/windows/CreateModelWindow.hpp"
#include"features/FeatureReader.hpp"
#include"features/MfccConverter.hpp"
#include"dao/FileModelDao.hpp"
#include"models/diagonal_model.hpp"
#include"models/learning_algo.hpp"
#include"models/verificator.hpp"
#include"models/ModelManager.hpp"

#include"configuration/ConfigManager.hpp"
#include<vector>
#include<thread>
#include<mutex>

class MainWindow : public QMainWindow
{
  Q_OBJECT

public:
  explicit MainWindow(QWidget *parent = 0);



private slots:
  void on_actionWczytaj_plik_konfiguracyjny_triggered();

  void on_actionZapisz_plik_konfiguracyjny_triggered();

  void on_actionUtw_rz_model_triggered();

  void on_actionRead_Configuration_File_triggered();

  void on_actionSave_Configuration_File_triggered();

  void on_action_CreateModel_triggered();

  void saveModelFromCreateModelWindow();

protected:
  Ui::MainWindow ui_;
  ConfigManager conf_;
//  std::vector<std::unique_ptr<GmmModel>> models_;
  ModelManager models_;
  std::unique_ptr<LearningAlgo> models_learning_algo_;

  /**
   * @brief checkConfiguration Sprawdza, czy w programie znajduje się
   * pełna konfiguracja(wszystkie podstawowe parametry), i w razie braku parametrów
   * prosi o uzupełnienie brakującego
   * @return Czy wszystkie niezbędne dla aplikacji parametry są obecne w konfiguracji
   */
  bool checkConfiguration()const;
  //std::mutex m_;

};

#endif // MAINWINDOW_HPP
