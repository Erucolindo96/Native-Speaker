#ifndef RECORDSINSAMPLEBASECONTROLLER_HPP
#define RECORDSINSAMPLEBASECONTROLLER_HPP
#include"windows/subcontrollers/RecordsFromFilesystemController.hpp"
#include<QComboBox>
#include"record-base/RecBaseManager.hpp"

class RecordsInSampleBaseController: protected RecordsFromFilesystemController
{
  Q_OBJECT
public:
  RecordsInSampleBaseController();

  RecordsInSampleBaseController
  (const RecordsInSampleBaseController &o) = default;
  RecordsInSampleBaseController& operator=
  (const RecordsInSampleBaseController &o) = default;

  RecordsInSampleBaseController
  (RecordsInSampleBaseController &&o) = default;
  RecordsInSampleBaseController& operator=
  (RecordsInSampleBaseController &&o) = default;

  ~RecordsInSampleBaseController()override=default;

  void setRemoveButtonPtr(QAbstractButton *ptr);
  void setComboBoxPtr(QComboBox *ptr);
  void setRecordListPtr(QListWidget *ptr);
  void setSampleBaseManPtr(RecBaseManager *ptr);

  void setModelsList(const std::vector<std::string> &models);

protected slots:
  void displayRecordsOfModel(const QString &model_name);
  void removingRecord() override;

protected:
  QComboBox *model_box_ptr_;
  RecBaseManager *sample_base_;

};

#endif // RECORDSINSAMPLEBASECONTROLLER_HPP
