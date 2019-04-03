#include "SPro4File.hpp"

const QString SPro4File::VALID_EXT = "mfcc";

void SPro4File::setPath(const QString &file_path)
{
  Record::setPath(file_path);
  validate();
}

void SPro4File::setPath(const QString &file_name, const QDir &file_dir)
{
  Record::setPath(file_name, file_dir);
  validate();
}

QFileInfo SPro4File::getRecordInfo()const
{
  validate();
  return Record::getRecordInfo();
}

SPro4File SPro4File::copy(const QDir &dest_dir)const
{
  return SPro4File(Record::copy(dest_dir));
}
/*
void SPro4File::move(const QDir &dest_dir)
{
  validate();
  Record::move(dest_dir);
}

void SPro4File::rename(const QString new_name)
{
  validate();
  Record::rename(new_name);
}*/



SPro4File::SPro4File(const Record &rec):Record(rec)
{
  validate();
}

void SPro4File::validate()const
{
  record_path_.refresh();
  if(!(record_path_.suffix() == VALID_EXT))
  {
    throw NotASProFile(__FILE__ + std::string(", line: ") + std::to_string(__LINE__)
                       + std::string("file pointed by class is not a SPro4File"));
  }
}

