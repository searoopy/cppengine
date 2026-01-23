#include <iostream>
#include <Windows.h>
#include "Engine.h"

using namespace wanted;


Engine::Engine()
{
}


Engine::~Engine()
{
}

void Engine::Run()
{

	//시계 정밀도.
	LARGE_INTEGER freq;
	QueryPerformanceFrequency(&freq);

	int64_t currentTime = 0;
	int64_t previousTime = 0;

	//하드웨어 타이머로 시간구함.
	LARGE_INTEGER time;

	QueryPerformanceCounter(&time);


	currentTime = time.QuadPart;
	previousTime = currentTime;


	//단위 :초
	float targetFrameTime = 1.0f;
	float oneFrameTime = 1.0f / targetFrameTime;


	while (!isQuit)
	{

		QueryPerformanceCounter(&time);
		currentTime = time.QuadPart;



		float deltaTime = static_cast<float>(currentTime - previousTime);

		deltaTime = deltaTime / static_cast<float>(freq.QuadPart);


		//고정프레임
		if (deltaTime >= oneFrameTime)
		{
			ProcessInput();
			Tick(deltaTime);
			Draw();

			previousTime = currentTime;


			// 키 마다의 입력 읽기.
		// !!! 운영체제가 제공하는 기능을 사용할 수 밖에 없음.
			for (int ix = 0; ix < 255; ++ix)
			{
				keyStates[ix].isKeyDown
					= GetAsyncKeyState(ix) & 0x8000 > 0 ? true : false;
			}

		}
	}


	// todo : 정리 작업.
	std::cout << "endgine has been shutdown\n";

}

void Engine::QuitEngine()
{
	isQuit = true;
}

bool Engine::GetKeyDown(int keyCode)
{
	//return false;
	return keyStates[keyCode].isKeyDown
		&& !keyStates[keyCode].wasKeyDown;
}

bool Engine::GetKeyUp(int keyCode)
{
	return !keyStates[keyCode].isKeyDown
		&& keyStates[keyCode].wasKeyDown;
}

bool Engine::GetKeyKey(int keyCode)
{
	return keyStates[keyCode].isKeyDown;
}

void Engine::ProcessInput()
{

	// 키 마다의 입력 읽기.
		// !!! 운영체제가 제공하는 기능을 사용할 수 밖에 없음.
	for (int ix = 0; ix < 255; ++ix)
	{
		keyStates[ix].isKeyDown
			= GetAsyncKeyState(ix) & 0x8000 > 0 ? true : false;
	}

}

void Engine::Tick(float deltaTime)
{

	std::cout << "Ticking... Delta Time: " << deltaTime << " seconds. ::"<<
		"FPS" << 1.0f / deltaTime << "\n";


	if( GetKeyDown(VK_ESCAPE) )
	{
		std::cout << "Escape key pressed. Quitting engine.\n";
		QuitEngine();
	}
}

void Engine::Draw()
{
}
