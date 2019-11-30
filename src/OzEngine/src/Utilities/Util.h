#ifndef _CUTIL_H_
#define _CUTIL_H_

#include <vector>
#include <string>

namespace Oz
{
	struct cUtil
	{
		static void splitStringLineEnding(const std::string& _input, std::vector<std::string>& _output);
		static void splitString(const std::string& _input, char _splitter, std::vector<std::string>& _output);
		static void splitStringWhiteSpace(const std::string& _input, std::vector<std::string>& _output);
	};
}

#endif