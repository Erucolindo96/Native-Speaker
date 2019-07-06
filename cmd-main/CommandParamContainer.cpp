#include "CommandParamContainer.hpp"

  QList<QCommandLineOption> CommandParamContainer::getAllValidParams()
  {
    QList<QCommandLineOption> ret;
    //wczytywanie konfiguracji
    ret.append(getOptionConfigPath());

    //dostepne komendy
    ret.append(getOptionCreateModel());
    ret.append(getOptionLearnModel());
    ret.append(getOptionDiffLLK());
    ret.append(getOptionVerifyModel());
    //parametry komend
    ret.append(getOptionDistribCnt());
    ret.append(getOptionModelName());
    ret.append(getOptionRecordsDir());
    ret.append(getOptionIterCnt());
    ret.append(getOptionAlgoName());
    ret.append(getOptionUbmName());
    ret.append(getOptionRecordPath());
    ret.append(getOptionThreshold());

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

  QCommandLineOption CommandParamContainer::getOptionLearnModel()
  {
    return QCommandLineOption("L", "Learn model existing in models dir.");
  }

  QCommandLineOption CommandParamContainer::getOptionDiffLLK()
  {
    return QCommandLineOption("D", "Count difference LLK between verified model and UBM.");
  }

  QCommandLineOption CommandParamContainer::getOptionVerifyModel()
  {
    return QCommandLineOption("V", "Verify record with indicated model and UBM.");
  }




  QCommandLineOption CommandParamContainer::getOptionModelName()
  {
    return QCommandLineOption("m", "Name of required model in command.", "model_name");
  }

  QCommandLineOption CommandParamContainer::getOptionDistribCnt()
  {
    return QCommandLineOption("d", "Number of gaussian distribution in model.", "distrib_cnt");
  }

  QCommandLineOption CommandParamContainer::getOptionRecordsDir()
  {
    return QCommandLineOption("s", "Directory with training records.", "dir_path");
  }

  QCommandLineOption CommandParamContainer::getOptionIterCnt()
  {
    return QCommandLineOption("i", "Number of learning iteration.", "iter_cnt");
  }

  QCommandLineOption CommandParamContainer::getOptionAlgoName()
  {
    return QCommandLineOption("a", "Chosen algo of learning.", "algo_name");
  }

  QCommandLineOption CommandParamContainer::getOptionUbmName()
  {
    return QCommandLineOption("u", "Name of UBM.", "ubm_name");
  }

  QCommandLineOption CommandParamContainer::getOptionRecordPath()
  {
    return QCommandLineOption("r", "Path to verified record.", "record_path");
  }

  QCommandLineOption CommandParamContainer::getOptionThreshold()
  {
    return QCommandLineOption("t", "Verification threshold", "value");
  }
