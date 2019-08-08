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
  QListWidgetItem* getRecordsListWidgetElem(int32_t i)
  {
    return RecordsFromFilesystemVerificationController::
        getRecordsListWidgetElem(i);
  }

};


BOOST_AUTO_TEST_SUITE( VerificationResultControllerTests )



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
  BOOST_CHECK_EQUAL(controller.getRecordsListWidgetElem(0)->text().toStdString(), REC1.toStdString());
  BOOST_CHECK_EQUAL(controller.getRecordsListWidgetElem(1)->text().toStdString(), REC2.toStdString());

}

BOOST_AUTO_TEST_CASE(throwOutOfRangeAtGettingRecordElemIfIndexIsOutOfBound)
{
  QListWidget records;
  RecordsFromFilesystemVerificationControllerMock controller;
  controller.setRecordListPtr(&records);
  const QString REC1 = "/tmp/record1", REC2 = "/home/eluhil/rec2.wav";
  records.addItem(REC1);
  records.addItem(REC2);
  BOOST_CHECK_THROW(controller.getRecordsListWidgetElem(-1), out_of_range);
  BOOST_CHECK_THROW(controller.getRecordsListWidgetElem(10), out_of_range);
}

BOOST_AUTO_TEST_CASE(correctlyDisplayVerificationResultIfListPtrsWereSetAndRecordsAreTwoAndResultMapIsCorrect)
{
  QListWidget records;
  QPushButton add, remove;
  RecordsFromFilesystemVerificationControllerMock controller;
  controller.setAddButtonPtr(&add);
  controller.setRemoveButtonPtr(&remove);
  controller.setRecordListPtr(&records);

  const QString REC1 = "/tmp/record1", REC2 = "/home/eluhil/rec2.wav";
  const int32_t REC_CNT = 2;

  records.addItem(REC1);
  records.addItem(REC2);

  std::map<QString, std::pair<bool, double>> result_map =
  {{REC1, {false, 0.0}}, {REC2, {true, 0.1}}};
  BOOST_REQUIRE_NO_THROW(controller.setResults(result_map));
  BOOST_CHECK_EQUAL(records.item(0)->toolTip().toStdString(), "0");
  BOOST_CHECK_EQUAL(records.item(1)->toolTip().toStdString(), "0.1");

  //zmieniamy liste nagrań i robimy weryfikacje jeszcze raz
  const QString REC3 = "/koleje/mazowieckie.mp3";
  records.clear();
  records.addItem(REC2);
  records.addItem(REC3);
  records.addItem(REC1);

  std::map<QString, std::pair<bool, double>> result_map2 =
  {{REC2, {true, 0.1}}, {REC3, {false, 0.2}}, {REC1, {false,0.3}}};
  BOOST_REQUIRE_NO_THROW(controller.setResults(result_map2));

  BOOST_CHECK_EQUAL(records.item(0)->toolTip().toStdString(), "0.1");
  BOOST_CHECK_EQUAL(records.item(1)->toolTip().toStdString(), "0.2");
  BOOST_CHECK_EQUAL(records.item(2)->toolTip().toStdString(), "0.3");


}

BOOST_AUTO_TEST_CASE(throwOutOfRangeIfInResultMapArentOneRecordInRecordList)
{
  QListWidget records;
  QPushButton add, remove;
  RecordsFromFilesystemVerificationControllerMock controller;
  controller.setAddButtonPtr(&add);
  controller.setRemoveButtonPtr(&remove);
  controller.setRecordListPtr(&records);

  const QString REC1 = "/tmp/record1", REC2 = "/home/eluhil/rec2.wav";
  records.addItem(REC1);
  records.addItem(REC2);

  std::map<QString, std::pair<bool, double>> result_map =
  {{REC1, {false,0.1}}},
  result_map2;
  BOOST_CHECK_THROW(controller.setResults(result_map), out_of_range);
  BOOST_CHECK_THROW(controller.setResults(result_map2), out_of_range);
}






BOOST_AUTO_TEST_SUITE_END()
