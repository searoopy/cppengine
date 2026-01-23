#pragma once

namespace wanted
{
	
	class Engine
	{
		
		//ตฅภฬลอ.
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

	private:
		void ProcessInput();

		void Tick(float deltaTime);

		void Draw();

	private:
		bool isQuit = false;
		KeyState keyStates[255] = {};

	};
}