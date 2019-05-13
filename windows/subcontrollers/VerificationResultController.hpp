#ifndef VERIFICATIONRESULTCONTROLLER_HPP
#define VERIFICATIONRESULTCONTROLLER_HPP
#include<QListWidget>

class VerificationResultController
{
public:
  VerificationResultController()=default;
  VerificationResultController(const VerificationResultController &other) = default;

  VerificationResultController& operator=
  (const VerificationResultController &other) = default;

  VerificationResultController(VerificationResultController &&other) = default;

  VerificationResultController& operator=
  (VerificationResultController &&other) = default;

  void setResultListPtr(QListWidget *result_list_ptr);

  void setResults(const std::map<QString, bool> &results);

protected:
  QListWidget *result_list_;
  virtual int32_t getRecordsCnt()const = 0;
  virtual QString getRecordElem(int32_t i) = 0;
};

#endif // VERIFICATIONRESULTCONTROLLER_HPP
