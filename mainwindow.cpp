#include "mainwindow.hpp"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent)
{
    ui.setupUi(this);
}

void MainWindow::on_actionWczytaj_plik_konfiguracyjny_toggled(bool arg1)
{
    QString fileName = QFileDialog::getOpenFileName(this,
                                                        tr("OpenImage"),
                                                        "/home/erucolindo",
                                                        nullptr);
    std::cout << fileName.toStdString();
}
