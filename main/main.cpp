//#include "mainwindow.hpp"
//#include <QApplication>
#include<alize/alize.h>

#include"models/diagonal_model.hpp"
#include"models/verificator.hpp"
#include"features/FeatureReaderSilenceCutter.hpp"
#include"models/learning_algo.hpp"
#include"utils/utils.hpp"
#include"dao/FileModelDao.hpp"
#include"windows/MainWindow.hpp"
#include<QtCore/QDir>

using namespace std;
using namespace alize;
using namespace utils;

/**
 * @brief verification Funkcja przeprowadzająca weryfikację modelu na podstawie przekazanych do main() parametrów
 * @param argc argc otrzymywany przez funkcję main()
 * @param argv argv otrzymywany przez funkcję main()
 * @return Zwraca zmienną logiczną, mówiąca, czy weryfikacja była pozytywna
 */
int verification(uint32_t argc, char *argv[])
{
  string model_dir = argv[2], model_name =argv[3], ubm_name = argv[4];
  double threshold = stod(argv[5]);
  string f_path = argv[6], ext = "";

  FeatureReader f_reader;
  f_reader.setFeatureDir("");
  auto f_vec = f_reader.readFile(f_path, ext);

  FileModelDao dao;
  dao.setModelsDir(model_dir);
  dao.setVectSize(f_vec[0].getVectSize());

  auto ubm = dao.readModel(ubm_name);
//  cout<<"UBM "<<ubm->getName()<<" readed"<<endl<<endl;

  auto model = dao.readModel(model_name);
//  cout<<"Model "<<model->getName()<<" readed"<<endl<<endl;

  Verificator v(threshold);
//  cout<<"Feature Vec size: "<<f_vec.size()<<endl<<endl;

  cout<<"Log Likehood for model "<<model->getName() <<":"<<v.countLogLikehood(*model, f_vec)<<endl;
  cout<<"Log Likehood for ubm "<<ubm->getName() <<":"<<v.countLogLikehood(*ubm, f_vec)<<endl;

  bool is_speaker_voice = v.verifyModel(*model, f_vec, *ubm);
  cout<<"Verificator return: "<<is_speaker_voice<<endl;
  if(is_speaker_voice)
  {
//    cout<<"This is speaker voice"<<endl;
  }
  else
  {
//    cout<<"No, this is not a speaker voice"<<endl;
  }
  return is_speaker_voice;
}

void learnExistModel(uint32_t  argc,char *argv[],  const string &model_dir)
{
  string dir_with_mfcc = argv[2], model_name = argv[3];
  vector<Feature> training_features;
  FeatureReader reader(dir_with_mfcc);
  vector<Feature> features_vec;
  for(uint32_t i = 4; i < argc; ++i)
  {
    cout<<"Load file: "<<argv[i]<<endl;
    features_vec = reader.readFile(argv[i], "");
    training_features.insert(training_features.end(), features_vec.begin(), features_vec.end());
    cout<<"Training features in "<<argv[i]<<" : "<<features_vec.size()<<endl<<endl;
  }
  cout<<"All training features: "<<training_features.size()<<endl<<endl;

  FileModelDao dao;
  dao.setModelsDir(model_dir);
  dao.setVectSize(features_vec[0].getVectSize());
  auto model = dao.readModel(model_name);
  //DiagonalModel model(D_CNT ,training_features[0].getVectSize());
  //model.setName(model_name);

  ExpectationMaximalizationAlgo algo;
  const uint32_t ITERATIONS = 5;
  algo.learnModel(*model,training_features, ITERATIONS );
  cout<<"Model "<<model->getName() <<" have learned"<<endl;

  dao.writeModel(*model);
  cout<<"Model "<<model->getName()<<" saved to file"<<endl<<endl;

  cout<<"Likehood for last of training feature vec: "<<model->countLikehoodWithWeight(features_vec)<<endl;

}

