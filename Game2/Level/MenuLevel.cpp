#include "MenuLevel.h"
#include "Game/Game.h"
#include "Core/Input.h"
#include "Utill/utill.h"
#include "Render/Renderer.h"
#include <iostream>

MenuLevel::MenuLevel()
{

	items.emplace_back(new MenuItem(
		"Resume Game",
		[]()
		{
			//메뉴 토글 함수 호출.
			Game::Get().ToggleMenu();
		}
	));


	items.emplace_back(new MenuItem(
		"Quit Game",
		[]()
		{
			//메뉴 토글 함수 호출.
			Game::Get().QuitEngine();
		}
	));
}

MenuLevel::~MenuLevel()
{
	for (MenuItem*& item : items)
	{
		delete item;
		item = nullptr;
	}


	items.clear();

}



void MenuLevel::Tick(float deltatime)
{


	super::Tick(deltatime);



	//배열길이
	static int length = static_cast<int>(items.size());


	if (Input::Get().GetKeyDown(VK_UP))
	{
		currentIndex = (currentIndex - 1 + length)% length;
	}

	if (Input::Get().GetKeyDown(VK_DOWN))
	{
		currentIndex = (currentIndex + 1) % length;

	}

	if (Input::Get().GetKeyDown(VK_RETURN))
	{
		items[currentIndex]->onSelected();

	}

	if (Input::Get().GetKeyDown(VK_ESCAPE))
	{
		//items[currentIndex]->onSelected();
		Game::Get().ToggleMenu();

		currentIndex = 0;

	}

}

void MenuLevel::Draw()
{
	Utill::SetConsolePosition(Vector2::Zero);
	Utill::SetConsoleTextColor(Color::White);

	//텍스트 출력.

	Renderer::Get().Submit("Sokoban Game", Vector2::Zero);
	//std::cout << "Sokoban Game\n\n";

	for (int i = 0; i < static_cast<int>(items.size()); ++i)
	{
		Color textColor = (i == currentIndex) ? selectedColor : unSelectedColor;
		// 색상 설정.
		//Utill::SetConsoleTextColor(textColor);

		Renderer::Get().Submit(
		items[i]->text,
			Vector2(0,2+i),
			textColor
			);

		// 텍스트 출력.
		//std::cout << items[i]->text << "\n";
	}
	

}
