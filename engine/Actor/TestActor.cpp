#include "TestActor.h"
#include <iostream>

void TestActor::BeginPlay()
{
	Actor::BeginPlay();

	std::cout << "testactor ::beginplay()\n";
}



void TestActor::Tick(float deltaTime)
{
	Actor::Tick(deltaTime);

	std::cout << "testactor::tick(). deltatime " << deltaTime
		<< ", FPS " << (1.0f / deltaTime) << "\n";
}
void TestActor::Draw()
{
	Actor::Draw();
}
