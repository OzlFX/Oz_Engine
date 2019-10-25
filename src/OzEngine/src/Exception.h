#include <exception>
#include <string>

namespace Oz
{

struct Exception : public std::exception
{
  Exception(const std::string& _message);
  virtual ~Exception() throw();
  virtual const char* what() const throw();

private:
  std::string m_Message;

};

}
