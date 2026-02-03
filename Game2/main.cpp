#include <iostream>


#include "Engine/Engine.h"
#include "Level/Level.h"
#include "Level/SokobanLevel.h"
#include "Actor/Actor.h"
#include "Actor/Player.h"
#include "Game/Game.h"


using namespace wanted;



int main()
{
	//wanted::Engine engine;
	//engine.SetNewLevel(new SokobanLevel());
	//engine.Run();

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



	Game game;
	game.Run();





	/*
	const int width = 3;
	const int height = 3;


	CHAR_INFO chararr[width * height] = {};
	chararr[2 * width + 1].Char.AsciiChar = 'P';
	chararr[2 * width + 1].Attributes = FOREGROUND_GREEN;


	COORD pos ={};
	
	COORD size;
	size.X = 3;
	size.Y = 3;	


	SMALL_RECT writeRegion = {
		0,
		0,
		static_cast<short>(width),
		static_cast<short>(height),
	};

	WriteConsoleOutputA(
		GetStdHandle(STD_OUTPUT_HANDLE),
		chararr,
		size,
		pos,
		&writeRegion
	);	

	std::cin.get();

	*/


}
