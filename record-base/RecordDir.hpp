#ifndef MODELDIR_HPP
#define MODELDIR_HPP
#include"record-base/Record.hpp"
#include<QDir>
#include<vector>
class RecordDir
{

public:
  RecordDir() = default;
  RecordDir(const RecordDir &other) = default;
  RecordDir& operator=(const RecordDir &other) = default;
  RecordDir(RecordDir &&other) = default;
  RecordDir& operator=(RecordDir &&other) = default;

  void addRecord(const Record &rec);
  const std::vector<Record> list()const;
  void removeAll();
  bool haveRecord(const Record &other)const;
protected:
  QDir dir_;
};

#endif // MODELDIR_HPP
