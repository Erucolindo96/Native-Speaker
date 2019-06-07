#include "FeatureReaderSilenceCutter.hpp"


 std::vector<alize::Feature> FeatureReaderSilenceCutter::readFile(const SPro4File &mfcc_file)const
 {
   return cutSilenceFeatures(FeatureReader::readFile(mfcc_file));
 }


 std::vector<alize::Feature> FeatureReaderSilenceCutter::cutSilenceFeatures(const std::vector<alize::Feature> &f_vec)const
 {
   const uint32_t LOG_ENERGY_INDEX = countIndexOfLogEnergy(f_vec[0].getVectSize(), true);
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

 uint32_t FeatureReaderSilenceCutter::countIndexOfLogEnergy(uint32_t f_lenght, bool with_diff_vec)const
 {
  return with_diff_vec?((f_lenght)/2)-1:(f_lenght-1);//albo srodkowy element wektora, albo ostatni
  //-1 bo to ma byc indeks tego elementu w wektorze
 }

