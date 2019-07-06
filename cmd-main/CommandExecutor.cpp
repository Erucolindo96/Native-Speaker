#include "CommandExecutor.hpp"
#include"cmd-main/CmdCreateModel.hpp"
#include"cmd-main/CmdLearnModel.hpp"
#include"cmd-main/CmdDiffLLK.hpp"
#include"cmd-main/CmdVerifyModel.hpp"
void CommandExecutor::execIfRequired(CmdCreateModel &cmd)const
{
  if(parser_ptr_->isSet(CommandParamContainer::getOptionCreateModel()))
  {
    cmd.execute();
  }
}

void CommandExecutor::execIfRequired(CmdLearnModel &cmd)const
{
  if(parser_ptr_->isSet(CommandParamContainer::getOptionLearnModel()))
  {
    cmd.execute();
  }
}

void CommandExecutor::execIfRequired(CmdDiffLLK &cmd)const
{
  if(parser_ptr_->isSet(CommandParamContainer::getOptionDiffLLK()))
  {
    cmd.execute();
  }
}

void CommandExecutor::execIfRequired(CmdVerifyModel &cmd)const
{
  if(parser_ptr_->isSet(CommandParamContainer::getOptionVerifyModel()))
  {
    cmd.execute();
  }
}



void CommandExecutor::setCommandLineParserPtr(QCommandLineParser *ptr)
{
  parser_ptr_ = ptr;
}
