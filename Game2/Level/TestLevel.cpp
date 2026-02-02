#include "TestLevel.h"
#include "Actor/Player.h"
#include "Actor/Wall.h"
#include "Actor/Ground.h"
#include "Actor/Box.h"
#include "Actor/Target.h"

#include <iostream>


/*
#: 벽
.: 바닥
p: 플레이어
b: 박스
t: 타겟
*/







TestLevel::TestLevel()
{
	//AddNewActor(new Player());
	
	LoadMap("stage1.txt");
}

void TestLevel::LoadMap(const char* filename)
{

	//파일 로드
	//최종 파일 경로 만들기. ("../assets/filenammmmmmmmmmmmmmmmmmm")
	char path[2048] = {};
	sprintf_s(path, sizeof(char) * 2048, "../assets/%s", filename);



	//파일 열기.
	FILE* file = nullptr;
	fopen_s(&file, path, "rt");

	if (!file)
	{
		std::cout << "failed to open map file\n";


		//디버그 모드에서 중단점으로 중단해주는 기능.
		__debugbreak();
	}


	//맵읽기.
	//맵 크기 파악. //포인터를 파일의 끝으로 이동.
	fseek(file, 0, SEEK_END);


	//이 위치를 읽기,
	size_t filesize = ftell(file);


	//file position 처음으로 돌리기
	rewind(file);


	//파일에서 데이터 읽어올 버퍼 생성.
	char* data = new char[filesize + 1];

	//데이터 읽기.
	size_t readSize = fread(data, sizeof(char), filesize, file);

	//TEST: 읽어온 문자열을 분석 파싱.
	//std::cout << data;
	int index = 0;

	//객체를 생성할 위치값.
	wanted::Vector2 pos;

	while (true)
	{
		if (index >= filesize)
		{
			
			break;
		}

		//캐릭터 읽기
		char mapCharacter = data[index];
		++index;

		if(mapCharacter == '\n')
		{
			//std::cout << '\n';
			++pos.y;
			pos.x = 0;
			continue;
		}


		//한 문자씩 처리.
		switch (mapCharacter)
		{
		case '1':
		case '#':
			//std::cout << '#';
			AddNewActor(new Wall(pos));
			break;
		case '.':
			AddNewActor(new Ground(pos));
			//std::cout << ' ';
			break;
		case 'p':
			//std::cout << 'P';
			AddNewActor(new Player(pos));
			AddNewActor(new Ground(pos));
			break;
		case 'b':

			//std::cout << 'B';

			//박스가 옴겨졌을때 그 밑에 땅이 있어야함
			AddNewActor(new Box(pos));
			AddNewActor(new Ground(pos));
			break;
		case 't':
			//std::cout << 'T';
			AddNewActor(new Target(pos));
			//AddNewActor(new Ground(pos));
			break;
		}

		/*
		#: 벽
		.: 바닥
		p: 플레이어
		b: 박스
		t: 타겟
		*/


		// x 좌표 증가 처리.
		++pos.x;

	}

	//사용한 버퍼 해제
	delete[] data;

	fclose(file);
}
