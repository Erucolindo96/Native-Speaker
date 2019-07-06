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

  static QCommandLineOption getOptionLearnModel();
  static QCommandLineOption getOptionRecordsDir();
  static QCommandLineOption getOptionIterCnt();
  static QCommandLineOption getOptionAlgoName();



};

#endif // COMMANDPARAMCONTAINER_HPP
