#ifndef DATAACCESSOBJECTS
#define DATAACCESSOBJECTS

#include<set>
#include "UbmModel.hpp"
#include"speaker.hpp"
#include"speakermodel.hpp"
class SpeakerAccessObject
{
  SpeakerAccessObject() = default;

  virtual std::set<Speaker> getSpeakerByName(std::string name) = 0;
  virtual std::set<Speaker> getSpeakerBySurname(std::string surname) = 0;
  virtual std::set<Speaker> getSpeakerBySex(Sex s) = 0;
  virtual std::set<Speaker> getSpeakerByAge(uint8_t age) = 0;


  virtual ~SpeakerAccessObject()
  {}

};

class SpeakerModelAccessObject
{
  SpeakerModelAccessObject() = default;
  virtual SpeakerModel getSpeakerModelById(int64_t id) = 0;
  virtual std::set<SpeakerModel> getSpeakerModelBySpeaker(Speaker sp) = 0;

  virtual ~SpeakerModelAccessObject()
  {}

};

class UbmModelAccesObject
{
  UbmModelAccesObject() = default;
  virtual UbmModel getUbmModelById(int64_t id) = 0;
  virtual std::set<UbmModel> getUbmModelByName(std::string name) = 0;

  virtual ~UbmModelAccesObject()
  {}

};

class RecordAccessObject
{
  RecordAccessObject() = default;
  virtual RecordAccessObject getRecordById(int64_t id) = 0;
  virtual std::set<Record> getRecordByName(std::string file_name) = 0;

  virtual ~RecordAccessObject()
  {}

};

#endif // DATAACCESSOBJECT

