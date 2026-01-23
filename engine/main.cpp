#include <iostream>

#include "Engine/Engine.h"

int main()
{
	std::cout << "Starting Wanted Engine..." << std::endl;
	wanted::Engine engine;
	engine.Run();
	std::cout << "Shutting down Wanted Engine..." << std::endl;
	return 0;		
}
