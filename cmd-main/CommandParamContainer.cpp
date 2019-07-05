#include "CommandParamContainer.hpp"

  QList<QCommandLineOption> CommandParamContainer::getAllValidParams()
  {
    QList<QCommandLineOption> ret;
    ret.append(getOptionConfigPath());
    ret.append(getOptionCreateModel());
    ret.append(getOptionDistribCnt());
    ret.append(getOptionModelName());
    return ret;
  }


  QCommandLineOption CommandParamContainer::getOptionConfigPath()
  {
    return QCommandLineOption("c", "Path to configuration file.", "config_path");
  }

  QCommandLineOption CommandParamContainer::getOptionCreateModel()
  {
    return QCommandLineOption("C", "Create new model in models dir.");
  }

  QCommandLineOption CommandParamContainer::getOptionModelName()
  {
    return QCommandLineOption("m", "Name of required model in command", "model_name");
  }

  QCommandLineOption CommandParamContainer::getOptionDistribCnt()
  {
    return QCommandLineOption("d", "Number of gaussian distribution in model", "distrib_cnt");
  }
