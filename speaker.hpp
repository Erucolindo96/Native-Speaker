#ifndef MOWCA_HPP
#define MOWCA_HPP

#include<string>
#include<exception>
#include<stdexcept>

class InvalidSexCharacter: public std::domain_error
{
  explicit InvalidSexCharacter(std::string msg): std::domain_error(msg)
  {}
};


class Sex
{
  static const char sMEN='M', sFEMALE='F';
  char val_;

private:
  void checkCharacter()
  {
    if (val_ != sMEN || val_ != sWOMEN)
      throw InvalidSexCharacter("Speaker.hpp, Line 22 - Invalid sex character");
  }

public:
  Sex(const char val):val_(val)
  {
    checkCharacter();
  }
  void setSex(const char val)
  {
    val_ = val;
    checkCharacter();
  }
  inline char getSex()const noexcept
  {
    return val_;
  }


};

class Speaker
{

protected:
  std::string name_, surname_;
  Sex sex_;
  uint8_t age_;


public:
  Speaker(std::string name,std::string surname,Sex s, uint8_t age):
    name_(name), surname_(surname),sex_(s), age_(age)
  {}

  std::string getName()const noexcept
  {
    return name_;
  }
  std::string getSurname()const noexcept
  {
    return surname_;
  }
  Sex getSex()const noexcept
  {
    return sex_;
  }
  uint8_t getAge()const noexcept
  {
    return age_;
  }

  void setName(std::string name)noexcept
  {
    name_ = name;
  }
  void setSurname(std::string surname)noexcept
  {
    surname_ = surname;
  }
  void setSex(Sex s)noexcept
  {
    sex_ = s;
  }
  void setAge(uint8_t age)noexcept
  {
    age_ = age;
  }

};



#endif // MOWCA_HPP

