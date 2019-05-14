#include "records_from_filesystem_verification_controller_test.hpp"

using namespace std;
using namespace alize;



class RecordsFromFilesystemVerificationControllerMock:
    public RecordsFromFilesystemVerificationController
{
public:
  RecordsFromFilesystemVerificationControllerMock()=default;
  RecordsFromFilesystemVerificationControllerMock
  (const RecordsFromFilesystemVerificationControllerMock &other) = default;

  RecordsFromFilesystemVerificationControllerMock& operator=
  (const RecordsFromFilesystemVerificationControllerMock &other) = default;

  RecordsFromFilesystemVerificationControllerMock
  (RecordsFromFilesystemVerificationControllerMock &&other) = default;

  RecordsFromFilesystemVerificationControllerMock& operator=
  (RecordsFromFilesystemVerificationControllerMock &&other) = default;

  ~RecordsFromFilesystemVerificationControllerMock() override = default;

  int32_t getRecordsCnt()
  {
    return RecordsFromFilesystemVerificationController::getRecordsCnt();
  }
  QString getRecordElem(int32_t i)
  {
    return RecordsFromFilesystemVerificationController::getRecordElem(i);
  }

};


BOOST_AUTO_TEST_SUITE( VerificationResultControllerTests )

BOOST_AUTO_TEST_CASE(correctlySetQListWidgetPtrIfOtherUiElementsWereSet)
{
  QListWidget results, records;
  QPushButton add, remove;
  RecordsFromFilesystemVerificationControllerMock controller;
  controller.setAddButtonPtr(&add);
  controller.setRemoveButtonPtr(&remove);
  controller.setRecordListPtr(&records);
  BOOST_CHECK_NO_THROW(controller.setResultListPtr(&results));
}



BOOST_AUTO_TEST_CASE(correctlyGetRecordCntIfRecordListWasSet)
{
  QListWidget records;
  RecordsFromFilesystemVerificationControllerMock controller;
  controller.setRecordListPtr(&records);

  const QString REC1 = "/tmp/record1", REC2 = "/home/eluhil/rec2.wav";
  const int32_t REC_CNT = 2;
  records.addItem(REC1);
  records.addItem(REC2);

  BOOST_CHECK_EQUAL(controller.getRecordsCnt(), REC_CNT);

}

BOOST_AUTO_TEST_CASE(correctlyGetRecordElemIfRecordListWasSet)
{
  QListWidget records;
  RecordsFromFilesystemVerificationControllerMock controller;
  controller.setRecordListPtr(&records);
  const QString REC1 = "/tmp/record1", REC2 = "/home/eluhil/rec2.wav";
  records.addItem(REC1);
  records.addItem(REC2);
  BOOST_CHECK_EQUAL(controller.getRecordElem(0).toStdString(), REC1.toStdString());
  BOOST_CHECK_EQUAL(controller.getRecordElem(1).toStdString(), REC2.toStdString());

}

BOOST_AUTO_TEST_CASE(throwOutOfRangeAtGettingRecordElemIfIndexIsOutOfBound)
{
  QListWidget records;
  RecordsFromFilesystemVerificationControllerMock controller;
  controller.setRecordListPtr(&records);
  const QString REC1 = "/tmp/record1", REC2 = "/home/eluhil/rec2.wav";
  records.addItem(REC1);
  records.addItem(REC2);
  BOOST_CHECK_THROW(controller.getRecordElem(-1), out_of_range);
  BOOST_CHECK_THROW(controller.getRecordElem(10), out_of_range);
}

