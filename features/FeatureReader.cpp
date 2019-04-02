#include "FeatureReader.hpp"



/*
 * Protected
 */
alize::Config FeatureReader::createConfig(const std::string & file_ext)const
{
  alize::Config ret;
  const uint32_t ANY_NUM = 12;//parametr nie ma znaczenia, chodzi o to, aby
  //jakikolwiek był. Czemu tak jest - nie wiem, chyba ALIZE ma tak zaimplementowane
  ret.setParam("featureFilesPath", dir_.c_str());
  ret.setParam("loadFeatureFileExtension", file_ext.c_str());
  ret.setParam("vectSize", std::to_string(ANY_NUM).c_str());
  return ret;
}


/*
 *Public
 */
FeatureReader::FeatureReader(const std::string &feature_dir)
  :dir_(feature_dir)
{}


std::string FeatureReader::getFeatureDir()const
{
  return dir_ ;
}


void FeatureReader::setFeatureDir(const std::string &dir)
{
  dir_ = dir;
}

std::vector<alize::Feature> FeatureReader::readFile(const SPro4File &mfcc_file)const
{
  throw std::runtime_error("TODO");
//  alize::Config conf = createConfig(extention);
//  alize::FeatureFileReaderSPro4 reader(file_name.c_str(),
//                                       conf);
//  std::vector<alize::Feature> ret;
//  alize::Feature temp;

//  try
//  {
//    const uint32_t F_CNT = reader.getFeatureCount(), STEP = 1;

//    for(uint32_t i = 0; i<F_CNT;++i)
//    {
//      reader.readFeature(temp,STEP);
//      ret.push_back(temp);
//    }
//    reader.close();
//    return ret;

//  }
//  catch(alize::FileNotFoundException &e)
//  {
//    throw FileNotFound(e.toString().c_str());
//  }
//  catch(alize::Exception  &e)
//  {
//    std::cerr<<"File "<<__FILE__<<"Line "<<__LINE__<<": unexcepted Alize Exception"<<endl;
//    throw std::runtime_error(e.toString().c_str());
//  }
}
double FeatureReader::getSampleRate(const SPro4File &mfcc_file)const
{
  throw std::runtime_error("TODO");
  //  alize::Config conf = createConfig(extention);
//  alize::FeatureFileReaderSPro4 reader(file_name.c_str(),
//                                       conf);
//  try
//  {
//    double ret = reader.getSampleRate();
//    reader.close();
//    return ret;
//  }
//  catch(alize::FileNotFoundException &e)
//  {
//    throw FileNotFound(e.toString().c_str());
//  }
//  catch(alize::Exception  &e)
//  {
//    std::cerr<<"File "<<__FILE__<<"Line "<<__LINE__<<": unexcepted Alize Exception"<<endl;
//    throw std::runtime_error(e.toString().c_str());
//  }

}

