#include "SPro4File.hpp"

void SPro4File::setPath(const QString &rec_path)
{
  throw std::runtime_error("TODO");
}

void SPro4File::setPath(const QString &rec_name, const QDir &rec_dir)
{
  throw std::runtime_error("TODO");
}

QFileInfo SPro4File::getRecordInfo()const
{
    throw std::runtime_error("TODO");
}

Record SPro4File::copy(const QDir &dest_dir)const
{
    throw std::runtime_error("TODO");
}
void SPro4File::move(const QDir &dest_dir)
{
    throw std::runtime_error("TODO");
}

void SPro4File::rename(const QString new_name)
{
    throw std::runtime_error("TODO");
}


bool SPro4File::exists()const
{
    throw std::runtime_error("TODO");
}

void SPro4File::validate()const
{
    throw std::runtime_error("TODO");
}

