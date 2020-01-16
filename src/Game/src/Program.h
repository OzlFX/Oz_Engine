#ifndef _CPROGRAM_H_
#define _CPROGRAM_H_

#include <OzEngine/src/OzEngine.h>

class cProgram
{
private:

	std::shared_ptr<Oz::cCore> m_Program;

public:

	cProgram();

	void Run();

	~cProgram();

};

#endif