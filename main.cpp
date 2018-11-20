//#include "mainwindow.hpp"
//#include <QApplication>
#include<alize/alize.h>
using namespace std;
using namespace alize;
int main(int argc, char *argv[])
{
  const uint32_t VECT_SIZE = 10;
  const string VECT_SIZE_STR = "10";
    //QApplication a(argc, argv);
    //MainWindow w;
    //w.show();
    alize::Config cfn, cfn_s;
    cfn.setParam("mixtureFilesPath", "../");
    cfn.setParam("saveMixtureFileFormat", "XML");
    cfn.setParam("saveMixtureFileExtension", ".mixture");

    cfn.setParam("loadMixtureFileFormat", "XML");
    cfn.setParam("loadMixtureFileExtension", ".mixture");

    cfn.setParam("saveMixtureServerFileFormat", "XML");
    cfn.setParam("saveMixtureServerFileExtension", ".mixture_server");
    cfn.setParam("loadMixtureFileBigEndian", "true");

    cfn.setParam("vectSize", "12");
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
    }
    cout<<"sample rate:"<<reader.getSampleRate()<<endl;
    cout<<"feature cnt:"<<reader.getFeatureCount()<<endl;
    }
    catch(alize::InvalidDataException e)
    {
      cout<<e.toString()<<endl;
    }

    cout<<"elo"<<endl;
    return 0;
    //return a.exec();
}
