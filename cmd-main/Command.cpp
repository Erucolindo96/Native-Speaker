#include "Command.hpp"

void Command::execute()
{
  checkConfigExistance();
  readConfig();
  reactOnMistakesInConfig();
  loadConfigToMembers();
  checkSyntax();
  readArgs();
  performCommand();
  throw NormallyExitException("");
}

void Command::setFeatureManagerPtr(FeatureManager *ptr)
{
  f_manager_ptr_  = ptr;
}

void Command::setModelManagerPtr(ModelManager *ptr)
{
  model_man_ptr_=ptr;
}

void Command::setConfigManagerPtr(ConfigManager *ptr)
{
  config_ptr_ = ptr;
}

void Command::setRecBaseManagerPtr(RecBaseManager *ptr)
{
  r_base_man_ptr_ = ptr;
}

void Command::setCommandLineParserPtr(QCommandLineParser *ptr)
{
  parser_ptr_ = ptr;
}

void Command::checkConfigExistance()
{
  if(!parser_ptr_->isSet(CommandParamContainer::getOptionConfigPath()))
  {
    QString msg("Path to valid configuration file was not set.");
    qWarning() <<msg;
    throw ErrorCodeException(msg.toStdString(), -1);
  }
  QFileInfo config_path(parser_ptr_->value(CommandParamContainer::getOptionConfigPath()));
  if(!config_path.exists())
  {
    QString msg("Path of configuration is invalid");
    qWarning() <<msg;
    throw ErrorCodeException(msg.toStdString(), -1);
  }
}

void Command::readConfig()
{
  config_ptr_->load(parser_ptr_->value(
                      CommandParamContainer::getOptionConfigPath()).
                    toStdString().c_str());
}

void Command::reactOnMistakesInConfig()
{
  ConfigValidator v;
  try
  {
    v.validateConfiguration(*config_ptr_);
  }catch(ParamNotValid &e)
  {
    qWarning()<<e.what();
    throw ErrorCodeException(e.what(), -1);
  }
}

void Command::loadConfigToMembers()
{
  f_manager_ptr_->setFeatureFolder(config_ptr_->getFeatureFolder().c_str());
  r_base_man_ptr_->setFeatureFolderPath(config_ptr_->getFeatureFolder().c_str());
}
