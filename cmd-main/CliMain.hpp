#ifndef CLIMAIN_HPP
#define CLIMAIN_HPP

#include<QCoreApplication>
#include<QCommandLineParser>
#include<QVector>
#include<memory>
#include"cmd-main/Command.hpp"
#include"features/FeatureManager.hpp"
#include"models/ModelManager.hpp"
#include"configuration/ConfigManager.hpp"
#include"record-base/RecBaseManager.hpp"
#include"cmd-main/CmdCreateModel.hpp"
#include"cmd-main/CmdLearnModel.hpp"
#include<vector>
#include<QDebug>
class CliMain: public QCoreApplication
{
  Q_OBJECT
public:

  /**
   * @brief CliMain Konstruktor klasy. Wykonuje dokładnie to, co konstruktor nadklasy
   * @param argc argc przekazany do fcji main
   * @param argv argv przekazane do fcji main
   */
  CliMain(int &argc, char * argv[]);

  /**
   * @brief execute Uruchamia kod, wykonujący zleconą przez użytkownika komendę
   *
   */
  void execute();

  ~CliMain() override = default;
protected:
  std::unique_ptr<QCommandLineParser> parser_ptr_;
  std::unique_ptr<ModelManager> model_man_ptr_;
  std::unique_ptr<FeatureManager> f_man_ptr_;
  std::unique_ptr<RecBaseManager> r_base_man_ptr_;
  std::unique_ptr<ConfigManager> config_ptr_;

  std::vector<std::unique_ptr<Command>> commands_;

  void prepareParser();
};

#endif // CLIMAIN_HPP
