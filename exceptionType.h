#ifndef __EXCEPTIONTYPE_H__
#define __EXCEPTIONTYPE_H__

#include <string>
#include <iostream>

class exceptionError{
  std::string msg;
public:
  exceptionError(std::string msg):msg{msg}{}
  void printMsg(std::ostream& out){
    out << msg << std::endl;
  }
};

class exitGame : public exceptionError{ 
public: 
  exitGame(std::string msg):exceptionError{msg}{}
};

class commandError : public exceptionError{
public:
  commandError(std::string msg):exceptionError{msg}{}
};

class arguError : public exceptionError{
public:
  arguError(std::string msg):exceptionError{msg}{}
};

class magicError : public exceptionError{
public:
  magicError(std::string msg):exceptionError{msg}{}
};


#endif

