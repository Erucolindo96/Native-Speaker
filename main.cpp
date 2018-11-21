//#include "mainwindow.hpp"
//#include <QApplication>
#include<alize/alize.h>
using namespace std;
using namespace alize;

class A
{
public:
  std::string s_;
  A() = default;
  A(const A &other) = default;
  A& operator=(const A &other) = default;

};

int main(int argc, char *argv[])
{
  const uint32_t VECT_SIZE = 10;
  const string VECT_SIZE_STR = "10";
    //QApplication a(argc, argv);
    //MainWindow w;
    //w.show();
    alize::Config cfn;
    cfn.setParam("mixtureFilesPath", "../");
    cfn.setParam("saveMixtureFileFormat", "XML");
    cfn.setParam("saveMixtureFileExtension", ".mixture");

    cfn.setParam("loadMixtureFileFormat", "XML");
    cfn.setParam("loadMixtureFileExtension", ".mixture");

    cfn.setParam("saveMixtureServerFileFormat", "XML");
    cfn.setParam("saveMixtureServerFileExtension", ".mixture_server");
    cfn.setParam("loadMixtureFileBigEndian", "true");

    cfn.setParam("vectSize", "1");
    cfn.setParam("mixtureDistribCount", "512");
    cfn.setParam("maxLLK", "100");
    cfn.setParam("minLLK", "-100");
    cfn.setParam("featureServerMemAlloc", "1000000");

    cfn.setParam("loadFeatureFileExtension", ".mfcc");
    cfn.setParam("featureFilesPath", "./");
    try{
    FeatureFileReaderSPro4 reader("test", cfn);
    Feature f(cfn);
    reader.readFeature(f);
    for(uint32_t i=0; i< 12; ++i)
    {
      cout<<f[i]<<endl;
      cout<<f.isValid()<<endl;
      cout<<f.getVectSize()<<endl;
    }

    cout<<"sample rate:"<<reader.getSampleRate()<<endl;
    cout<<"feature cnt:"<<reader.getFeatureCount()<<endl;
    }
    catch(alize::InvalidDataException e)
    {
      cout<<e.toString()<<endl;
    }
    catch(alize::ParamNotFoundInConfigException e)
    {
      cout<<e.toString()<<endl;
    }
    catch(alize::Exception e)
    {
      cout<<e.toString()<<endl;
    }

    cout<<"TEST A"<<endl;
    A pierszy;
    pierszy.s_ = "dupa";
    A drugi(pierszy);
    pierszy.s_ = "zmieniona_dupa";
    cout<<"pierwszy: "<<pierszy.s_<<endl;
    cout<<"drugi: "<<drugi.s_<<endl;


    cout<<"elo"<<endl;
    return 0;
    //return a.exec();
}
