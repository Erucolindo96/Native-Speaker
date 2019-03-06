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
    ConfigValidator v;
    //lock_guard<mutex> l(m_);
    try
    {
      conf_.load(filename.toStdString().c_str());
      v.validateConfiguration(conf_);
    }
    catch(ParamNotValid e)
    {
      QMessageBox::warning(const_cast<MainWindow*>(this),
                           "Configuration Error",
                           e.what() ,QMessageBox::Ok);
    }
    catch(alize::FileNotFoundException e)
    {
      QMessageBox::warning(const_cast<MainWindow*>(this),
                           "Configuration Error",
                           "File with loaded config not found." ,QMessageBox::Ok);
    }
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
  if(!checkConfiguration())
  {
    return;
  }
  std::unique_ptr<CreateModelWindow> window = make_unique<CreateModelWindow>(this);
  window->setConfig(conf_);
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
  //models_.loadModels(conf_); //TODO - może niepotrzebne, zalezy czy modele sie odwiezaja
  cout<<"Model:" <<models_[0]->getName()<<"saved!"<<endl;
}
bool MainWindow::checkConfiguration()const
{
  /*
  if(!conf_.haveModelFolder())
  {
    QMessageBox::warning(this, "Configuration Error",
                         "Please insert model dir to configuration",
                         QMessageBox::Ok);
    return false;
  }
  if(!conf_.haveUbmFolder())
  {
    QMessageBox::warning(this, "Configuration Error",
                         "Please insert Ubm dir to configuration",
                         QMessageBox::Ok);
    return false;
  }
  if(!conf_.haveVectSize())
  {
    QMessageBox::warning(this, "Configuration Error",
                         "Please insert feature vector size to configuration",
                        QMessageBox::Ok);
    return false;
  }
  if(!conf_.haveFeatureFolder())
  {
    QMessageBox::warning(this, "Configuration Error",
                         "Please insert dir of aggreging features and records to configuration",
                          QMessageBox::Ok);
    return false;
  }
*/
  if(!conf_.haveAllParams())
  {
    const std::string msg = std::string("Please insert required parametrs to configuration: ") +
                      ConfigManager::PARAM_MODEL_DIR().c_str() + ", " +
                      ConfigManager::PARAM_FEATURE_FOLDER().c_str()+ ", " +
                      ConfigManager::PARAM_UBM_DIR().c_str()   + ", " +
                      ConfigManager::PARAM_VECT_SIZE().c_str();
    QMessageBox::warning(const_cast<MainWindow*>(this),
                         "Configuration Error",
                         msg.c_str() ,QMessageBox::Ok);
    return false;
  }
  return true;
}
