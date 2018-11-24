#ifndef SIMPLE_EXCEPTIONS_HPP
#define SIMPLE_EXCEPTIONS_HPP
#include<alize.h>
#include<stdexcept>
class IndexOutOfBounds : std::out_of_range
{
public:
  explicit IndexOutOfBounds(std::string &&msg) : out_of_range(msg)
  {}
};

class InvalidFeatureSize: std::invalid_argument
{
public :
  explicit InvalidFeatureSize(std::string &&msg):invalid_argument(msg)
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

class ModelNameNotDefined: public std::logic_error
{
public:
  ModelNameNotDefined(const std::string &msg): std::logic_error(msg)
  {}
};
#endif // SIMPLE_EXCEPTIONS_HPP

