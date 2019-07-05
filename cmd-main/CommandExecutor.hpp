#ifndef COMMANDEXECUTOR_HPP
#define COMMANDEXECUTOR_HPP

#include<memory>

class CmdCreateModel;

class CommandExecutor
{
public:
  CommandExecutor() = default;
  CommandExecutor(const CommandExecutor &o) = default;
  CommandExecutor& operator=(const CommandExecutor &o) = default;
  CommandExecutor(CommandExecutor &&o) = default;
  CommandExecutor& operator=(CommandExecutor &&o) = default;

  virtual ~CommandExecutor() = default;

  void execIfRequired(CmdCreateModel &cmd)const;

};

#endif // COMMANDEXECUTOR_HPP
