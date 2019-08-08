#include "VerificationResultController.hpp"
#include<iostream>


void VerificationResultController::setResults(const std::map<QString, std::pair<bool, double> > &results)
{

  QIcon false_icon(ResourceContainer::getFalseImagePath()),
      true_icon(ResourceContainer::getTrueImagePath());
  for(int32_t i=0;i<getRecordsCnt();++i)
  {
    QListWidgetItem* item = getRecordsListWidgetElem(i);
    QString rec_path = item->text();
    results.at(rec_path).first?
          item->setIcon(true_icon):item->setIcon(false_icon);//wynik weryfikacji
    item->setToolTip(QString::number(results.at(rec_path).second));//LLK
  }

}

