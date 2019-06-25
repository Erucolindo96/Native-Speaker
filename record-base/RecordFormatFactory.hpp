#ifndef RECORDFORMATFACTORY_HPP
#define RECORDFORMATFACTORY_HPP

#include<QAudioRecorder>
#include"exceptions/simple_exceptions.hpp"
class RecordFormatFactory
{
public:
  RecordFormatFactory() = delete;
  static QString getCodec(const QString &format);
  static QString getContainer(const QString &format);
  static QStringList getValidFormats();

};

#endif // RECORDFORMATFACTORY_HPP
