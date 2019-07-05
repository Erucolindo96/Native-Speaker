#ifndef COMMANDPARAMCONTAINER_HPP
#define COMMANDPARAMCONTAINER_HPP

#include<QCommandLineOption>
#include<QCommandLineParser>

class CommandParamContainer
{
public:

  static QList<QCommandLineOption> getAllValidParams();

  static QCommandLineOption getOptionConfigPath();
  static QCommandLineOption getOptionCreateModel();
  static QCommandLineOption getOptionModelName();
  static QCommandLineOption getOptionDistribCnt();
};

#endif // COMMANDPARAMCONTAINER_HPP
