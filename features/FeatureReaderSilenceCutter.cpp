#include "FeatureReaderSilenceCutter.hpp"


 FeatureReaderSilenceCutter::FeatureReaderSilenceCutter(const std::string &feature_dir):
   FeatureReader(feature_dir)
{}

 std::vector<alize::Feature> FeatureReaderSilenceCutter::readFile(const std::string &file_name,
                                              const std::string &extention)const
 {
   return cutSilenceFeatures( FeatureReader::readFile(file_name, extention));

 }


 std::vector<alize::Feature> FeatureReaderSilenceCutter::cutSilenceFeatures(const std::vector<alize::Feature> &f_vec)const
 {

   const uint32_t LOG_ENERGY_INDEX = 0;
   std::vector<alize::Feature> ret;
   for(auto f_iter = f_vec.begin(); f_iter != f_vec.end(); ++f_iter)
   {
      if(f_iter->operator[](LOG_ENERGY_INDEX) >= MIN_ENERGY)
      {
        ret.push_back(*f_iter);
      }
   }
   return ret;
 }

