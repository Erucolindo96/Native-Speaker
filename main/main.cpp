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

#include"features/FeatureManager.hpp"
#include"record-base/RecBaseManager.hpp"
#include"models/ModelManager.hpp"
using namespace std;
using namespace alize;
using namespace utils;


void printFeature(const alize::Feature f)
{
  cout<<"Wektor cech: "<<endl;
  for(uint32_t i=0; i< f.getVectSize();++i)
  {
    cout<<f[i]<<endl;
  }
}

std::vector<Record> getWavRecordsFromDir(const std::string &dir_path)
{
  std::vector<Record> recs;
  QDir records(dir_path.c_str());
  records.setFilter(QDir::NoDotAndDotDot| QDir::Files);
  records.setNameFilters({"*.wav"});
  Record r;
  for(auto file: records.entryInfoList())
  {
    r.setPath(file.absoluteFilePath());
    recs.push_back(r);
  }
  return recs;
}

void LLKDifference(char *argv[])
{
  const string MODEL_DIR = argv[2], MODEL_NAME = argv[3], UBM_NAME = argv[4];
  const double THRESHOLD = stod(argv[5]);
  const uint32_t F_SIZE = stoi(argv[6]);
  const string R_PATH = argv[7], FEATURE_FOLDER = ".";

  FeatureManager f_man;
  f_man.setFeatureFolder(FEATURE_FOLDER.c_str());

  Record rec;
  rec.setPath(R_PATH.c_str());
  auto mfcc = f_man.convertRecord(rec, F_SIZE);

  FileModelDao dao;
  dao.setModelsDir(MODEL_DIR);
  dao.setVectSize(F_SIZE);

  auto ubm = dao.readModel(UBM_NAME);
  auto model = dao.readModel(MODEL_NAME);

  Verificator v(THRESHOLD);
  double diff = v.countLogLikehood(*model, mfcc) - v.countLogLikehood(*ubm, mfcc);
  cout<<diff<<endl;
}
/**
 * @brief verification Funkcja przeprowadzająca weryfikację modelu na podstawie przekazanych do main() parametrów
 * @param argc argc otrzymywany przez funkcję main()
 * @param argv argv otrzymywany przez funkcję main()
 * @return Zwraca zmienną logiczną, mówiąca, czy weryfikacja była pozytywna
 */
bool verification(char *argv[])
{
  const string MODEL_DIR = argv[2], MODEL_NAME = argv[3], UBM_NAME = argv[4];
  const double THRESHOLD = stod(argv[5]);
  const uint32_t F_SIZE = stoi(argv[6]);
  const string R_PATH = argv[7], FEATURE_FOLDER = ".";

  FeatureManager f_man;
  f_man.setFeatureFolder(FEATURE_FOLDER.c_str());

  Record rec;
  rec.setPath(R_PATH.c_str());
  auto mfcc = f_man.convertRecord(rec, F_SIZE);

  FileModelDao dao;
  dao.setModelsDir(MODEL_DIR);
  dao.setVectSize(F_SIZE);

  auto ubm = dao.readModel(UBM_NAME);
  auto model = dao.readModel(MODEL_NAME);

  Verificator v(THRESHOLD);

  bool is_speaker_voice = v.verifyModel(*model, mfcc, *ubm);
  cout<<is_speaker_voice<<endl;
  return is_speaker_voice;
}

void learnExistModel(uint32_t  argc,char *argv[])
{
     throw std::runtime_error("TODO");
}

void createModel(char *argv[])
{
  const string MODELS_DIR = argv[2], MODEL_NAME = argv[3];
  const uint32_t D_CNT = std::stoi(argv[4]), F_SIZE = std::stoi(argv[5]),
      ITERS = std::stoi(argv[6]);
  const string REC_DIR = argv[7], FEATURE_FOLDER = ".";

  FeatureManager f_man;
  f_man.setFeatureFolder(FEATURE_FOLDER.c_str());

  auto records = getWavRecordsFromDir(REC_DIR);
  auto mfcc_vecs = f_man.convertRecord(records, F_SIZE);
  cout<<"Ilośc wektorów cech: "<<mfcc_vecs.size()<<endl;
  DiagonalModel model(D_CNT ,F_SIZE);
  model.setName(MODEL_NAME);

  ExpectationMaximalizationAlgo algo;
  for(uint32_t i = 0; i< ITERS; ++i)
  {
    algo.learnModel(model, mfcc_vecs, 1);
    cout<<"Iteracja nr "<<i<<" uczenia modelu ukonczona"<<endl;
  }
  cout<<"Uczenie modelu zakończone"<<endl;

  FileModelDao dao;
  dao.setModelsDir(MODELS_DIR);
  dao.setVectSize(F_SIZE);
  dao.writeModel(model);

  cout<<"Model "<<model.getName()<<" saved to file"<<endl<<endl;
  cout<<"Likehood for first of training feature vec: "<<model.countLikehoodWithWeight(mfcc_vecs[0])<<endl;
  printFeature(mfcc_vecs[100]);
}

/**
 *
 * Mozliwe formaty komend:
 *
 * 1. Uczenie modeli - main -l [folder modeli] [nazwa modelu] [ilość rozkładów normalnych] [dł wektora cech] [iteracje uczenia] [folder z próbkami]
 * 2. Weryfikacja - main -r [folder modeli] [nazwa modelu] [nazwa ubm'a] [próg] [dł wektora cech] [sciezka nagrania weryfikowanego]
 * 3. Różnica LLK - main -rr [folder modeli] [nazwa modelu] [nazwa ubm'a] [próg] [dł wektora cech] [sciezka nagrania weryfikowanego]
 * //// 3. Douczenie - main -ll  [folder próbek] [nazwa modelu] [pliki z probkami]
 * //Nazwy plików podajemy bez rozszerzeń.
 *
 * //Rozszerzenia plików z próbkami - .mfcc
 * Rozszerzenia plików  z modelami - .xml
 *
*/
int main(int argc, char *argv[])
{
  try
  {
    if(argc > 1)
    {
      if(string(argv[1]) == string("-l"))
      {
        createModel(argv);
        return 0;
      }
      if(string(argv[1]) == string("-r"))
      {
        return !verification(argv);//negacja, aby poprawna weryfikacja dała 0
      }
      if(string(argv[1]) == string("-rr"))
      {
        LLKDifference(argv);
        return 0;
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

}
