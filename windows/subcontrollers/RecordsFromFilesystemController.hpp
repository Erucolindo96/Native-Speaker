#ifndef RECORDSFROMFILESYSTEMCONTROLLER_HPP
#define RECORDSFROMFILESYSTEMCONTROLLER_HPP
#include<QListWidget>
#include<QPushButton>
#include<QFileDialog>
#include<QLabel>
#include<iostream>
#include"record-base/Record.hpp"
class RecordsFromFilesystemController:public QObject
{
  Q_OBJECT
public:
  RecordsFromFilesystemController(/*QListWidget *record_list = nullptr,
                                  QAbstractButton* add_button= nullptr,
                                  QAbstractButton *remove_button= nullptr*/);
  RecordsFromFilesystemController(const RecordsFromFilesystemController &other) = default;
  RecordsFromFilesystemController& operator=(const RecordsFromFilesystemController &other) = default;
  RecordsFromFilesystemController(RecordsFromFilesystemController &&other) = default;
  RecordsFromFilesystemController& operator=(RecordsFromFilesystemController &&other) = default;
  ~RecordsFromFilesystemController() override = default;

  void setRemoveButtonPtr(QAbstractButton *ptr);
  void setAddButtonPtr(QAbstractButton *ptr);
  void setRecordListPtr(QListWidget *ptr);

  std::vector<Record> getActualRecords()const;

protected:
  QListWidget *record_list_;
  QAbstractButton *add_button_, *remove_button_;
//  void bindSlots();

protected slots:
  void addingRecord();
  void removingRecord();


};

#endif // RECORDSFROMFILESYSTEMCONTROLLER_HPP
