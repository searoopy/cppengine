#pragma once
#include "Actor/Actor.h"
#include "Common/Common.h";	
#include "Math/Vector2.h"	


using namespace wanted;

class Box : public wanted::Actor
{
	//RTTI µî·Ï
	RTTI_DECLARATIONS(Box, Actor)

public:
	Box(const Vector2& newPos);
};

