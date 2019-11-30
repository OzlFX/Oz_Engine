#include "Util.h"

namespace Oz
{
	void cUtil::splitStringLineEnding(const std::string& _input, std::vector<std::string>& _output)
	{
		std::string curr;

		_output.clear();

		for (size_t i = 0; i < _input.length(); i++)
		{
			if (_input.at(i) == '\n')
			{
				_output.push_back(curr);
				curr = "";
			}
			else if (_input.at(i) == '\r')
			{
				// Ignore
			}
			else
			{
				curr += _input.at(i);
			}
		}

		if (curr.length() > 0)
		{
			_output.push_back(curr);
		}
	}

	void cUtil::splitString(const std::string& _input, char _splitter, std::vector<std::string>& _output)
	{
		std::string curr;

		_output.clear();

		for (size_t i = 0; i < _input.length(); i++)
		{
			if (_input.at(i) == _splitter)
			{
				_output.push_back(curr);
				curr = "";
			}
			else
			{
				curr += _input.at(i);
			}
		}

		if (curr.length() > 0)
		{
			_output.push_back(curr);
		}
	}

	void cUtil::splitStringWhiteSpace(const std::string& _input, std::vector<std::string>& _output)
	{
		std::string _curr;

		_output.clear();

		for (size_t i = 0; i < _input.length(); i++)
		{
			if (_input.at(i) == ' ' || _input.at(i) == '\r' || _input.at(i) == '\n' || _input.at(i) == '\t')
			{
				if (_curr.length() > 0)
				{
					_output.push_back(_curr);
					_curr = "";
				}
			}
			else
			{
				_curr += _input.at(i);
			}
		}

		if (_curr.length() > 0)
		{
			_output.push_back(_curr);
		}
	}
}