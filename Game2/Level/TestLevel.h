#pragma once
#include "Common/Common.h";
#include "Level/Level.h"



class TestLevel :public wanted::Level
{
	RTTI_DECLARATIONS(TestLevel, Level)

public:
	TestLevel();


private:
	void LoadMap(const char* filename);
};

