#include "Renderer.h"
#include "Utill/utill.h"
#include "ScreenBuffer.h"



namespace wanted
{

	Renderer* Renderer::instance = nullptr;

	Renderer::Renderer(const Vector2& screenSize)
		: screenSize(screenSize)
	{
		instance = this;

		//프레임 객체 생성.
		const int buffercount = screenSize.x * screenSize.y;
		frame = new Frame(buffercount);
		frame->Clear(screenSize);


		//이중 버퍼 배열.
		screenBuffers[0] = new  ScreenBuffer(screenSize);
		screenBuffers[1] = new  ScreenBuffer(screenSize);
		screenBuffers[0]->Clear();
		screenBuffers[1]->Clear();


		Present();
		//ScreenBuffer* screenBuffers[2] = {};


	}
	Renderer::~Renderer()
	{
		SafeDelete(frame);

		for(ScreenBuffer*& buffer : screenBuffers)
		{
			SafeDelete(buffer);
		}
	}

	void Renderer::Submit(const char* text, const Vector2& position, Color color, int sortingOrder)
	{
		RenderCommand command;
		command.text = text;
		command.position = position;
		command.color = color;
		command.sortingOrder = sortingOrder;

		renderQueue.emplace_back(command);
	}

	void Renderer::Present()
	{
		//버퍼 교환.
		SetConsoleActiveScreenBuffer(
			GetCurrentBuffer()->GetBuffer()
		);


		//인덱스 교체
		currentBufferIndex = 1 - currentBufferIndex;
	}


	void Renderer::Draw()
	{
		//화면 지우기.
		Clear();

		//전제조건: 레벨의 모든 액터가 렌더러에 submit을 완료.
		//렌더큐  순회하면서 프레임 채우기
		for (const RenderCommand& command : renderQueue)
		{
			if (!command.text)
			{
				continue;
			}

			if (
				command.position.y < 0 ||
				command.position.y >= screenSize.y)
			{
				continue;
			}


			//화면에 그릴 문자열길이.
			const int length = static_cast<int>(strlen(command.text));

			//안그려도 되면 건너띔
			if (length <= 0)
			{
				continue;
			}

			//x좌표 기준으로 화면에서 벗어났는지 확인
			const int startx = command.position.x;
			const int endx = command.position.x + length - 1;


			if( endx<0 ||
				startx >= screenSize.x)
			{
				continue;
			}


			//시작위치
			const int visibleStart = startx < 0 ? 0 : startx;
			const int visibleEnd = endx >= screenSize.x ? screenSize.x - 1 : endx;
			
			for (int x = visibleStart; x <= visibleEnd; x++)
			{
				const int sourceInput = x - startx;



				//프레임 2차원 문자배열 인덱스
				const int index =
					(command.position.y * screenSize.x ) +x;


				//그리기 우선순위 비교
				if (frame->sortingOrderArray[index] >
					command.sortingOrder)
				{
					continue;
				}


				//데이터 기록
		
				frame->charInfo[index].Char.AsciiChar
					= command.text[sourceInput];
				frame->charInfo[index].Attributes
					= (WORD)command.color;

				// 우선순위 업데이트.
				frame->sortingOrderArray[index]
					= command.sortingOrder;
			}
		}



		//그리기.
		GetCurrentBuffer()->Draw(frame->charInfo);


		//버퍼 교환.,
		Present();


		//렌더큐 지우기.
		renderQueue.clear();
	}


	void Renderer::Clear()
	{
		//화면 지우기.
		//1. 프레임 지우기
		frame->Clear(screenSize);

		//2. 콘솔 버퍼 지우기
		GetCurrentBuffer()->Clear();
	}

	ScreenBuffer* Renderer::GetCurrentBuffer() const
	{
		return screenBuffers[currentBufferIndex];
	}

	Renderer& Renderer::Get()
	{
		if(!instance)
		{
			MessageBoxA(
				nullptr,
				"Renderer instance is null!",
				"Renderer Get Error",
				MB_OK
			);
			__debugbreak();
		}

		return *instance;
	}
	

	Renderer::Frame::Frame(int bufferCount)
	{
		charInfo = new CHAR_INFO[bufferCount];
		memset(charInfo, 0, sizeof(CHAR_INFO) * bufferCount);


		sortingOrderArray = new int[bufferCount];
		memset(sortingOrderArray, 0, sizeof(int) * bufferCount);
	}

	Renderer::Frame::~Frame()
	{
		SafeDeleteArray(charInfo);
		SafeDeleteArray(sortingOrderArray);
	}

	void Renderer::Frame::Clear(const Vector2& screenSize)
	{

		const int width = (int)screenSize.x;
		const int height = (int)screenSize.y;

		for(int y = 0; y < height; ++y)
		{
			for(int x = 0; x < width; ++x)
			{
				const int index = y * width + x;
				charInfo[index].Char.AsciiChar = ' ';
				charInfo[index].Attributes = static_cast<WORD>(Color::Black);
				sortingOrderArray[index] = -1;
			}
		}
	}

}