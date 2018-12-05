#include "MainWindow.hpp"
using namespace alize;
using namespace std;
MainWindow::MainWindow(QWidget *parent) :
  QMainWindow(parent)
{
  ui.setupUi(this);
}

void MainWindow::on_actionWczytaj_plik_konfiguracyjny_triggered()
{
  const QString DEF_DIR = "/home/erucolindo",FILTER_TYPE = "Config Files (*.alize *.conf)";
  QString filename = QFileDialog::getOpenFileName(this, "", DEF_DIR, FILTER_TYPE);
  conf_.load(filename.toStdString().c_str());
}

void MainWindow::on_actionZapisz_plik_konfiguracyjny_triggered()
{
  const QString DEF_SAVE_FILE = "/home/erucolindo/Dokumenty/untitled.conf",FILTER_TYPE = "Config Files (*.alize *.conf)";
  QString filename = QFileDialog::getSaveFileName(this, "", DEF_SAVE_FILE, FILTER_TYPE);
  conf_.save(filename.toStdString().c_str());
}
