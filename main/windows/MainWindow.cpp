#include "MainWindow.hpp"
using namespace alize;
using namespace std;
MainWindow::MainWindow(QWidget *parent) :
  QMainWindow(parent)
{
  ui_.setupUi(this);
}

void MainWindow::on_actionWczytaj_plik_konfiguracyjny_triggered()
{
  throw std::runtime_error("Dead code");
//  const QString DEF_DIR = "/home/erucolindo",FILTER_TYPE = "Config Files (*.alize *.conf)";
//  QString filename = QFileDialog::getOpenFileName(this, "", DEF_DIR, FILTER_TYPE);
//  conf_.load(filename.toStdString().c_str());
}
void MainWindow::on_actionZapisz_plik_konfiguracyjny_triggered()
{
  throw std::runtime_error("Dead code");
//  const QString DEF_SAVE_FILE = "/home/erucolindo/Dokumenty/untitled.conf",FILTER_TYPE = "Config Files (*.alize *.conf)";
//  QString filename = QFileDialog::getSaveFileName(this, "", DEF_SAVE_FILE, FILTER_TYPE);
//  conf_.save(filename.toStdString().c_str());
}

void MainWindow::on_actionUtw_rz_model_triggered()
{
  throw std::runtime_error("Dead code");
}


void MainWindow::on_actionRead_Configuration_File_triggered()
{

  const QString DEF_DIR = "/home/erucolindo",FILTER_TYPE = "Config Files (*.alize *.conf)";
  QString filename = QFileDialog::getOpenFileName(this, "", DEF_DIR, FILTER_TYPE);
  if(!filename.isEmpty())
  {
    //lock_guard<mutex> l(m_);
    conf_.load(filename.toStdString().c_str());
  }
}

void MainWindow::on_actionSave_Configuration_File_triggered()
{
  const QString DEF_SAVE_FILE = "/home/erucolindo/Dokumenty/untitled.conf",FILTER_TYPE = "Config Files (*.alize *.conf)";
  QString filename = QFileDialog::getSaveFileName(this, "", DEF_SAVE_FILE, FILTER_TYPE);
  if(!filename.isEmpty())
  {
    //lock_guard<mutex> l(m_);
    conf_.save(filename.toStdString().c_str());
  }
}

void MainWindow::on_action_CreateModel_triggered()
{
  std::unique_ptr<CreateModelWindow> window = make_unique<CreateModelWindow>();
  connect(window.get(), SIGNAL(accepted()), this, SLOT(saveModelFromCreateModelWindow()));
  window->exec();
}

void MainWindow::saveModelFromCreateModelWindow()
{
  cout<<"Save Model"<<endl;
  CreateModelWindow* ptr = dynamic_cast<CreateModelWindow*>(QObject::sender());
  if(ptr == nullptr)
  {
    throw std::runtime_error("Sender doesnt known - it must be always CreateModelWindow!");
  }
  models_.addModel(conf_, ptr->getCreatedGmmModel());
  models_.loadModels(conf_); //TODO - może niepotrzebne, zalezy czy modele sie odwiezaja
}
