#include "Program.h"

int main()
{
	std::shared_ptr<cProgram> Game = std::make_shared<cProgram>();
	Game->Run();

	return 0;
}