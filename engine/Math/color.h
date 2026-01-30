#pragma once


#include "common/Common.h"
#include <Windows.h>



namespace wanted
{
	enum class WANTED_API Color : unsigned char
	{
		Black = 0,
		Red = FOREGROUND_RED,
		Green = FOREGROUND_GREEN,
		Blue = FOREGROUND_BLUE,

		White = FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE
	};	


}