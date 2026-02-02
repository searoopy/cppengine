#pragma once
#include "Actor/Actor.h"


using namespace wanted;

class Ground :
    public Actor
{

    RTTI_DECLARATIONS(Ground, Actor)

public:
    Ground(const Vector2& pos);


};

