#pragma once
#include "Common/Common.h";
namespace wanted
{
	class Level;
	class Input;

	class WANTED_API Engine
	{

	public:
		Engine();
		~Engine();
		
		void Run();

		void QuitEngine();

		void SetNewLevel(class Level* newLevel);


		static Engine& Get();

	private:

		void BeginPlay();

		void Tick(float deltaTime);

		void Draw();

	private:
		//종료 플래그.
		bool isQuit = false;


		//입력 관리자
		Input* input = nullptr;

		//메인 레벨
		class Level* mainLevel = nullptr;

		static Engine* instance;


	};
}