BOOST_AUTO_TEST_CASE(correctlyDisplayVerificationResultIfListPtrsWereSetAndRecordsAreTwoAndResultMapIsCorrect)
{
  QListWidget records, results;
  QPushButton add, remove;
  RecordsFromFilesystemVerificationControllerMock controller;
  controller.setAddButtonPtr(&add);
  controller.setRemoveButtonPtr(&remove);
  controller.setRecordListPtr(&records);
  controller.setResultListPtr(&results);

  const QString REC1 = "/tmp/record1", REC2 = "/home/eluhil/rec2.wav";
  const int32_t REC_CNT = 2;

  records.addItem(REC1);
  records.addItem(REC2);

  std::map<QString, bool> result_map = {{REC1, false}, {REC2, true}};
  BOOST_REQUIRE_NO_THROW(controller.setResults(result_map));
  BOOST_REQUIRE_EQUAL(results.count(), REC_CNT);
  BOOST_CHECK_EQUAL(results.item(0)->text().toStdString(), "false");
  BOOST_CHECK_EQUAL(results.item(1)->text().toStdString(), "true");
  //zmieniamy liste nagrań i robimy weryfikacje jeszcze raz
  const QString REC3 = "/koleje/mazowieckie.mp3";
  records.clear();
  records.addItem(REC2);
  records.addItem(REC3);
  records.addItem(REC1);

  std::map<QString, bool> result_map2 = {{REC2, true}, {REC3, false}, {REC1, false}};
  BOOST_REQUIRE_NO_THROW(controller.setResults(result_map2));
  BOOST_REQUIRE_EQUAL(results.count(), REC_CNT + 1);
  BOOST_CHECK_EQUAL(results.item(0)->text().toStdString(), "true");
  BOOST_CHECK_EQUAL(results.item(1)->text().toStdString(), "false");
  BOOST_CHECK_EQUAL(results.item(2)->text().toStdString(), "false");
}

BOOST_AUTO_TEST_CASE(throwOutOfRangeIfInResultMapArentOneRecordInRecordList)
{
  QListWidget records, results;
  QPushButton add, remove;
  RecordsFromFilesystemVerificationControllerMock controller;
  controller.setAddButtonPtr(&add);
  controller.setRemoveButtonPtr(&remove);
  controller.setRecordListPtr(&records);
  controller.setResultListPtr(&results);

  const QString REC1 = "/tmp/record1", REC2 = "/home/eluhil/rec2.wav";
  records.addItem(REC1);
  records.addItem(REC2);

  std::map<QString, bool> result_map = {{REC1, false}},
  result_map2;
  BOOST_CHECK_THROW(controller.setResults(result_map), out_of_range);
  BOOST_CHECK_THROW(controller.setResults(result_map2), out_of_range);
}

/**
  ten test jest bez sensu, bo zmiana jest powodowana sygnałem puszczenia przycisków dodawania i usuwania nagrań z listy
  a nie samym faktem usunięcia
  */

//BOOST_AUTO_TEST_CASE(clearResultsIfAnotherRecordWasAddedOrRemovedToRecordList)
//{
//  QListWidget records, results;
//  QPushButton add, remove;
//  RecordsFromFilesystemVerificationControllerMock controller;
//  controller.setAddButtonPtr(&add);
//  controller.setRemoveButtonPtr(&remove);
//  controller.setRecordListPtr(&records);
//  controller.setResultListPtr(&results);

//  const QString REC1 = "/tmp/record1", REC2 = "/home/eluhil/rec2.wav",
//      REC3 = "koleje/mazowieckie.mp5";
//  const int32_t REC_CNT = 2;
//  records.addItem(REC1);
//  records.addItem(REC2);

//  std::map<QString, bool> result_map = {{REC1, false}, {REC2, true}},
//      result_map2 = {{REC2, true}, {REC3, false}, {REC1, false}};

//  BOOST_REQUIRE_NO_THROW(controller.setResults(result_map));
//  BOOST_CHECK_EQUAL(results.count(), REC_CNT);

//  records.addItem(REC3);
//  BOOST_CHECK_EQUAL(results.count(), 0);
//  BOOST_REQUIRE_NO_THROW(controller.setResults(result_map2));
//  BOOST_CHECK_EQUAL(results.count(), REC_CNT + 1);
//  records.removeItemWidget(records.item(0));
//  BOOST_CHECK_EQUAL(results.count(), 0);
//}




BOOST_AUTO_TEST_SUITE_END()
