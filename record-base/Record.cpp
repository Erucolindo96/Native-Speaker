#include "Record.hpp"
#include"features/MfccConverter.hpp"

void Record::setPath(const QString &rec_path)
{
  record_path_.setFile(rec_path);
  checkFileExistance();
}

void Record::setPath(const QString &rec_name, const QDir &rec_dir)
{
  checkDirExistance(rec_dir);
  record_path_.setFile(rec_dir, rec_name);
  checkFileExistance();
}
QFileInfo Record::getRecordInfo()const
{
  checkFileExistance();
  return record_path_;
}

Record Record::copy(const QDir &dest_dir)const
{
  checkDirExistance(dest_dir);
  checkFileExistance();

  QFile rec_file(record_path_.absoluteFilePath());
  QString dest_path = dest_dir.absolutePath() +"/" +record_path_.fileName();
  rec_file.copy(dest_path);

  Record ret;
  ret.setPath(dest_path);
  return ret;
}
void Record::move(const QDir &dest_dir)
{
  checkDirExistance(dest_dir);
  checkFileExistance();

  QFile rec_file(record_path_.absoluteFilePath());
  QString dest_path = dest_dir.absolutePath() + "/" +record_path_.fileName();
  rec_file.rename(dest_path);
  record_path_.setFile(rec_file);
}

void Record::rename(const QString new_name)
{
  checkFileExistance();
  QFile rec_file(record_path_.absoluteFilePath());
  rec_file.rename(record_path_.absolutePath() + "/" + new_name);
  record_path_.setFile(rec_file);

}

void Record::remove()
{
  checkFileExistance();
  QFile rec_file(record_path_.absoluteFilePath());
  rec_file.remove();
}

bool Record::exists()const
{
  record_path_.refresh();
  return record_path_.exists();
}

std::unique_ptr<MfccConverter> Record::getConverter()const
{
  std::unique_ptr<MfccConverter> ret;
  if(getRecordInfo().completeSuffix() == "wav")
  {
    ret = std::make_unique<MfccConverterWav>();
  }
  return ret;
}


  //protected
void Record::checkFileExistance()const
{
  record_path_.refresh();
  if(!record_path_.exists() || !record_path_.isFile())
  {
    throw FileNotFound(__FILE__ + std::string(", line: ") + std::to_string(__LINE__)
                       + std::string("record of path ") + record_path_.path().toStdString() +
                       std::string(" pointed by class does not exists"));
  }

}

void Record::checkDirExistance(const QDir &dir)const
{
  if(!dir.exists())
  {
    throw DirNotFound(__FILE__ + std::string(", line: ") + std::to_string(__LINE__)
                       + std::string("dir pointed by QDir class does not exists"));
  }
}
