#include "RecordsFromSampleBaseController.hpp"

void RecordsFromSampleBaseController::setDisplayedModelComboBox(QComboBox *b)
{

  displayed_model_ = b;
  connect(displayed_model_, SIGNAL(currentIndexChanged(QString)),
          this, SLOT(changeModelDir(const QString&)));
}


void RecordsFromSampleBaseController::initComboBox(const std::vector<std::string> models)
{
  for(auto name: models)
  {
    displayed_model_->addItem(name.c_str());
  }
}

void RecordsFromSampleBaseController::setFeatureFolderPath(const QString &path)
{
  f_folder_path_ = path;
  changeModelDir("");
}

void RecordsFromSampleBaseController::changeModelDir(const QString &model_name)
{
  displayed_model_dir_ = RecBaseManager::getModelPath(model_name, f_folder_path_);
}

void RecordsFromSampleBaseController::addingRecord()
{
  const QString title = "Add record", def_dir=displayed_model_dir_ , filters=
      "Records (*.wav *.mp3);;All Files (*)";
  QStringList record_files = QFileDialog::getOpenFileNames(nullptr,title,def_dir, filters);
  if(record_files.empty())
  {
    return;
  }
  record_list_->addItems(record_files);
}

