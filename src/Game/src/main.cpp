#include <OzEngine/src/Core.h>

int main()
{
	std::unique_ptr<Oz::cCore> Program = std::make_unique<Oz::cCore>();
	
	Program->Run();
	
	return 0;
}