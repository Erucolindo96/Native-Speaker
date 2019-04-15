﻿#include "TempDir.hpp"
#include"features/MfccConverter.hpp"
void TempDir::setFeatureReader(std::unique_ptr<FeatureReader> &&reader)
{
  checkExistanceOfDir();
  f_reader_ = std::move(reader);
}

const std::unique_ptr<FeatureReader>& TempDir::getFeatureReaderRef()const
{
  checkExistanceOfDir();
  return f_reader_;
}

std::vector<alize::Feature> TempDir::convertToMfcc(const Record &rec_to_convert)
{
  auto rec = RecordDir::addRecord(rec_to_convert);

  auto converter = rec.getConverter();
  if(converter == nullptr)
  {
    throw UnableToConvertToMfcc(__FILE__ + std::string(", line: ") + std::to_string(__LINE__)
                                + std::string("unable to convert this file: ")
                                + rec_to_convert.getRecordInfo().fileName().toStdString());
  }
  auto spro_file = converter->convertToSPro4(rec);
  if(f_reader_ == nullptr)
  {
    f_reader_ = std::make_unique<FeatureReader>();
  }
  return f_reader_->readFile(spro_file);
}

void TempDir::cleanDir()
{
  RecordDir::removeAll();
}

bool TempDir::exists()const
{
  return RecordDir::exists();
}
