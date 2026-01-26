#include "Level.h"
#include "Actor/Actor.h"

namespace wanted
{
	Level::Level()
	{
	}
	Level::~Level()
	{
		for (Actor*& actor : actors)
		{

			if (actor)
			{

				delete actor;
				actor = nullptr;

			}

		}

		actors.clear();
	}

	//게임 플레이 이벤트
	void Level::BeginPlay()
	{
		for (Actor* actor : actors)
		{
			actor->BeginPlay();
		}
	}
	void Level::Tick(float deltaTime)
	{
		for (Actor* actor : actors)
		{
			actor->Tick(deltaTime);
		}
	}
	void Level::Draw()
	{
		for (Actor* actor : actors)
		{
			actor->Draw();
		}
	}


}