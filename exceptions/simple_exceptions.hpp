#ifndef SIMPLE_EXCEPTIONS_HPP
#define SIMPLE_EXCEPTIONS_HPP
#include<alize.h>
#include<stdexcept>
class IndexOutOfBounds : std::out_of_range
{
public:
  explicit IndexOutOfBounds(const std::string &msg) : out_of_range(msg)
  {}
};

class InvalidFeatureSize: std::invalid_argument
{
public :
  explicit InvalidFeatureSize(const std::string &msg):invalid_argument(msg)
  {}
};
class InvalidModelType: std::invalid_argument
{
public:
  explicit InvalidModelType(const std::string &msg): invalid_argument(msg)
  {}
};

class InvalidDistribCount: std::invalid_argument
{
public:
  explicit InvalidDistribCount(const std::string &msg): invalid_argument(msg)
  {}

};

class LearningModelWithoutFeatures: public invalid_argument
{
public:
  explicit LearningModelWithoutFeatures(const std::string &msg): invalid_argument(msg)
  {}
};

class VerifyModelWithoutFeatures: public invalid_argument
{
public:
  explicit VerifyModelWithoutFeatures(const std::string &msg): invalid_argument(msg)
  {}
};




class NotSquareMatrix: public std::invalid_argument
{
public:
  NotSquareMatrix(std::string &&msg) : std::invalid_argument(msg)
  {}
};

class FileNotFound: public std::logic_error
{
public:
  FileNotFound(const std::string &msg): std::logic_error(msg)
  {}
};

class DirNotFound: public std::logic_error
{
public:
  DirNotFound(const std::string &msg): std::logic_error(msg)
  {}
};

class CannotConvertToSPro4: public std::logic_error
{
public:
  CannotConvertToSPro4(const std::string &msg): std::logic_error(msg)
  {}
};

class NotAModelFile: public std::logic_error
{
public:
  NotAModelFile(const std::string &msg): std::logic_error(msg)
  {}
};

class ModelNameNotDefined: public std::logic_error
{
public:
  ModelNameNotDefined(const std::string &msg): std::logic_error(msg)
  {}
};

class ParamNotValid: public std::logic_error
{
public:
  explicit ParamNotValid(const std::string &msg): std::logic_error(msg)
  {}

};



class UnableToCreateFolder: public std::logic_error
{
public:
  explicit UnableToCreateFolder(const std::string &msg): std::logic_error(msg)
  {}
};

class UnableToRemoveFolder: public std::logic_error
{
public:
  explicit UnableToRemoveFolder(const std::string &msg): std::logic_error(msg)
  {}
};

class UnableToCleanFolder: public std::logic_error
{
public:
  explicit UnableToCleanFolder(const std::string &msg): std::logic_error(msg)
  {}
};

class FeatureFolderNotFound: public DirNotFound
{
public:
  explicit FeatureFolderNotFound(const std::string &msg): DirNotFound(msg)
  {}
};
class NotASProFile: public FileNotFound
{
public:
  explicit NotASProFile(const std::string &msg) : FileNotFound(msg)
  {}
};
class UnableToConvertToMfcc: public std::logic_error
{
public:
  explicit UnableToConvertToMfcc(const std::string &msg) : std::logic_error(msg)
  {}
};

class RerunningThread : public std::logic_error
{
public:
  explicit RerunningThread(const std::string &msg) : std::logic_error(msg)
  {}

};

class RerunningLearningThread: public RerunningThread
{
public:
  explicit RerunningLearningThread(const std::string &msg) : RerunningThread(msg)
  {}
};

class FormatDoesNotExists: public std::invalid_argument
{
public :
  explicit FormatDoesNotExists(const std::string &msg) :
    std::invalid_argument(msg)
  {}
};

#endif // SIMPLE_EXCEPTIONS_HPP

