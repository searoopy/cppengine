#include <iostream>
#include <Windows.h>


#include "Engine.h"
#include "Level\Level.h"
#include "Core/Input.h"



namespace wanted
{
	Engine* Engine::instance = nullptr;


	Engine::Engine()
	{
		instance = this;
		input = new Input();
	}


	Engine::~Engine()
	{
		if (mainLevel)
		{
			delete mainLevel;
			mainLevel = nullptr;
		}
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
		float targetFrameTime = 60.0f;   ///
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
				input->ProcessInput();


				BeginPlay();
				Tick(deltaTime);
				Draw();

				previousTime = currentTime;


				input->SavePreviousInputStates();

			}
		}


		// todo : 정리 작업.
		std::cout << "endgine has been shutdown\n";

	}

	void Engine::QuitEngine()
	{
		isQuit = true;
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

	Engine& Engine::Get()
	{
		if (!instance)
		{
			//silent is violent.
			std::cout << "error : engine::get(). instance is null\n";
			__debugbreak();
		}
		return *instance;
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

		//std::cout << "Ticking... Delta Time: " << deltaTime << " seconds. ::" <<
		//	"FPS" << 1.0f / deltaTime << "\n";



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