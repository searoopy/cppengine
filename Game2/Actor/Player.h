#pragma once

#include "Actor/Actor.h"
#include "Common/Common.h";

class Player : public wanted::Actor
{

	RTTI_DECLARATIONS(Player, Actor)

public:
	Player();

protected:
	//게임 플레이 이벤트
	virtual void BeginPlay() override;
	virtual void Tick(float deltaTime) override;
	virtual void Draw() override;
};

