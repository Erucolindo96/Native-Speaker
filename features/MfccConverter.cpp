#include "MfccConverter.hpp"
using namespace utils;
/*
void execBashScript(const std::string command, int32_t *ret_code)
{
  *ret_code = system(command.c_str());
}
*/

int32_t MfccConverterLinux::runMadPlay(const std::string &source_dir,const std::string &source_name,
                const std::string &dest_dir,const std::string &dest_name)const
{

}

int32_t MfccConverterLinux::runSfbcep(const std::string &source_dir,const std::string &source_name,
                  const std::string &dest_dir,const std::string &dest_name)const
{
  int32_t status = 255;
  pid_t ch_pid = 0;
  ch_pid = fork();
  if(ch_pid == 0)
  {

  }
  else if(ch_pid > 0)
  {
    waitpid(ch_pid, &status,0);
  }
  else
  {
    throw std::runtime_error("Unable to fork process!");
  }
  return status;
}
void MfccConverterLinux::convertToSPro4(const std::string &source_path,
                    const std::string &dest_dir,const std::string &dest_name)const
{
  if(!fileExist(source_path))
    throw FileNotFound(__FILE__ + std::string(", line: ") + std::to_string(__LINE__)
                       + std::string(" - source file not found"));
  if(!fileExist(dest_dir))
    throw DirNotFound(__FILE__ + std::string(", line: ") + std::to_string(__LINE__)
                       + std::string(" - destination directory not found"));
  string command = string("  madplay --left --output=raw:- ") + source_path+ string(" | ") +
                    string("sfbcep -f 11025 - ") + dest_dir+std::string("/") + dest_name;

  int32_t status = system(command.c_str());
  if(status != 0)
  {
    if(utils::fileExist(dest_dir + "/" + dest_name))
    {
      system((string("rm ") + dest_dir + "/" + dest_name).c_str());
    }
    throw CannotConvertToSPro4("CannotConvertToSPro4");
  }
}

