#include "CommandParamContainer.hpp"

  QList<QCommandLineOption> CommandParamContainer::getAllValidParams()
  {
    QList<QCommandLineOption> ret;
    ret.append(getOptionConfigPath());

    ret.append(getOptionCreateModel());
    ret.append(getOptionLearnModel());

    ret.append(getOptionDistribCnt());
    ret.append(getOptionModelName());
    ret.append(getOptionRecordsDir());
    ret.append(getOptionIterCnt());
    ret.append(getOptionAlgoName());

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

  QCommandLineOption CommandParamContainer::getOptionLearnModel()
  {
    return QCommandLineOption("L", "Learn model existing in models dir");
  }

  QCommandLineOption CommandParamContainer::getOptionRecordsDir()
  {
    return QCommandLineOption("s", "Directory with training records", "dir_path");
  }

  QCommandLineOption CommandParamContainer::getOptionIterCnt()
  {
    return QCommandLineOption("i", "Number of learning iteration", "iter_cnt");
  }

  QCommandLineOption CommandParamContainer::getOptionAlgoName()
  {
    return QCommandLineOption("a", "Chosen algo of learning", "algo_name");
  }
