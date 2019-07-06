#include "CmdVerifyModel.hpp"

void CmdVerifyModel::checkSyntax()const
{
  CmdDiffLLK::checkSyntax();
  if(!parser_ptr_->isSet(CommandParamContainer::getOptionThreshold()))
  {
    QString msg("Threshold was not set");
    qWarning()<<msg.toLatin1().data();
    throw ErrorCodeException(msg.toStdString(), -1);
  }
}

void CmdVerifyModel::readArgs()
{
  CmdDiffLLK::readArgs();

  threshold_ = parser_ptr_->value(CommandParamContainer::getOptionThreshold()).
               toDouble(&is_threshold_double_);
  qDebug()<<"Threshold value: " + QString().number(threshold_);
  CmdVerifyModel::validateArgs();
}


void CmdVerifyModel::performCommand()
{
  Record r;
  r.setPath(record_path_.absoluteFilePath());
  auto mfcc = f_manager_ptr_->
              convertRecord(r, config_ptr_->getVectSize(),
                            make_unique<FeatureReaderSilenceCutter>());
  auto model = model_man_ptr_->operator [](model_name_.toStdString()),
      ubm = model_man_ptr_->operator [](ubm_name_.toStdString());
  Verificator v;
  v.setThreshold(threshold_);
  qInfo()<<v.verifyModel(*model, mfcc, *ubm);
}

void CmdVerifyModel::acceptExecutor(const CommandExecutor &executor)
{
  executor.execIfRequired(*this);
}

void CmdVerifyModel::validateArgs()
{
  if(!is_threshold_double_)
  {
    QString msg("Threshold is not a number");
    qWarning()<<msg.toLatin1().data();
    throw ErrorCodeException(msg.toStdString(), -1);
  }
}
