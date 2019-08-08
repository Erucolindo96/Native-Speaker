#include "VerificationResultController.hpp"
#include<iostream>
void VerificationResultController::setResultListPtr(QListWidget *result_list_ptr)
{
  throw std::runtime_error("To remove");
  result_list_ = result_list_ptr;
  connectClearResultList();
}

void VerificationResultController::setResults(const std::map<QString, std::pair<bool, double> > &results)
{
  using namespace std;
  //result_list_->clear();
//  for(int32_t i = 0; i<getRecordsCnt(); ++i)
//  {
//    QString rec = getRecordElem(i), result_str;
//    results.at(rec).first?result_str="true":result_str="false";
//    result_list_->addItem(result_str);
//  }

  QIcon false_icon(FALSE_ICON_PATH), true_icon(TRUE_ICON_PATH);
  for(int32_t i=0;i<getRecordsCnt();++i)
  {
    QListWidgetItem* item = getRecordsListWidgetElem(i);
    QString rec_path = item->text();
    results.at(rec_path).first?
          item->setIcon(true_icon):item->setIcon(false_icon);//wynik weryfikacji
    item->setToolTip(QString::number(results.at(rec_path).second));//LLK
  }

}

void VerificationResultController::clearResultList()
{
  throw std::runtime_error("To remove");
  result_list_->clear();
}
