#include <iostream>
#include <Windows.h>

#include "Utill/utill.h"
#include "Render/Renderer.h"
#include "Actor.h"
#include "Math/color.h"

namespace wanted
{

	Actor::Actor(const char* image ,
		const Vector2& position,
		Color color)
		: position(position), color(color)
	{

		size_t length = strlen(image) + 1;
		this->image = new char[length];
		strcpy_s(this->image, length, image);
	}

	Actor::~Actor()
	{
		SafeDeleteArray(image);

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
		//Renderer::Draw(position, image, color);
		Renderer::Get().Submit(
			image, position, color, sortingorder);
	}

	void Actor::SetPosition(const Vector2& newPosition)
	{
		//Renderer::Draw(position, ' '); //이전 위치 지우기.

		if (position == newPosition)
		{
			return;
		}

		position = newPosition;

	}



}