#include "VerificationResultController.hpp"
#include<iostream>
void VerificationResultController::setResultListPtr(QListWidget *result_list_ptr)
{
  result_list_ = result_list_ptr;
  connectClearResultList();
}

void VerificationResultController::setResults(const std::map<QString, bool> &results)
{
  using namespace std;
  result_list_->clear();
  for(int32_t i = 0; i<getRecordsCnt(); ++i)
  {
    QString rec = getRecordElem(i), result_str;
    results.at(rec)?result_str="true":result_str="false";
    result_list_->addItem(result_str);
  }
}
