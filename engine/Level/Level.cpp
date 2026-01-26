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
			//이미 beginplay 호출된 액터는 건너뛰기.
			if (actor->HasBeganPlay())
			{
				continue;
			}

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

	void Level::AddNewActor(Actor* newActor)
	{
		//todo 나중에 프레임 처리 고려해서 따로 추가 작업 해야함.
		actors.emplace_back(newActor);
	}


}