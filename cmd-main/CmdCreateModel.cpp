#include "CmdCreateModel.hpp"

void CmdCreateModel::checkSyntax()const
{
  throw std::runtime_error("TODO");
}
void CmdCreateModel::readArgs()
{
  throw std::runtime_error("TODO");
}

void CmdCreateModel::performCommand()
{
  throw std::runtime_error("TODO");
}

void CmdCreateModel::acceptExecutor(const CommandExecutor &executor)
{
  executor.execIfRequired(*this);
}
