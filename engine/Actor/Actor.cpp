#include "Actor.h"


namespace wanted
{

	Actor::Actor()
	{
	}

	Actor::~Actor()
	{
		
	}


	//게임 플레이 이벤트
	void Actor::BeginPlay()
	{
		//이벤트를 받은 후에는 플래그 설정.
		hasBeganPlay = true;
	}
	void Actor::Tick(float deltaTime)
	{
	}
	void Actor::Draw()
	{
	}



}