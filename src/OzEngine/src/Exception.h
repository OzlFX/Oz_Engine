#ifndef _EXCEPTION_H_
#define _EXCEPTION_H_

#include <exception>
#include <string>

namespace Oz
{
	/* Custom engine exception for specific engine usages */
	struct Exception : public std::exception
	{
		Exception(const std::string& _message);
		virtual ~Exception() throw();
		virtual const char* what() const throw();

	private:
		std::string m_Message;

	};
}

#endif