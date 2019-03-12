﻿#ifndef MAINWINDOW_HPP
#define MAINWINDOW_HPP

#include "ui_MainWindow.h"
#include <alize.h>
#include<QFileDialog>
#include<QMessageBox>
#include<QProgressBar>
#include"windows/CreateModelWindow.hpp"
#include"windows/SetParameterWindow.hpp"
#include"features/FeatureReader.hpp"
#include"features/MfccConverter.hpp"
#include"dao/FileModelDao.hpp"
#include"models/diagonal_model.hpp"
#include"models/learning_algo.hpp"
#include"models/verificator.hpp"
#include"windows/subcontrollers/ModelController.hpp"
#include"configuration/ConfigValidator.hpp"

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
  void initMainWindow();
  void on_actionWczytaj_plik_konfiguracyjny_triggered();
  void on_actionZapisz_plik_konfiguracyjny_triggered();
  void on_actionUtw_rz_model_triggered();

  void on_actionRead_Configuration_File_triggered();
  void on_actionSave_Configuration_File_triggered();
  void on_action_CreateModel_triggered();
  void on_actionAdd_Configuration_Parameter_triggered();

  /**
   * @brief saveModelFromCreateModelWindow Zapisuje utworzony przez CreateModelWindow model mówcy.
   *
   */
  void saveModelFromCreateModelWindow();
  /**
   * @brief saveParamFromSetParameterWindow Zapisuje parametr wprowadzony przez uzytkownika w oknie SetParameterWindow
   */
  void saveParamFromSetParameterWindow();





  void on_toolButton_refresh_released();

  void on_commandLinkButton_next_models_released();

  void on_commandLinkButton_prev_models_released();

protected:
  const int32_t MODELS_ON_PAGE =5 ;
  Ui::MainWindow ui_;
  ConfigManager conf_;
  ModelController models_;
  std::unique_ptr<LearningAlgo> models_learning_algo_;

  /**
   * @brief checkConfiguration Sprawdza, czy w programie znajduje się
   * pełna konfiguracja(wszystkie podstawowe parametry), i w razie braku parametrów
   * prosi o uzupełnienie brakującego
   * @return Czy wszystkie niezbędne dla aplikacji parametry są obecne w konfiguracji
   */
  bool checkConfiguration()const;

  void actualizePage();

};

#endif // MAINWINDOW_HPP
