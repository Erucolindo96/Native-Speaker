#ifndef MAINWINDOW_HPP
#define MAINWINDOW_HPP

#include "ui_mainwindow.h"
#include <QFileDialog>
#include <iostream>
#include <QtGlobal>
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);

private slots:
    void on_actionWczytaj_plik_konfiguracyjny_toggled(bool arg1);

private:
    Ui::MainWindow ui;
};

#endif // MAINWINDOW_HPP
