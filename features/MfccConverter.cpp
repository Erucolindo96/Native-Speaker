#include "MfccConverter.hpp"
using namespace utils;

MfccConverter::MfccConverter():sample_rate_(DEF_SAMPLE_RATE_),
  frame_lenght_(DEF_FRAME_LENGHT_),interval_(DEF_INTERVAL_),
  f_lenght_(DEF_FEATURE_LENGHT_),pre_emphasis_(DEF_PRE_EMPHASIS_),
  with_log_energy_(DEF_WITH_LOG_ENERGY_),
  with_diff_vec_(DEF_WITH_DIFF_VEC_)
{}
void MfccConverter::setSampleRate(int32_t sample_rate)
{
  const int32_t MIN = 1;
  if(sample_rate < MIN)
  {
    throw std::invalid_argument(__FILE__ + std::string(", line: ") + std::to_string(__LINE__)
                                + std::string("sample rate is not a positive  integer"));
  }
  sample_rate_ = sample_rate;
}
uint32_t MfccConverter::getSampleRate()const
{
  return sample_rate_;
}

void MfccConverter::setPreEmphasis(double pre_emphasis )
{
  const double MAX = 0.95, MIN = 0.01;
  if(pre_emphasis > MAX || pre_emphasis < MIN)
  {
    throw std::invalid_argument(__FILE__ + std::string(", line: ") + std::to_string(__LINE__)
                                + std::string("pre-emphasis is not a positive  number less than 0.95"));
  }
  pre_emphasis_ = pre_emphasis;
}

double MfccConverter::getPreEmphasis()const
{
  return pre_emphasis_;
}

void MfccConverter::setFrameLenght(int32_t frame_lenght)
{
  const int32_t MIN = 1;
  if(frame_lenght < MIN)
  {
    throw std::invalid_argument(__FILE__ + std::string(", line: ") + std::to_string(__LINE__)
                                + std::string("frame lenght is not a positive integer"));
  }
  frame_lenght_ = frame_lenght;
}

uint32_t MfccConverter::getFrameLenght()const
{
  return frame_lenght_;
}

void MfccConverter::setInterval(int32_t interval)
{
  const int32_t MIN = 1;
  if(interval < MIN)
  {
    throw std::invalid_argument(__FILE__ + std::string(", line: ") + std::to_string(__LINE__)
                                + std::string("interval is not a positive integer"));
  }
  interval_ = interval;
}

uint32_t MfccConverter::getInterval()const
{
  return interval_;
}

void MfccConverter::setFeatureLenght(int32_t f_lenght)
{
  const int32_t MIN = 1, MAX = 24;
  if(f_lenght < MIN || f_lenght > MAX)
  {
    throw std::invalid_argument(__FILE__ + std::string(", line: ") + std::to_string(__LINE__)
                                + std::string("feature lenght is not a positive integer less or equal 24"));
  }
  f_lenght_ = f_lenght;
}

void MfccConverter::setLogEnergy(bool yes)
{
  with_log_energy_ = yes;
}

void MfccConverter::setFirstOrderDerivative(bool yes)
{
  with_diff_vec_ = yes;
}


uint32_t MfccConverter::getFeatureLenght()const
{
  uint32_t ret = with_diff_vec_?2*f_lenght_:f_lenght_;
  ret += with_log_energy_?1:0;//dodaje log energii
  ret += (with_log_energy_ && with_diff_vec_)?1:0;//dodaje roznicowy log energii
  return ret;
}



MfccConverterWav::MfccConverterWav():MfccConverter()
{
  const uint32_t SAMPLE_RATE_WAV = 44100, F_LENGHT = 18;
  setSampleRate(SAMPLE_RATE_WAV);
  setFeatureLenght(F_LENGHT);
  setLogEnergy(true);
  setFirstOrderDerivative(true);
}

SPro4File MfccConverterWav::convertToSPro4(const Record &source_record)const
{
  if(source_record.getRecordInfo().completeSuffix() != "wav")
  {
    throw UnableToConvertToMfcc(__FILE__ + std::string(", line: ") + std::to_string(__LINE__)
                                + std::string(" source record is not a wav file"));
  }

  const QString COMMAND_SFBCEP = "sfbcep",COMMAND_SOX = "sox",
      SOURCE_FILE = source_record.getRecordInfo().absoluteFilePath(),
      DEST_FILE = source_record.getRecordInfo().absolutePath() + "/" +
                  source_record.getRecordInfo().baseName() + SPro4File::VALID_EXT;

  auto args_sox = setArgumentsToSox(SOURCE_FILE, "-"),
      args_sfbcep = setArgumentsToSfbcep("-", DEST_FILE);


  QProcess *proc_sox = new QProcess, *proc_sfbcep = new QProcess;
  proc_sox->setStandardOutputProcess(proc_sfbcep);
  proc_sox->setProcessChannelMode(QProcess::ForwardedErrorChannel);
  proc_sfbcep->setProcessChannelMode(QProcess::ForwardedErrorChannel);

  proc_sox->start(COMMAND_SOX, args_sox);
  proc_sfbcep->start(COMMAND_SFBCEP, args_sfbcep);

  proc_sox->waitForStarted();
  proc_sfbcep->waitForStarted();

  proc_sox->waitForFinished();
  proc_sfbcep->waitForFinished();

  if(proc_sox->exitCode() != QProcess::NormalExit
     || proc_sfbcep->exitCode() != QProcess::NormalExit)
  {
    throw UnableToConvertToMfcc(__FILE__ + std::string(", line: ") + std::to_string(__LINE__)
                                + std::string(" sfbcep process crashed"));
  }
  SPro4File dest_file;
  dest_file.setPath(DEST_FILE);
  return dest_file;
}

QStringList MfccConverterWav::setArgumentsToSfbcep(const QString &source_file, const QString &dest_file)const
{
  QStringList args;
  args.append(QString("--sample-rate=") + to_string(sample_rate_).c_str());
  args.append(QString("--length=") + to_string(frame_lenght_).c_str());
  args.append(QString("--shift=") + to_string(interval_).c_str());
  args.append(QString("-p ") + to_string(f_lenght_).c_str());
  args.append(QString("--pre-emphasis=") + QString().setNum(pre_emphasis_));
  args.append(QString("--cms"));
  args.append(QString("--normalize"));
  if(with_log_energy_)
  {
    args.append("--energy");
    //args.append(QString("--scale-energy=")+QString().setNum(log_energy_scale_factor_));
  }
  if(with_diff_vec_)
  {
    args.append("--delta");
  }
  args.append(source_file);
  args.append(dest_file);
  return args;
}

QStringList MfccConverterWav::setArgumentsToSox(const QString &source_file, const QString &dest_file)const
{
  QStringList args;
  args.append("-V1");
  args.append("-D"); //wyłącza dithering - zmienia on losowo nagranie
  args.append(source_file);
  //Spro przymuje 16 bitowy, signed-integer PCM
  args.append("-b");
  args.append("16");
  args.append("-t");
  args.append("raw");
  args.append("-e");
  args.append("signed-integer");

  args.append("-r");//wyjsciowa cz.probkowania
  args.append(to_string(sample_rate_).c_str());
  args.append(dest_file);
  return args;
}
//sox 001m/kasprzak11_1-01.wav -b 16 -t raw -e signed-integer -r 48000 -


