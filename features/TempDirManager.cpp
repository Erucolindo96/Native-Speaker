#include "TempDirManager.hpp"

void TempDirManager::setFeatureFolder(const QString &dir_path)
{
  RecordDirManager::setFeatureFolder(dir_path);
}

QString TempDirManager::getFeatureFolder()const
{
  return RecordDirManager::getFeatureFolder();

}

bool TempDirManager::isDirExists()const
{
  return RecordDirManager::isDirExists(TEMP_DIR_NAME.toStdString());

}
TempDir TempDirManager::getTempDir()
{
  RecordDir dir = getModelDir(TEMP_DIR_NAME.toStdString());
  TempDir ret;
  ret.setDir(QDir(dir.getDirPath()));
  return ret;
}

TempDir TempDirManager::getTempDir()const
{
  RecordDir dir = getModelDir(TEMP_DIR_NAME.toStdString());
  TempDir ret;
  ret.setDir(QDir(dir.getDirPath()));
  return ret;
}
