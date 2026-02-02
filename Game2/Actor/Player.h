#pragma once

#include "Actor/Actor.h"


using namespace wanted;

class Player : public Actor
{

	RTTI_DECLARATIONS(Player, Actor)

public:
	Player();
	Player(const Vector2& pos);

protected:
	//게임 플레이 이벤트
	virtual void BeginPlay() override;
	virtual void Tick(float deltaTime) override;
	virtual void Draw() override;
};

