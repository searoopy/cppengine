#pragma once


namespace wanted
{ 
	class Actor
	{
	public:
		Actor();
		virtual ~Actor();

		//게임 플레이 이벤트
		virtual void BeginPlay();
		virtual void Tick(float deltaTime);
		virtual void Draw();

		//Getter.
		inline bool HasBeganPlay() const { return hasBeganPlay; }
		bool IsActive() const
		{
			return isActive && !destroyRequested;
		}

	protected:

		//이미 beginPlay 이벤트를받았는지 여부
		bool hasBeganPlay = false;


		bool isActive = true;

		//현재 프레임에 삭제요청 받았는지
		bool destroyRequested = false;



	};

}
