#ifndef MAINWINDOW_HPP
#define MAINWINDOW_HPP

#include "ui_MainWindow.h"
#include <alize.h>
#include<QFileDialog>
class MainWindow : public QMainWindow
{
  Q_OBJECT

public:
  explicit MainWindow(QWidget *parent = 0);

private slots:
  void on_actionWczytaj_plik_konfiguracyjny_triggered();

  void on_actionZapisz_plik_konfiguracyjny_triggered();

private:
  Ui::MainWindow ui;
  alize::Config conf_;
};

#endif // MAINWINDOW_HPP
