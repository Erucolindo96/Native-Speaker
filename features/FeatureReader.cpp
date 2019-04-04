#include "FeatureReader.hpp"



/*
 * Protected
 */
alize::Config FeatureReader::createConfig(const SPro4File &mfcc_file)const
{
  alize::Config ret;
  const uint32_t ANY_NUM = 1;//parametr nie ma znaczenia, chodzi o to, aby
  //jakikolwiek był. Czemu tak jest - nie wiem, chyba ALIZE ma tak zaimplementowane
  QString dir_path = mfcc_file.getRecordInfo().
                     absoluteDir().absolutePath()+ "/";
  ret.setParam("featureFilesPath", dir_path.toStdString().c_str());
  ret.setParam("loadFeatureFileExtension", "");
  ret.setParam("vectSize", std::to_string(ANY_NUM).c_str());
  return ret;
}


/*
 *Public
 */


std::vector<alize::Feature> FeatureReader::readFile(const SPro4File &mfcc_file)const
{
  alize::Config conf = createConfig(mfcc_file);
  alize::FeatureFileReaderSPro4 reader(mfcc_file.getRecordInfo().fileName().toStdString().c_str(),
                                       conf);
  std::vector<alize::Feature> ret;
  alize::Feature temp;

  try
  {
    const uint32_t F_CNT = reader.getFeatureCount(), STEP = 1;

    for(uint32_t i = 0; i<F_CNT;++i)
    {
      reader.readFeature(temp,STEP);
      ret.push_back(temp);
    }
    reader.close();
    return ret;

  }
  catch(alize::FileNotFoundException &e)
  {
    throw FileNotFound(e.toString().c_str());
  }
  catch(alize::Exception  &e)
  {
    std::cerr<<"File "<<__FILE__<<"Line "<<__LINE__<<": unexcepted Alize Exception"<<endl;
    throw std::runtime_error(e.toString().c_str());
  }
}
double FeatureReader::getSampleRate(const SPro4File &mfcc_file)const
{
  alize::Config conf = createConfig(mfcc_file);
  alize::FeatureFileReaderSPro4 reader(mfcc_file.getRecordInfo().fileName().toStdString().c_str(),
                                       conf);
  try
  {
    double ret = reader.getSampleRate();
    reader.close();
    return ret;
  }
  catch(alize::FileNotFoundException &e)
  {
    throw FileNotFound(e.toString().c_str());
  }
  catch(alize::Exception  &e)
  {
    std::cerr<<"File "<<__FILE__<<"Line "<<__LINE__<<": unexcepted Alize Exception"<<endl;
    throw std::runtime_error(e.toString().c_str());
  }

}

