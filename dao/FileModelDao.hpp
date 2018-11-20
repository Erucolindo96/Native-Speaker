#ifndef FILEMODELDAO_HPP
#define FILEMODELDAO_HPP
#include"dao/ModelDao.hpp"
#include<alize.h>
#include<stdexcept>
#include"exceptions/simple_exceptions.hpp"
enum MixtureFileType{
  XML,
  RAW
};

/*
class DirNotDefined: public std::logic_error
{
public:
  DirNotDefined(const std::string &msg): std::logic_error(msg)
  {}
};
*/


class FileModelDao : public ModelDao
{
protected:
  alize::Config conf_;
  std::unique_ptr<alize::MixtureServerFileReaderAbstract> reader_;
  std::unique_ptr<alize::MixtureServerFileWriter> writer_;
  MixtureFileType type_;

public:
  explicit FileModelDao(MixtureFileType t = XML);
  FileModelDao(const FileModelDao &other);
  FileModelDao& operator =(const FileModelDao &other);
  FileModelDao(FileModelDao &&other);
  FileModelDao& operator =(FileModelDao &&other);

  MixtureFileType getFileType()const;
  void setFileType(MixtureFileType t);

  std::string getMixtureDir()const;
  void setMixtureDir(const std::string new_dir);

  void writeModel(const GmmModel &m)const override;
  std::unique_ptr<GmmModel> readModel(const std::string &model_name) override;


};

#endif // FILEMODELDAO_HPP
