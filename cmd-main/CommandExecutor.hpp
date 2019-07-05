﻿#ifndef COMMANDEXECUTOR_HPP
#define COMMANDEXECUTOR_HPP

#include<memory>
#include<QCommandLineParser>
#include"cmd-main/CommandParamContainer.hpp"
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

  void setCommandLineParserPtr(QCommandLineParser *ptr);
protected:
  QCommandLineParser *parser_ptr_;
};

#endif // COMMANDEXECUTOR_HPP
