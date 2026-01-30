#include <iostream>
#include <Windows.h>

#include "Utill/utill.h"
#include "Core/Renderer.h"
#include "Actor.h"
#include "Math/color.h"

namespace wanted
{

	Actor::Actor(const char image ,
		const Vector2& position,
		Color color)
		:image(image), position(position), color(color)
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
		Renderer::Draw(position, image, color);

	}

	void Actor::SetPosition(const Vector2& newPosition)
	{
		Renderer::Draw(position, ' '); //이전 위치 지우기.

		position = newPosition;

	}



}