#include "Exception.h"

#include <GL/glew.h>
#include <iostream>

namespace Oz
{

Exception::Exception(const std::string& _message)
{
  this->m_Message = _message;
}

Exception::~Exception() throw() { }

const char* Exception::what() const throw()
{
  return m_Message.c_str();
}

}
