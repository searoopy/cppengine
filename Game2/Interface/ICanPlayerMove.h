#pragma once
#include "Math/Vector2.h"
using namespace wanted;

class ICanPlayerMove
{
public:

	//플레이어가 이동가능한지 문의할때 사용할 함수.
	virtual bool CanMove(
		const Vector2& playerPos,
		const Vector2& nextPos)
		= 0;

};