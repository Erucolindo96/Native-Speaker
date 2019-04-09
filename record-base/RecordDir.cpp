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
//    if(file == "." || file == "..")
//    {
//      continue;
//    }
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
  dir_.refresh();
  return dir_.exists();
}

void RecordDir::checkExistanceOfDir()const
{
  dir_.refresh();
  if(!dir_.exists())
  {
    throw DirNotFound(__FILE__ + std::string(", line: ") + std::to_string(__LINE__)
                      + std::string("record dir pointed by class does not exists"));
  }
}

void RecordDir::setDir(const QDir &dir)
{
  dir_ = dir;
  dir_.setFilter(QDir::NoDotAndDotDot|QDir::Files);
}

QDir RecordDir::getDir()const
{
  return dir_;
}


