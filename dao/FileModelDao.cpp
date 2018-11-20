#include "FileModelDao.hpp"



FileModelDao::FileModelDao(MixtureFileType t)
{

}

FileModelDao::FileModelDao(const FileModelDao &other)
{

}

FileModelDao& FileModelDao::operator =(const FileModelDao &other)
{

}

FileModelDao::FileModelDao(FileModelDao &&other)
{

}

FileModelDao& FileModelDao::operator =(FileModelDao &&other)
{

}

MixtureFileType FileModelDao::getFileType()const
{
}
void FileModelDao::setFileType(MixtureFileType t)
{

}

std::string FileModelDao::getMixtureDir()const
{

}
void FileModelDao::setMixtureDir(const std::string new_dir)
{

}

void FileModelDao::writeModel(const GmmModel &m)const
{

}
std::unique_ptr<GmmModel> FileModelDao::readModel(const std::string &model_name)
{

}
