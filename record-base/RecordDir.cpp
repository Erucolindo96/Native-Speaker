#include "RecordDir.hpp"


const Record RecordDir::addRecord(const Record &rec)
{
  checkExistanceOfDir();
  return rec.copy(dir_);
}

const std::vector<Record> RecordDir::list()const
{
  checkExistanceOfDir();
  std::vector<Record> ret;
  for(auto file: dir_.entryList())
  {
    Record r;
    r.setPath(file, dir_);
    ret.push_back(r);
  }
  return ret;
}
void RecordDir::removeAll()
{
  checkExistanceOfDir();
  for(auto file: dir_.entryList())
  {
    dir_.remove(file);
  }
}

bool RecordDir::haveRecord(const Record &other)const
{
  checkExistanceOfDir();
  return dir_.entryList().contains(other.getRecordInfo().fileName());
}
bool RecordDir::exists()const
{
  return QFileInfo(dir_path_).exists() && QFileInfo(dir_path_).isDir();
}

void RecordDir::checkExistanceOfDir()const
{
  if(!QFileInfo(dir_path_).exists())
  {
    throw DirNotFound(__FILE__ + std::string(", line: ") + std::to_string(__LINE__)
                      + std::string(" record dir pointed by class does not exists"));
  }
  dir_.setPath(dir_path_);
  dir_.refresh();
}

void RecordDir::setDir(const QDir &dir)
{
  dir_path_ = dir.absolutePath();
  dir_ = dir;
  dir_.setFilter(QDir::NoDotAndDotDot|QDir::Files);
}

QString RecordDir::getDirPath()const
{
  return dir_path_;
}


