#pragma once
#include "Actor/Actor.h"

using namespace wanted;

class Wall :
    public Actor
{
    RTTI_DECLARATIONS(Wall, Actor)


public:
    //위치 지정 이 가능하도록 생성자

    Wall( const Vector2& other);



};

