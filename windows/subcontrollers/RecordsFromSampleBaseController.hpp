#ifndef RECORDSFROMSAMPLEBASECONTROLLER_HPP
#define RECORDSFROMSAMPLEBASECONTROLLER_HPP

#include"windows/subcontrollers/RecordsFromFilesystemController.hpp"
#include<QComboBox>
#include"record-base/RecBaseManager.hpp"

class RecordsFromSampleBaseController : public RecordsFromFilesystemController
{
  Q_OBJECT

public:
  RecordsFromSampleBaseController() = default;
  RecordsFromSampleBaseController(const RecordsFromSampleBaseController & o) = default;
  RecordsFromSampleBaseController& operator=(const RecordsFromSampleBaseController & o) = default;
  RecordsFromSampleBaseController(RecordsFromSampleBaseController &&o) = default;
  RecordsFromSampleBaseController& operator=(RecordsFromSampleBaseController &&o) = default;
  ~RecordsFromSampleBaseController()override = default;

  void setDisplayedModelComboBox(QComboBox *b);
  void initComboBox(const std::vector<std::string> models);
  void setFeatureFolderPath(const QString &path);

protected:
  QComboBox *displayed_model_;
  QString displayed_model_dir_;
  QString f_folder_path_;

protected slots:
  void changeModelDir(const QString &model_name);
  void addingRecord()override;

};

#endif // RECORDSFROMSAMPLEBASECONTROLLER_HPP
