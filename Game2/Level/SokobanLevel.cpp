#include "SokobanLevel.h"
#include "Actor/Player.h"
#include "Actor/Wall.h"
#include "Actor/Ground.h"
#include "Actor/Box.h"
#include "Actor/Target.h"
#include "Utill/utill.h"
#include <iostream>


/*
#: 벽
.: 바닥
p: 플레이어
b: 박스
t: 타겟
*/







SokobanLevel::SokobanLevel()
{
	//AddNewActor(new Player());
	
	//LoadMap("stage1.txt");
	//LoadMap("map.txt");
	LoadMap("stage3.txt");
}

void SokobanLevel::Draw()
{
	super::Draw();

	//게임 클리어인 경우. 메시지 출력.
	if (isGameClear)
	{
		Utill::SetConsolePosition(Vector2(30, 0));
		Utill::SetConsoleTextColor(Color::White);

		std::cout << "Game Clear!";
	}
}

void SokobanLevel::LoadMap(const char* filename)
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
			++targetScore;
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

bool SokobanLevel::CanMove(const Vector2& playerPos, const Vector2& nextPos)
{
	//레벨에 있는 박스 엑터 모으기.
	//박스는 플레이어가 밀기등 추가적으로 처리하기 때문.

	std::vector<Actor*> boxes;


	//박스 저장.
	for (Actor* const actor : actors)
	{
		if (actor->IsTypeOf<Box>())
		{
			boxes.emplace_back(actor);
			continue;
		}
	}


	//이동하려는곳에 뭐가 있는지 검사.
	Actor* boxActor = nullptr;
	for (Actor* const box : boxes)
	{
		if (box->GetPosition() == nextPos)
		{
			boxActor = box;
			break;
		}
	}


	//경우의 수 처리
	//이동하려는 곳에 박스가 있다.
	if (boxActor)
	{
		//1:박스를 이동시키려는 위치에 다른 박스가 또 있는지 확인
		//두 위치 사이에서 이동 방향 구하기.(벡터의 뺼셈 활용)
		//이동 로직에서 두벡터를 더한다는것은
		//둘중 하나는 위치이고 다른 하나는 벡터
		Vector2 direction = nextPos - playerPos;
		Vector2 newPos = boxActor->GetPosition() + direction;


		//박스 검색.
		for (Actor* const otherbox : boxes)
		{
			//앞에서 검색한 박스와 같다면 건너뛰기
			if (otherbox == boxActor)
			{
				continue;
			}

			//다른 박스가 있는지 확인
			if (otherbox->GetPosition() == newPos)
			{
				//두개의 박스가 겹쳐진곳으로는 이동불가.

				return false;
			}


		}



		//검색
		for (Actor* const actor : actors)
		{
			///2. 벽이면 이동 불가.
			if (actor->GetPosition() == newPos)
			{
				if (actor->IsTypeOf<Wall>())
				{
					return false;
				}

				//그라운드 또는 타겟이면 이동가능.
				if (actor->IsTypeOf<Ground>() ||
					actor->IsTypeOf<Target>())
				{
					//이동처리.
					boxActor->SetPosition(newPos);

					//: 게임 점수 확인...
					isGameClear = CheckGameClear();

					return true;
				}

			}

		}



	}//end box.



	//박스가 없다!.
	for (Actor* const actor : actors)
	{
		//이동하려는 위치에 있는 엑터 검색.
		if (actor->GetPosition() == nextPos)
		{
			// 이 엑터가 벽인지 확인.
			if (actor->IsTypeOf<Wall>())
			{
				return false;
			}

			//그라운드 또는 타겟.
			return true;
		}
	}


	//에러...
	return false;
}

bool SokobanLevel::CheckGameClear()
{

	//타겟 위에 있는 박수의 수 검증.
	int currentScore = 0;
	

	//벡터에 박스 및 타겟 저장.
	// 
	std::vector<Actor*> boxes;
	std::vector<Actor*> targets;

	for (Actor* const actor : actors)
	{
		if( actor->IsTypeOf<Box>() )
		{
			boxes.emplace_back(actor);
			continue;
		}
		if (actor->IsTypeOf<Target>())
		{
		
			targets.emplace_back(actor);
			continue;
		}
	}


	//점수 확인
	for (Actor* const box : boxes)
	{
		for (Actor* const target : targets)
		{
			if (box->GetPosition() == target->GetPosition())
			{
				currentScore += 1;
			}
		}
	}



	return currentScore == targetScore;
}

