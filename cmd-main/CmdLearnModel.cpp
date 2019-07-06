#include "CmdLearnModel.hpp"



void CmdLearnModel::checkSyntax()const
{
  if(!parser_ptr_->isSet(CommandParamContainer::getOptionModelName()))
  {
    QString msg("Model name was not set");
    qWarning()<<msg.toLatin1().data();
    throw ErrorCodeException(msg.toStdString(), -1);
  }
  if(!parser_ptr_->isSet(CommandParamContainer::getOptionRecordsDir()))
  {
    QString msg("Training record directory was not set");
    qWarning()<<msg.toLatin1().data();
    throw ErrorCodeException(msg.toStdString(), -1);
  }
  if(!parser_ptr_->isSet(CommandParamContainer::getOptionIterCnt()))
  {
    QString msg("Number of learning iteration was not set");
    qWarning()<<msg.toLatin1().data();
    throw ErrorCodeException(msg.toStdString(), -1);
  }
  if(!parser_ptr_->isSet(CommandParamContainer::getOptionAlgoName()))
  {
    QString msg("Learning algo was not set");
    qWarning()<<msg.toLatin1().data();
    throw ErrorCodeException(msg.toStdString(), -1);
  }
}

void CmdLearnModel::readArgs()
{
  model_man_ptr_->loadModels(*config_ptr_);
  model_name_ = parser_ptr_->value(CommandParamContainer::getOptionModelName());
  qDebug()<<"Model name: " + model_name_;

  record_dir_.setPath(parser_ptr_->value(CommandParamContainer::getOptionRecordsDir()));
  qDebug()<<"Record dir path: " + record_dir_.path();

  iter_is_int_ = false;
  iters_cnt_ = parser_ptr_->value(CommandParamContainer::getOptionIterCnt()).toInt(&iter_is_int_);
  qDebug()<<"Iters cnt: " + QString::number(iters_cnt_);

  algo_name_ = parser_ptr_->value(CommandParamContainer::getOptionAlgoName());
  qDebug()<<"Algo name: " + algo_name_;

  algo_ptr_ = AlgoManager::getAlgoByName(algo_name_);
  validateArgs();

}


void CmdLearnModel::performCommand()
{
  auto learning_recs = RecBaseManager::getWavRecordsFromDir(record_dir_.absolutePath());
  auto features = f_manager_ptr_->convertRecord(learning_recs,
                                                config_ptr_->getVectSize(),
                                                make_unique<FeatureReaderSilenceCutter>());
  auto model_ptr = model_man_ptr_->operator [](model_name_.toStdString());
  qInfo()<<("Start learning od model: " + model_name_).toLatin1().data();
  qInfo()<<("Learning Algo: " + algo_name_).toLatin1().data();
  qInfo()<<("Iteration count: " + QString::number(iters_cnt_)).toLatin1().data();
  qInfo()<<("Model containing training records: " +  record_dir_.path()).toLatin1().data();
  for(int32_t i = 0; i < iters_cnt_; ++i)
  {
    algo_ptr_->learnModel(*model_ptr, features, 1);
    qInfo()<<("Iteration " + QString::number(i) + " complete!").toLatin1().data();
  }
  qInfo()<<"Learning complete.";
  for(auto r: learning_recs)
  {
    r_base_man_ptr_->setRecordToBase(r, model_name_.toStdString());
  }
  qInfo()<<"Training records saved in records base";
}

void CmdLearnModel::acceptExecutor(const CommandExecutor &executor)
{
  executor.execIfRequired(*this);
}

void CmdLearnModel::validateArgs()
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
  if(!record_dir_.exists())
  {
    QString msg("Training records dir " + record_dir_.path() + "does not exists");
    qWarning()<<msg.toLatin1().data();
    throw ErrorCodeException(msg.toStdString(), -1);
  }
  if(!iter_is_int_ || iters_cnt_ <= 0)
  {
    QString msg("Iters cnt is not positive integer value");
    qWarning()<<msg.toLatin1().data();
    throw ErrorCodeException(msg.toStdString(), -1);
  }
  if(algo_ptr_ == nullptr)
  {
    QString msg("Algo name was not recognized as valid learning algo name");
    qWarning()<<msg.toLatin1().data();
    throw ErrorCodeException(msg.toStdString(), -1);
  }


}
