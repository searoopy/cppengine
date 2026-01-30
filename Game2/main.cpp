#include <iostream>


#include "Engine/Engine.h"
#include "Level/Level.h"
#include "Level/TestLevel.h"
#include "Actor/Actor.h"
#include "Actor/Player.h"


using namespace wanted;

int main()
{
	wanted::Engine engine;
	engine.SetNewLevel(new TestLevel());
	engine.Run();

	//TestLevel* level = new TestLevel();
	//Actor* actor = new Actor();
	//Actor* actor2 = new Player();


	//Player* Player = actor2->As<Player>();
	//if (Player) 
	


	//Player* Player = dynamic_cast<Player*>(actor);

	//if( actor->Is(actor2) )
	//{
	//	std::cout << "actor is Player type.\n";
	//}
	//else
	//{
	//	std::cout << "actor is not Player type.\n";
	//}

}
