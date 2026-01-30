#pragma once

#include <iostream>
#include "Utill/utill.h"


namespace wanted
{
	class Renderer
	{
	public:
		static void Draw(const char image)
		{
			std::cout << image;
		}


		static void Draw(const Vector2& position, const char image)
		{
			Utill::SetConsolePosition(position);
			Draw(image);
		}


		//위치 색상 설정 및 그리기
		static void Draw(const Vector2& position, const char image, Color color)
		{
			Utill::SetConsoleTextColor(color);
			Utill::SetConsolePosition(position);
			Draw(position, image);


			Utill::SetConsoleTextColor(Color::White);
		}
	};
}