#pragma once

namespace wanted
{
	class Level;

	class Engine
	{
		
		//데이터.
		struct KeyState
		{
			bool isKeyDown = false;
			bool wasKeyDown = false;
		};



	public:
		Engine();
		~Engine();
		
		void Run();

		void QuitEngine();

		bool GetKeyDown(int keyCode);
		bool GetKeyUp(int keyCode);
		bool GetKeyKey(int keyCode);


		void SetNewLevel(class Level* newLevel);

	private:
		void ProcessInput();

		void BeginPlay();

		void Tick(float deltaTime);

		void Draw();

	private:
		//종료 플래그.
		bool isQuit = false;

		//키 상태 저장용 배열.
		KeyState keyStates[255] = {};

		//메인 레벨
		class Level* mainLevel = nullptr;

	};
}