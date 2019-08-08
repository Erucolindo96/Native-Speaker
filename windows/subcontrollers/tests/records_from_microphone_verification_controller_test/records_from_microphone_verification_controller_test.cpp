#include "records_from_microphone_verification_controller_test.hpp"

using namespace std;
using namespace alize;


class RecordsFromMicrophoneVerificationControllerMock:
    public RecordsFromMicrophoneVerificationController
{
public:
  RecordsFromMicrophoneVerificationControllerMock()=default;
  RecordsFromMicrophoneVerificationControllerMock
  (const RecordsFromMicrophoneVerificationControllerMock &other) = default;

  RecordsFromMicrophoneVerificationControllerMock& operator=
  (const RecordsFromMicrophoneVerificationControllerMock &other) = default;

  RecordsFromMicrophoneVerificationControllerMock
  (RecordsFromMicrophoneVerificationControllerMock &&other) = default;

  RecordsFromMicrophoneVerificationControllerMock& operator=
  (RecordsFromMicrophoneVerificationControllerMock &&other) = default;

  ~RecordsFromMicrophoneVerificationControllerMock() override = default;

  int32_t getRecordsCnt()
  {
    return RecordsFromMicrophoneVerificationController::getRecordsCnt();
  }
  QListWidgetItem* getRecordsListWidgetElem(int32_t i)
  {
    return RecordsFromMicrophoneVerificationController::
        getRecordsListWidgetElem(i);
  }

};


BOOST_AUTO_TEST_SUITE( MicrophoneVerificationResultControllerTests )


BOOST_AUTO_TEST_CASE(correctlyGetRecordCntIfRecordListWasSet)
{
  QListWidget records;
  RecordsFromMicrophoneVerificationControllerMock controller;
  controller.setRecordListPtr(&records);

  const QString REC1 = "/tmp/record1", REC2 = "/home/eluhil/rec2.wav";
  const int32_t REC_CNT = 2;
  records.addItem(REC1);
  records.addItem(REC2);

  BOOST_CHECK_EQUAL(controller.getRecordsCnt(), REC_CNT);

}

BOOST_AUTO_TEST_CASE(correctlygetRecordsListWidgetElemIfRecordListWasSet)
{
  QListWidget records;
  RecordsFromMicrophoneVerificationControllerMock controller;
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
  RecordsFromMicrophoneVerificationControllerMock controller;
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
  RecordsFromMicrophoneVerificationControllerMock controller;
  controller.setAddButtonPtr(&add);
  controller.setRemoveButtonPtr(&remove);
  controller.setRecordListPtr(&records);

  const QString REC1 = "/tmp/record1", REC2 = "/home/eluhil/rec2.wav";
  const int32_t REC_CNT_first = 2, REC_CNT_second = 3;

  records.addItem(REC1);
  records.addItem(REC2);

  std::map<QString, std::pair<bool, double>> result_map = {{REC1, {false, 0.1}}, {REC2, {true, 0.1}}};
  BOOST_REQUIRE_NO_THROW(controller.setResults(result_map));
  BOOST_REQUIRE_EQUAL(records.count(), REC_CNT_first);
  BOOST_CHECK_EQUAL(records.item(0)->toolTip().toStdString(), "0.1");
  BOOST_CHECK_EQUAL(records.item(1)->toolTip().toStdString(), "0.1");
  //zmieniamy liste nagrań i robimy weryfikacje jeszcze raz
  const QString REC3 = "/koleje/mazowieckie.mp3";
  records.clear();
  records.addItem(REC2);
  records.addItem(REC3);
  records.addItem(REC1);

  std::map<QString, std::pair<bool, double>> result_map2 = {{REC2, {true,0.2}},
                                                            {REC3, {false, 0.3}},
                                                            {REC1, {false, 0.4}}};
  BOOST_REQUIRE_NO_THROW(controller.setResults(result_map2));
  BOOST_REQUIRE_EQUAL(records.count(), REC_CNT_second);
  BOOST_CHECK_EQUAL(records.item(0)->toolTip().toStdString(), "0.2");
  BOOST_CHECK_EQUAL(records.item(1)->toolTip().toStdString(), "0.3");
  BOOST_CHECK_EQUAL(records.item(2)->toolTip().toStdString(), "0.4");
}

BOOST_AUTO_TEST_CASE(throwOutOfRangeIfInResultMapArentOneRecordInRecordList)
{
  QListWidget records;
  QPushButton add, remove;
  RecordsFromMicrophoneVerificationControllerMock controller;
  controller.setAddButtonPtr(&add);
  controller.setRemoveButtonPtr(&remove);
  controller.setRecordListPtr(&records);

  const QString REC1 = "/tmp/record1", REC2 = "/home/eluhil/rec2.wav";
  records.addItem(REC1);
  records.addItem(REC2);

  std::map<QString, std::pair<bool, double>> result_map =
  {{REC1, {false, 0.1}}},
  result_map2;
  BOOST_CHECK_THROW(controller.setResults(result_map), out_of_range);
  BOOST_CHECK_THROW(controller.setResults(result_map2), out_of_range);
}





BOOST_AUTO_TEST_SUITE_END()
