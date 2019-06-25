#include "RecordFormatFactory.hpp"

QString RecordFormatFactory::getCodec(const QString &format)
{
  if(format == "wav")
  {
    return "audio/pcm";
  }

  throw FormatDoesNotExists("");
}

QString RecordFormatFactory::getContainer(const QString &format)
{
  if(format == "wav")
  {
    return "audio/x-wav";
  }

  throw FormatDoesNotExists("");

}

QStringList RecordFormatFactory::getValidFormats()
{
  return {"wav"};
}
