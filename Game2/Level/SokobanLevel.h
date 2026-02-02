#pragma once
#include "Common/Common.h";
#include "Level/Level.h"
#include "Interface/ICanPlayerMove.h"


class SokobanLevel :public wanted::Level , public ICanPlayerMove
{
	RTTI_DECLARATIONS(SokobanLevel, Level)

public:
	SokobanLevel();


private:
	void LoadMap(const char* filename);

	// ICanPlayerMove을(를) 통해 상속됨
	virtual	bool CanMove(const Vector2& playerPos, const Vector2& nextPos) override;

};

