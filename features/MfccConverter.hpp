#ifndef MFCCCONVERTER_HPP
#define MFCCCONVERTER_HPP
#include<alize.h>
#include<string>
#include"exceptions/simple_exceptions.hpp"
#include<cstdlib>
#include<unistd.h>
#include<thread>
#include<sys/wait.h>
#include"utils/utils.hpp"



/**
 * @brief The MfccConverter Klasa, która przetwarza plik w formacie MP3
 * na wektory cech w formacie SPro4
 */
class MfccConverter
{
//protected:
//  const std::string CONVERT_SCRIPT_PATH = "./convert_mp3_to_SPro4.sh";
public:
  MfccConverter() = default;
  MfccConverter(const MfccConverter &other) = default;
  MfccConverter& operator=(const MfccConverter &other) = default;
  MfccConverter(MfccConverter &&other) = default;
  MfccConverter& operator=(MfccConverter &&other) = default;

  virtual void convertToSPro4(const std::string &source_path,
                      const std::string &dest_dir,const std::string &dest_name)const = 0;

};

class MfccConverterLinux
{
protected:
  const std::string CONVERT_SCRIPT_PATH = "./scripts/convert_mp3_to_SPro4.sh";
public:
  MfccConverterLinux() = default;
  MfccConverterLinux(const MfccConverterLinux &other) = default;
  MfccConverterLinux& operator=(const MfccConverterLinux &other) = default;
  MfccConverterLinux(MfccConverterLinux &&other) = default;
  MfccConverterLinux& operator=(MfccConverterLinux &&other) = default;

  int32_t runMadPlay(const std::string &source_dir,const std::string &source_name,
                  const std::string &dest_dir,const std::string &dest_name)const;
  int32_t runSfbcep(const std::string &source_dir,const std::string &source_name,
                    const std::string &dest_dir,const std::string &dest_name)const;
  virtual void convertToSPro4(const std::string &source_path,
                              const std::string &dest_dir,const std::string &dest_name)const ;

};


#endif // MFCCCONVERTER_HPP
