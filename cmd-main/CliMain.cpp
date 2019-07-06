#include "CliMain.hpp"
using namespace std;
CliMain::CliMain(int &argc, char ** argv):QCoreApplication(argc, argv),
  parser_ptr_(make_unique<QCommandLineParser>()),
  model_man_ptr_(make_unique<ModelManager>()),
  f_man_ptr_(make_unique<FeatureManager>()),
  r_base_man_ptr_(make_unique<RecBaseManager>()),
  config_ptr_(make_unique<ConfigManager>())
{
  commands_.push_back(make_unique<CmdCreateModel>());
  commands_.push_back(make_unique<CmdLearnModel> ());
  commands_.push_back(make_unique<CmdDiffLLK>    ());
  commands_.push_back(make_unique<CmdVerifyModel>());

  for(unique_ptr<Command> &cmd: commands_)
  {
    cmd->setCommandLineParserPtr(parser_ptr_.get());
    cmd->setConfigManagerPtr(config_ptr_.get());
    cmd->setFeatureManagerPtr(f_man_ptr_.get());
    cmd->setModelManagerPtr(model_man_ptr_.get());
    cmd->setRecBaseManagerPtr(r_base_man_ptr_.get());
  }

}

void CliMain::execute()
{
  try
  {
    prepareParser();
    CommandExecutor executor;
    executor.setCommandLineParserPtr(parser_ptr_.get());
    for(auto &cmd: commands_)
    {
      cmd->acceptExecutor(executor);
    }
  }catch(NormallyExitException &e)
  {
    qDebug()<<"normally exit exception handler";
    exit(0);
  }
  catch(ErrorCodeException &e)
  {
    qDebug()<<"error code exception handler";
    exit(e.error_code_);
  }
  catch(alize::Exception &e)
  {
    qCritical()<<e.toString().c_str();
    exit(-1);
  }
  catch(std::exception &e)
  {
    qCritical()<<e.what();
    exit(-1);
  }

}

void CliMain::prepareParser()
{
  parser_ptr_->addOptions(CommandParamContainer::getAllValidParams());
  parser_ptr_->addHelpOption();
//  parser_ptr_->addVersionOption();
  parser_ptr_->process(*this);
}
