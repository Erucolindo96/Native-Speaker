#include "MainWindow.hpp"
#include"learn-performing/LearningThreadWidget.hpp"
using namespace alize;
using namespace std;
MainWindow::MainWindow(QWidget *parent) :
  QMainWindow(parent),
  conf_(std::make_unique<ConfigManager>()),
  models_(std::make_unique<ModelController>(nullptr, MODELS_ON_PAGE))
{
  initMainWindow();
}

void MainWindow::initMainWindow()
{
  ui_.setupUi(this);
  models_->setToolBoxPtr(ui_.models_list);



  learning_c_.setComboBoxPtr(ui_.comboBox_learning_models);
  learning_c_.setProgressBarPtr(ui_.progressBar);
  learning_c_.setModelManagerPtr(models_.get());
  learning_c_.setConfigManagerPtr(conf_.get());

}

void MainWindow::on_actionRead_Configuration_File_triggered()
{
  const QString DEF_DIR = "/home/erucolindo",FILTER_TYPE = "Config Files (*.alize *.conf)";
  QString filename = QFileDialog::getOpenFileName(this, "", DEF_DIR, FILTER_TYPE);
  if(!filename.isEmpty())
  {
    ConfigValidator v;
    try
    {
      ConfigManager temp;
      temp.load(filename.toStdString().c_str());
      v.validateConfiguration(temp);
      *conf_ = temp;
      loadConfigToMembers();
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
    conf_->save(filename.toStdString().c_str());
  }
}

void MainWindow::on_action_CreateModel_triggered()
{
  if(!checkConfiguration())
  {
    return;
  }
  CreateModelWindow window(this);// = make_unique<CreateModelWindow>(this);
  window.setConfig(*conf_);
  connect(&window, SIGNAL(accepted()), this, SLOT(saveModelFromCreateModelWindow()));
  window.exec();
}

void MainWindow::on_actionAdd_Configuration_Parameter_triggered()
{
  std::unique_ptr<SetParameterWindow> window = make_unique<SetParameterWindow>(*conf_, this);
  connect(window.get(), SIGNAL(accepted()), this, SLOT(saveParamFromSetParameterWindow()));
  window->exec();

}

void MainWindow::saveModelFromCreateModelWindow()
{
  CreateModelWindow* ptr = dynamic_cast<CreateModelWindow*>(QObject::sender());
  if(ptr == nullptr)
  {
    throw std::runtime_error("Sender doesnt known - it must be always CreateModelWindow!");
  }
  models_->addModel(*conf_, ptr->getCreatedGmmModel());
}

void MainWindow::saveParamFromSetParameterWindow()
{
  SetParameterWindow *ptr = dynamic_cast<SetParameterWindow*>(QObject::sender());
  if(ptr == nullptr)
  {
    throw std::runtime_error("Sender doesnt known - it must be always SetParameterWindow!");
  }
  try
  {
    ConfigValidator v;
    v.isParamValid(ptr->getParamName().c_str(), ptr->getParamValue().c_str());
    conf_->setParam(ptr->getParamName().c_str(), ptr->getParamValue().c_str());
    v.checkComplexityOfConfig(*conf_);
  }
  catch(ParamNotValid &e)
  {
    QMessageBox::warning(const_cast<MainWindow*>(this),
                         "Configuration Error",
                         e.what() ,QMessageBox::Ok);
  }
  catch(ParamDoesNotExists &e)
  {
    return;
  }

  loadConfigToMembers();
}



bool MainWindow::checkConfiguration()const
{

  if(!conf_->haveAllParams())
  {
    const std::string msg = std::string("Please insert required parametrs to configuration: ") +
                      ConfigManager::PARAM_MODEL_DIR().c_str() + ", " +
                      ConfigManager::PARAM_FEATURE_FOLDER().c_str()+ ", " +
//                      ConfigManager::PARAM_UBM_DIR().c_str()   + ", " +
                      ConfigManager::PARAM_VECT_SIZE().c_str();
    QMessageBox::warning(const_cast<MainWindow*>(this),
                         "Configuration Error",
                         msg.c_str() ,QMessageBox::Ok);
    return false;
  }
  return true;
}



void MainWindow::on_toolButton_refresh_released()
{
    if(checkConfiguration())
    {
      models_->loadModels(*conf_);
      models_->refreshDisplayedModels();
      actualizePage();
    }
}

void MainWindow::actualizePage()
{
  QString page = QString::number(models_->getActPage());
  ui_.lineEdit_act_page->setText(page);
}

void MainWindow::on_commandLinkButton_next_models_released()
{
  if(checkConfiguration())
  {
    models_->nextPage();
    actualizePage();
  }
}

void MainWindow::on_commandLinkButton_prev_models_released()
{
  if(checkConfiguration())
  {
    models_->prevPage();
    actualizePage();
  }
}

void MainWindow::on_action_ModelLearning_triggered()
{
    if(checkConfiguration())
    {
      std::unique_ptr<LearningModelWindow> window = std::make_unique<LearningModelWindow>
                                                    (*models_, *conf_, r_base_, f_manager_, learning_c_);
      window->exec();
    }
}

void MainWindow::loadConfigToMembers()
{
  f_manager_.setFeatureFolder(conf_->getFeatureFolder().c_str());
  r_base_.setFeatureFolderPath(conf_->getFeatureFolder().c_str());
}



void MainWindow::on_actionVerification_triggered()
{
    if(checkConfiguration())
    {
      std::unique_ptr<ModelVerificationWindow> window = make_unique<ModelVerificationWindow>
                                                        (*models_,f_manager_,
                                                         conf_->getVectSize());
      window->exec();
    }
}

void MainWindow::on_actionView_sample_base_triggered()
{
  if(checkConfiguration())
  {
    auto window = make_unique<RecordBaseDisplayingWindow>(r_base_);
    window->setModelsList(models_->getModelsNames());
    window->exec();
  }
}
