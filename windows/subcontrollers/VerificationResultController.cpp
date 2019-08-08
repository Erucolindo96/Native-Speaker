#include "VerificationResultController.hpp"
#include<iostream>


const QString VerificationResultController::TRUE_ICON_PATH  = "resources/true.png";
const QString VerificationResultController::FALSE_ICON_PATH = "resources/false.png";

void VerificationResultController::setResults(const std::map<QString, std::pair<bool, double> > &results)
{

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

