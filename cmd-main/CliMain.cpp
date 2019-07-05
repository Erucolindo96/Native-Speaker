#include "CliMain.hpp"
using namespace std;
CliMain::CliMain(int &argc, char ** argv):QCoreApplication(argc, argv),
  parser_ptr_(make_unique<QCommandLineParser>()),
  model_man_ptr_(make_unique<ModelManager>()),
  f_man_ptr_(make_unique<FeatureManager>()),
  r_base_man_ptr_(make_unique<RecBaseManager>()),
  config_ptr_(make_unique<ConfigManager>())
{
  throw std::runtime_error("TODO");
}

void CliMain::execute()
{
  throw std::runtime_error("TODO");
}
