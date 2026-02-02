#include "Wall.h"

Wall::Wall(const Vector2& other)
	: super('#', other, Color::White )
{
	//그리기 우선순위 결정
	sortingorder = 0;
}
