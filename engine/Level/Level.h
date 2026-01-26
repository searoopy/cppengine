#pragma once


#include <vector>

namespace wanted
{

	class Actor;

	class Level
	{
	public:
		Level();
		virtual ~Level();

		//게임 플레이 이벤트
		virtual void BeginPlay();
		virtual void Tick(float deltaTime);
		virtual void Draw();

		void AddNewActor(Actor* newActor);

	protected:
		//액터 배열.
		std::vector<Actor*> actors;

	};

}

