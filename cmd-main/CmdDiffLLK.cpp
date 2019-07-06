#include "CmdDiffLLK.hpp"



void CmdDiffLLK::checkSyntax()const
{
  if(!parser_ptr_->isSet(CommandParamContainer::getOptionModelName()))
  {
    QString msg("Model name was not set");
    qWarning()<<msg.toLatin1().data();
    throw ErrorCodeException(msg.toStdString(), -1);
  }
  if(!parser_ptr_->isSet(CommandParamContainer::getOptionUbmName()))
  {
    QString msg("Ubm name was not set");
    qWarning()<<msg.toLatin1().data();
    throw ErrorCodeException(msg.toStdString(), -1);
  }
  if(!parser_ptr_->isSet(CommandParamContainer::getOptionRecordPath()))
  {
    QString msg("Record path was not set");
    qWarning()<<msg.toLatin1().data();
    throw ErrorCodeException(msg.toStdString(), -1);
  }
}

void CmdDiffLLK::readArgs()
{
  model_man_ptr_->loadModels(*config_ptr_);
  model_name_ = parser_ptr_->value(CommandParamContainer::getOptionModelName());
  qDebug()<<"Model name: "<<model_name_;
  ubm_name_ = parser_ptr_->value(CommandParamContainer::getOptionUbmName());
  qDebug()<<"UBM name: "<<ubm_name_;
  record_path_.setFile(parser_ptr_->value(CommandParamContainer::getOptionRecordPath()));
  qDebug()<<"Record path: "<<record_path_.filePath();
  validateArgs();

}


void CmdDiffLLK::performCommand()
{
  Record r;
  r.setPath(record_path_.absoluteFilePath());

  auto mfcc = f_manager_ptr_->convertRecord(r, config_ptr_->getVectSize(), make_unique<FeatureReaderSilenceCutter>());
  qDebug() <<"Record verified: "+ record_path_.filePath() + " converted to MFCC";
  auto model = model_man_ptr_->operator [](model_name_.toStdString()),
      ubm = model_man_ptr_->operator [](ubm_name_.toStdString());
  Verificator v;
  double llk_model = v.countLogLikehood(*model, mfcc),
      llk_ubm = v.countLogLikehood(*ubm, mfcc);
  double llk_diff = llk_model - llk_ubm;
  qInfo() <<llk_diff;
}

void CmdDiffLLK::acceptExecutor(const CommandExecutor &executor)
{
  executor.execIfRequired(*this);
}

void CmdDiffLLK::validateArgs()
{
  try
  {
    model_man_ptr_->operator [](model_name_.toStdString());
  }catch(std::out_of_range &e)
  {
    QString msg("Model named " + model_name_ + " not found in models dir from config");
    qWarning()<<msg.toLatin1().data();
    throw ErrorCodeException(msg.toStdString(), -1);
  }

  try
  {
    model_man_ptr_->operator [](ubm_name_.toStdString());
  }
  catch(std::out_of_range &e)
  {
    QString msg("UBM named " + ubm_name_ + " not found in models dir from config");
    qWarning()<<msg.toLatin1().data();
    throw ErrorCodeException(msg.toStdString(), -1);
  }

  if(!record_path_.exists())
  {
    QString msg("Verified record " + record_path_.filePath() + " does not exists");
    qWarning()<<msg.toLatin1().data();
    throw ErrorCodeException(msg.toStdString(), -1);
  }
}


