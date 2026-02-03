#include "Box.h"

Box::Box(const Vector2& newPos)
	:super("B", newPos, Color::Red)	
{
	sortingorder = 5;
}
