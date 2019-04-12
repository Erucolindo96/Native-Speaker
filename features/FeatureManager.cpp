#include "FeatureManager.hpp"


void FeatureManager::setFeatureFolder(const QString &path)
{
  temp_manager_.setFeatureFolder(path);
}

QString FeatureManager::getFeatureFolder()const
{
  return temp_manager_.getFeatureFolder();
}


std::vector<alize::Feature> FeatureManager::convertRecord(const Record &r,
                                          std::unique_ptr<FeatureReader>&& reader)
{
  auto temp_dir = temp_manager_.getTempDir();
  temp_dir.setFeatureReader(std::move(reader));
  return temp_dir.convertToMfcc(r);
}

std::vector<alize::Feature> FeatureManager::convertRecord(const std::vector<Record> &r_vec,
                                          std::unique_ptr<FeatureReader>&& reader )
{
  auto temp_dir = temp_manager_.getTempDir();
  temp_dir.setFeatureReader(std::move(reader));
  std::vector<alize::Feature> ret;
  for(auto rec : r_vec)
  {
    auto mfcc_vec = temp_dir.convertToMfcc(rec);
    ret.insert(ret.cend(), mfcc_vec.cbegin(), mfcc_vec.cend());
  }
  return ret;
}

void FeatureManager::clean()
{
  auto temp_dir = temp_manager_.getTempDir();
  temp_dir.cleanDir();
}

