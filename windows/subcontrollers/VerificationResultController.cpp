#include "VerificationResultController.hpp"

void VerificationResultController::setResultListPtr(QListWidget *result_list_ptr)
{
  result_list_ = result_list_ptr;
}

void VerificationResultController::setResults(const std::map<QString, bool> &results)
{
  result_list_->clear();
  for(int32_t i = 0; i<getRecordsCnt(); ++i)
  {
    QString rec = getRecordElem(i), result_str;
    results.at(rec)?result_str="true":result_str="false";
    result_list_->addItem(result_str);
  }
}