void createModel(uint32_t  argc,char *argv[],  const string &model_dir)
{
  const uint32_t D_CNT = 512;
  string dir_with_mfcc = argv[2], model_name = argv[3];
  vector<Feature> training_features;
  FeatureReader reader(dir_with_mfcc);
  vector<Feature> features_vec;
  for(uint32_t i = 4; i < argc; ++i)
  {
    cout<<"Load file: "<<argv[i]<<endl;
    features_vec = reader.readFile(argv[i], "");
    training_features.insert(training_features.end(), features_vec.begin(), features_vec.end());
    cout<<"Training features in "<<argv[i]<<" : "<<features_vec.size()<<endl<<endl;
  }
  cout<<"All training features: "<<training_features.size()<<endl<<endl;

  DiagonalModel model(D_CNT ,training_features[0].getVectSize());
  model.setName(model_name);

  ExpectationMaximalizationAlgo algo;
  const uint32_t ITERATIONS = 5;
  algo.learnModel(model,training_features, ITERATIONS );
  cout<<"Model "<<model.getName() <<" have learned"<<endl;

  FileModelDao dao;
  dao.setModelsDir(model_dir);
  dao.setVectSize(training_features[0].getVectSize());
  dao.writeModel(model);
  cout<<"Model "<<model.getName()<<" saved to file"<<endl<<endl;

  cout<<"Likehood for last of training feature vec: "<<model.countLikehoodWithWeight(features_vec)<<endl;
}

/**
 *
 * Mozliwe formaty komend:
 *
 * 1. Uczenie modeli - main -l [folder próbek] [nazwa modelu] [pliki z probkami]
 * 2. Weryfikacja - main -r [folder modeli] [nazwa modelu] [nazwa ubm'a] [próg] [sciezka próbki do rozpoznania]
 * 3. Douczenie - main -ll  [folder próbek] [nazwa modelu] [pliki z probkami]
 * Nazwy plików podajemy bez rozszerzeń.
 * Rozszerzenia plików z próbkami - .mfcc
 * Rozszerzenia plików  z modelami - .xml
 *
*/
int main(int argc, char *argv[])
{
  try
  {
    const std::string model_dir = "models/";
    if(argc > 1)
    {
      if(string(argv[1]) == string("-l"))
      {
        createModel(argc, argv, model_dir);
        return 0;
      }
      if(string(argv[1]) == string("-ll"))
      {
        learnExistModel(argc, argv, model_dir);
        return 0;
      }
      if(string(argv[1]) == string("-r"))
      {
        return verification(argc, argv);

      }
    }
    QApplication app(argc, argv);
    MainWindow window;
    window.show();
    return app.exec();


  }
  catch(alize::Exception &e)
  {
    cout<<e.toString().c_str()<<endl;
  }
  catch(std::exception &e)
  {
    cout<<e.what()<<endl;
  }
  return 0;
/*
  try{
  if(argc < 7)
    return 0;
  verification(argc, argv);
  }
  catch(alize::Exception &e)
  {
    cout<<e.toString().c_str()<<endl;
  }
  catch(alize::Object &e)
  {
    cout<<"alize object"<<endl;
  }
  catch(std::exception &e)
  {
    cout<<e.what()<<endl;
  }
*/
/*
  alize::Config conf, conf_server;
  conf.setParam("saveMixtureFileFormat", "XML");
  conf.setParam("saveMixtureFileExtension", ".xml");
  conf.setParam("saveMixtureServerFileFormat", "XML");
  conf.setParam("saveMixtureServerFileExtension", ".xml");
  conf.setParam("loadMixtureFileFormat", "XML");
  conf.setParam("loadMixtureFileExtension", ".xml");
  conf.setParam("mixtureFilesPath", "./");

  try
  {
  conf_server.setParam("vectSize", to_string(12).c_str());
  MixtureServer s(conf_server);
  s.createMixtureGD(10);
  MixtureServerFileWriter writer("model1", conf);
  writer.writeMixtureServer(s);
  }
  catch(alize::ParamNotFoundInConfigException &e)
  {
    cout<<e.toString().c_str()<<endl;
  }

*/
}
