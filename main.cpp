#include "mainwindow.hpp"
#include <QApplication>
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
    alize::Config cfn;
//    cfn.load("config");
//    std::cout << cfn.existsParam("vectSize")<<std::endl;
//    std::cout << cfn.getParam("vectSize")<<std::endl;

    cfn.setParam("vectSize", "10");
    std::cout << cfn.existsParam("vectSize")<<std::endl;
    std::cout << cfn.getParam("vectSize")<<std::endl;

    cfn.setParam("Dupa", "true");
    std::cout << cfn.existsParam("Dupa")<<std::endl;
    std::cout << cfn.getParam("Dupa")<<std::endl;

    cfn.setParam("vectSize", "10");
    cfn.setParam("mixtureDistribCount", "512");
    cfn.setParam("maxLLK", "100");
    cfn.setParam("minLLK", "-100");
    cfn.setParam("featureServerMemAlloc", "1000000");

    MixtureServer s(cfn);
    s.createMixture(512, DistribType_GD);
    cout<< s.getMixture(0).getDistribCount()<<endl;
    s.getMixture(0).weight(511) = 1.0;
    cout<<s.getMixture(0).weight(511)<<endl ;
    s.getMixture(0).weight(511) = -1;
    cout<<s.getMixture(0).weight(511)<<endl ;
    return 0;
    //return a.exec();
}
