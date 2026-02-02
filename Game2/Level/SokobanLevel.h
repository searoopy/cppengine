#pragma once
#include "Common/Common.h";
#include "Level/Level.h"
#include "Interface/ICanPlayerMove.h"


class SokobanLevel :public wanted::Level , public ICanPlayerMove
{
	RTTI_DECLARATIONS(SokobanLevel, Level)

public:
	SokobanLevel();

	//이벤트 함수 오버라이드.
	virtual void Draw() override;

private:
	void LoadMap(const char* filename);

	// ICanPlayerMove을(를) 통해 상속됨
	virtual	bool CanMove(const Vector2& playerPos, const Vector2& nextPos) override;


	//게임 클리어 확인 함수.
	bool CheckGameClear();

private:
	//획득해야하는 목표점수.
	int targetScore = 0;

	//게임 클리어 여부를 알려주는 변수.
	bool isGameClear = false;
};

