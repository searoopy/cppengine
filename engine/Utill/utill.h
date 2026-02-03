#pragma once

#include "Math/Vector2.h"
#include "Math/color.h"

using namespace wanted;

namespace Utill
{
	inline void SetConsolePosition(const Vector2& position)
	{
		
		SetConsoleCursorPosition(
			GetStdHandle(STD_OUTPUT_HANDLE),
			static_cast<COORD>(position)
		);
	}



	inline void SetConsoleTextColor(Color color)
	{
		SetConsoleTextAttribute(
			GetStdHandle(STD_OUTPUT_HANDLE),
			static_cast<WORD>(color)
		);
	}


	inline void TurnOffCursor()
	{
		CONSOLE_CURSOR_INFO info = {};
		GetConsoleCursorInfo(
			GetStdHandle(STD_OUTPUT_HANDLE),
			&info
		);
		info.bVisible = false;
		SetConsoleCursorInfo(
			GetStdHandle(STD_OUTPUT_HANDLE),
			&info
		);
	}

	inline void TurnOnCursor()
	{
		CONSOLE_CURSOR_INFO info = {};
		GetConsoleCursorInfo(
			GetStdHandle(STD_OUTPUT_HANDLE),
			&info
		);
		info.bVisible = true;
		SetConsoleCursorInfo(
			GetStdHandle(STD_OUTPUT_HANDLE),
			&info
		);
	}

}


template<typename T>
void SafeDeleteArray(T*& ptr)
{
	if (ptr)
	{
		delete[] ptr;
		ptr = nullptr;
	}
}

template<typename T>
void SafeDelete(T*& ptr)
{
	if(ptr)
	{
		delete ptr;
		ptr = nullptr;
	}
}