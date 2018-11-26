//#include "mainwindow.hpp"
//#include <QApplication>
#include<alize/alize.h>
using namespace std;
using namespace alize;
#include"models/diagonal_model.hpp"
#include"models/verificator.hpp"
#include"features/FeatureReader.hpp"
#include"models/learning_algo.hpp"
#include"utils/utils.hpp"

void learnMyModel(GmmModel &me)
{
  uint32_t LEARN_ITER = 20;
  std::vector<Feature> jeden, pokoj, kubek, komputer,kolega;
  FeatureReader reader("probki/krzysiek/");
  jeden = reader.readFile("jeden", ".mfcc");
  pokoj = reader.readFile("pokoj", ".mfcc");
  kubek = reader.readFile("kubek", ".mfcc");
  komputer = reader.readFile("komputer", ".mfcc");
  kolega = reader.readFile("kolega", ".mfcc");
  std::vector<Feature> summ(jeden);
  summ.insert(summ.end(), pokoj.begin(), pokoj.end());
  summ.insert(summ.end(), kubek.begin(), kubek.end());
  summ.insert(summ.end(), komputer.begin(), komputer.end());
  summ.insert(summ.end(), kolega.begin(), kolega.end());

  cout<<"elems in jeden: "<<jeden.size()<<endl;
  cout<<"elems in pokoj: "<<pokoj.size()<<endl;
  cout<<"elems in nauczanie: "<<kubek.size()<<endl;
  cout<<"elems in komputer: "<<komputer.size()<<endl;
  cout<<"elems in kolega: "<<kolega.size()<<endl;
  cout<<"elems in summ: "<<summ.size()<<endl;

  ExpectationMaximalizationAlgo algo;
  algo.learnModel(me, summ, LEARN_ITER);

  cout<<"LLk dla słowa Jeden: "<<log(me.countLikehoodWithWeight(jeden))<<endl;
  cout<<"LLk dla słowa pokój: "<<log(me.countLikehoodWithWeight(pokoj))<<endl;
  cout<<"LLk dla słowa kubek: "<<log(me.countLikehoodWithWeight(kubek))<<endl;
  cout<<"LLk dla słowa komputer: "<<log(me.countLikehoodWithWeight(komputer))<<endl;
  cout<<"LLk dla słowa kolega: "<<log(me.countLikehoodWithWeight(kolega))<<endl;


}

void learnUbmModel(GmmModel &ubm, GmmModel &me)
{
  uint32_t LEARN_ITER = 20;
  std::vector<Feature> ulica, wawa, nauczanie, drzewo,ksiazka, kutas;
  FeatureReader reader("probki/pawel/");
  ulica = reader.readFile("ulica", ".mfcc");
  wawa = reader.readFile("wawa", ".mfcc");
  nauczanie = reader.readFile("nauczanie", ".mfcc");
  drzewo = reader.readFile("drzewo", ".mfcc");
  ksiazka = reader.readFile("ksiazka", ".mfcc");
  kutas = reader.readFile("kutas",".mfcc");

  std::vector<Feature> summ(ulica);
  summ.insert(summ.end(), wawa.begin(), wawa.end());
  summ.insert(summ.end(), nauczanie.begin(), nauczanie.end());
  summ.insert(summ.end(), drzewo.begin(), drzewo.end());
  summ.insert(summ.end(), ksiazka.begin(), ksiazka.end());
  summ.insert(summ.end(), kutas.begin(), kutas.end());

  cout<<"elems in ulica: "<<ulica.size()<<endl;
  cout<<"elems in wawa: "<<wawa.size()<<endl;
  cout<<"elems in nauczanie: "<<nauczanie.size()<<endl;
  cout<<"elems in drzewo: "<<drzewo.size()<<endl;
  cout<<"elems in ksiazka: "<<ksiazka.size()<<endl;
  cout<<"elems in kutas: "<<kutas.size()<<endl;
  cout<<"elems in summ: "<<summ.size()<<endl;

  ExpectationMaximalizationAlgo algo;
  algo.learnModel(ubm, summ, LEARN_ITER);

  cout<<"LLk dla słowa ulica: "<<log(ubm.countLikehoodWithWeight(ulica))<<endl;
  cout<<"LLk dla słowa pokój: "<<log(ubm.countLikehoodWithWeight(wawa))<<endl;
  cout<<"LLk dla słowa nauczanie: "<<log(ubm.countLikehoodWithWeight(nauczanie))<<endl;
  cout<<"LLk dla słowa drzewo: "<<log(ubm.countLikehoodWithWeight(drzewo))<<endl;
  cout<<"LLk dla słowa ksiazka: "<<log(ubm.countLikehoodWithWeight(ksiazka))<<endl;
  cout<<"LLk dla słowa kutas: "<<log(ubm.countLikehoodWithWeight(kutas))<<endl;

  cout<<"LLk dla słowa ulica: "<<log(me.countLikehoodWithWeight(ulica))<<endl;
  cout<<"LLk dla słowa pokój: "<<log(me.countLikehoodWithWeight(wawa))<<endl;
  cout<<"LLk dla słowa nauczanie: "<<log(me.countLikehoodWithWeight(nauczanie))<<endl;
  cout<<"LLk dla słowa drzewo: "<<log(me.countLikehoodWithWeight(drzewo))<<endl;
  cout<<"LLk dla słowa ksiazka: "<<log(me.countLikehoodWithWeight(ksiazka))<<endl;
  cout<<"LLk dla słowa kutas: "<<log(me.countLikehoodWithWeight(kutas))<<endl;

}

int main(int argc, char *argv[])
{

/*
  uint32_t DISTRIB_CNT = 512, FEATURE_SIZE = 12;

  DiagonalModel speaker_model(DISTRIB_CNT, FEATURE_SIZE), ubm_model(DISTRIB_CNT, FEATURE_SIZE);
  learnMyModel(speaker_model);
  learnUbmModel(ubm_model, speaker_model);
*/
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


}
