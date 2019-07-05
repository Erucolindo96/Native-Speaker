#include "CommandExecutor.hpp"
#include"cmd-main/CmdCreateModel.hpp"

void CommandExecutor::execIfRequired(CmdCreateModel &cmd)const
{
  if(parser_ptr_->isSet(CommandParamContainer::getOptionCreateModel()))
  {
    cmd.execute();
  }
}


void CommandExecutor::setCommandLineParserPtr(QCommandLineParser *ptr)
{
  parser_ptr_ = ptr;
}
