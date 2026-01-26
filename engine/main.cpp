#include <iostream>

#include "Engine/Engine.h"

#include "Level/TestLevel.h"

int main()
{
	std::cout << "Starting Wanted Engine..." << std::endl;
	wanted::Engine engine;


	engine.SetNewLevel(new TestLevel());

	engine.Run();
	std::cout << "Shutting down Wanted Engine..." << std::endl;
	return 0;		
}
