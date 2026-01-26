#include <iostream>
#include <Windows.h>


#include "Engine.h"
#include "Level\Level.h"



namespace wanted
{

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


				BeginPlay();
				Tick(deltaTime);
				Draw();

				previousTime = currentTime;


				// 키 마다의 입력 읽기.
			// !!! 운영체제가 제공하는 기능을 사용할 수 밖에 없음.
				for (int ix = 0; ix < 255; ++ix)
				{
					keyStates[ix].isKeyDown
						= (GetAsyncKeyState(ix) & 0x8000) > 0 ? true : false;
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

	void Engine::SetNewLevel(Level* newLevel)
	{
		//기존 레벨 있는지 확인
		//있으면 기존레벨 제거
		//todo: 임시코드 레벨 전환할때는 바로 제거하면 안됨.
		if (mainLevel)
		{
			delete mainLevel;
			mainLevel = nullptr;
		}


		//레벨 설정.
		mainLevel = newLevel;
	}

	void Engine::ProcessInput()
	{

		// 키 마다의 입력 읽기.
			// !!! 운영체제가 제공하는 기능을 사용할 수 밖에 없음.
		for (int ix = 0; ix < 255; ++ix)
		{
			keyStates[ix].isKeyDown
				= (GetAsyncKeyState(ix) & 0x8000) > 0 ? true : false;
		}

	}

	void Engine::BeginPlay()
	{
		if (!mainLevel)
		{
			std::cout << "mainLevel is empty.\n";
			//로그를 남겨야함.
			return;
		}

		mainLevel->BeginPlay();
	}

	void Engine::Tick(float deltaTime)
	{

		/*std::cout << "Ticking... Delta Time: " << deltaTime << " seconds. ::" <<
			"FPS" << 1.0f / deltaTime << "\n";


		if (GetKeyDown(VK_ESCAPE))
		{
			std::cout << "Escape key pressed. Quitting engine.\n";
			QuitEngine();
		}*/


		//레벨에 이벤트 흘리기.
		if (!mainLevel)
		{
			std::cout << "rrror:engine::tick()\n";
			return;
		}
		mainLevel->Tick(deltaTime);
	}

	void Engine::Draw()
	{
		//레벨에 이벤트 흘리기.
		if (!mainLevel)
		{
			std::cout << "rrror:engine::Draw()\n";
			return;
		}
		mainLevel->Draw();
	}


}