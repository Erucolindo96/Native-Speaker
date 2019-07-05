#include "CmdCreateModel.hpp"

void CmdCreateModel::checkSyntax()const
{
  if(!parser_ptr_->isSet(CommandParamContainer::getOptionModelName()))
  {
    QString msg("Model name was not set");
    qWarning()<<msg;
    throw ErrorCodeException(msg.toStdString(), -1);
  }
  if(!parser_ptr_->isSet(CommandParamContainer::getOptionDistribCnt()))
  {
    QString msg("Distribution count was not set.");
    qWarning()<<msg;
    throw ErrorCodeException(msg.toStdString(), -1);
  }

}
void CmdCreateModel::readArgs()
{
  //tu powinna być walidacja nazwy modelu i ilosci gestosci
  bool is_int =false;
  d_cnt_ = parser_ptr_->value(CommandParamContainer::getOptionDistribCnt()).toInt(&is_int);
  if(!is_int || d_cnt_ <= 0)
  {
    QString msg("Distribution count must be a positive integer number.");
    qWarning()<<msg;
    throw ErrorCodeException(msg.toStdString(), -1);
  }
  model_name_ = parser_ptr_->value(CommandParamContainer::getOptionModelName());

}

void CmdCreateModel::performCommand()
{
  std::shared_ptr<GmmModel> model = make_shared<DiagonalModel>(d_cnt_, config_ptr_->getVectSize());
  model->setName(model_name_.toStdString());
  model_man_ptr_->addModel(*config_ptr_, model);
}

void CmdCreateModel::acceptExecutor(const CommandExecutor &executor)
{
  executor.execIfRequired(*this);
}
