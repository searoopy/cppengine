#include "Player.h"
#include <iostream>
#include "Engine/Engine.h"
//#include "..\includes\engine\Cor"
#include "Core/Input.h"
#include <Windows.h>
#include "Utill/utill.h"
#include "Actor/Box.h"
#include "Level/Level.h"

#include "Interface/ICanPlayerMove.h"

using namespace wanted;

Player::Player()
	: super('P', Vector2(5,3), Color::Yellow)
{
	sortingorder = 10;
}

Player::Player(const Vector2& pos)
	: super('P', pos, Color::Yellow)
{
	sortingorder = 10;
}

void Player::BeginPlay()
{
	Actor::BeginPlay();

	//std::cout << "Player ::beginplay()\n";
}



void Player::Tick(float deltaTime)
{
	super::Tick(deltaTime);



	static ICanPlayerMove* canPlayerMoveInterface = nullptr;
	if (!canPlayerMoveInterface && GetOwner())
	{
		canPlayerMoveInterface = dynamic_cast<ICanPlayerMove*>(GetOwner());
	}

	//if (wanted::Input::Get()->GetKeyDown(VK_ESCAPE))
	if(wanted::Input::Get().GetKeyDown(VK_ESCAPE))
	{
		//게임 엔진 종료 요청
		std::cout << "Escape key pressed. Quitting engine.\n";
		//QuitEngine();

		wanted::Engine::Get().QuitEngine();
	}

	if (Input::Get().GetKeyDown(VK_RIGHT)  )
	{

		Vector2 newPos(GetPosition().x + 1, GetPosition().y);

		if (canPlayerMoveInterface->CanMove(GetPosition(), newPos))
		{
			SetPosition(newPos);
		}

	/*	Vector2 newPos = GetPosition();
		newPos.x += 1;
		SetPosition(newPos);*/
	}

	if (Input::Get().GetKeyDown(VK_LEFT) )
	{
		Vector2 newPos(GetPosition().x - 1, GetPosition().y);

		if (canPlayerMoveInterface->CanMove(GetPosition(), newPos))
		{
			SetPosition(newPos);
		}
	}

	if (Input::Get().GetKeyDown(VK_UP) )
	{
		Vector2 newPos(GetPosition().x , GetPosition().y -1 );

		if (canPlayerMoveInterface->CanMove(GetPosition(), newPos))
		{
			SetPosition(newPos);
		}
	}

	if (Input::Get().GetKeyDown(VK_DOWN) )
	{
		Vector2 newPos(GetPosition().x , GetPosition().y+1);

		if (canPlayerMoveInterface->CanMove(GetPosition(), newPos))
		{
			SetPosition(newPos);
		}
	}


	if (Input::Get().GetKeyDown(VK_SPACE) )
	{
		if (owner)
		{
			owner->AddNewActor(new Box(GetPosition()));
		}
	}

	//std::cout << "Player::tick(). deltatime " << deltaTime
	//	<< ", FPS " << (1.0f / deltaTime) << "\n";
}
void Player::Draw()
{
	Actor::Draw();
}
