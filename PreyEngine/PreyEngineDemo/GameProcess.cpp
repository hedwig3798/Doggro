#include "GameProcess.h"
#include "PreyGameEngine.h"
#include "TimeManager.h"

// Call back WndProc에서 MouseWheel을 사용하려면 전역으로 된 것이 필요하다.
PreyGameEngine* gPreyEngine;

/// <summary>
/// Gameprocess 본체 완성
/// 2024.01.02
/// </summary>
GameProcess::GameProcess()
	:msg(), hWnd(0), preyGameEngine{}
{

}

GameProcess::~GameProcess()
{
	delete preyGameEngine;
}

void GameProcess::Initalize(HINSTANCE hInstance)
{
	/// 윈도우 초기화
	wchar_t szAppName[] = L"Shoebill Engine";
	WNDCLASSEXW wcex = {};

	wcex.cbSize = sizeof(WNDCLASSEX);

	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = GameProcess::WndProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = hInstance;
	wcex.hIcon = LoadIcon(hInstance, IDI_APPLICATION);
	wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wcex.lpszMenuName = nullptr;
	wcex.lpszClassName = szAppName;
	wcex.hIconSm = LoadIcon(wcex.hInstance, IDI_APPLICATION);

	RegisterClassExW(&wcex);

	hWnd = CreateWindowW(szAppName, szAppName, WS_OVERLAPPEDWINDOW,
		300, 300, static_cast<int>(screenWidth), static_cast<int>(screenHeight), NULL, NULL, hInstance, NULL);

	if (!hWnd)
	{
		return;
	}

	ShowWindow(hWnd, SW_SHOWNORMAL);
	UpdateWindow(hWnd);

	RECT nowRect;
	DWORD _style = (DWORD)GetWindowLong(hWnd, GWL_STYLE);
	DWORD _exstyle = (DWORD)GetWindowLong(hWnd, GWL_EXSTYLE);

	GetWindowRect(hWnd, &nowRect);

	RECT newRect;
	newRect.left = 0;
	newRect.top = 0;
	newRect.right = 1920;
	newRect.bottom = 1080;

	//AdjustWindowRectEx(&newRect, _style, NULL, _exstyle);
	//AdjustWindowRectEx(&newRect, _style, NULL, _exstyle);

	// 클라이언트 영역보다 윈도 크기는 더 커야 한다. (외곽선, 타이틀 등)
	int _newWidth = (newRect.right - newRect.left);
	int _newHeight = (newRect.bottom - newRect.top);

	SetWindowPos(hWnd, HWND_NOTOPMOST, nowRect.left, nowRect.top,
		_newWidth, _newHeight, SWP_SHOWWINDOW);


	// Prey Game Engine 시작 및 Window Proc를 사용하기 위한 전역 변수 선언
	preyGameEngine = new PreyGameEngine();
	gPreyEngine = preyGameEngine;
	preyGameEngine->Initalize(hWnd);
}

void GameProcess::Update()
{
	/// 메인 루프
	while (true)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			if (msg.message == WM_QUIT) break;

			DispatchMessage(&msg);
		}
		else
		{
			// 무언가 작동하는 부분
			preyGameEngine->Update();
			preyGameEngine->Render();
		}
	}
}

void GameProcess::Finalize()
{
	preyGameEngine->Finalize();
}

LRESULT CALLBACK GameProcess::WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_DESTROY:
		{
		PostQuitMessage(0);
		}
		break;
	case WM_MOUSEWHEEL:
		{
			// 여기서 휠 드래그가 된다.
			float wheelDelta = GET_WHEEL_DELTA_WPARAM(wParam);
			gPreyEngine->SetMouseWheelData(wheelDelta);
		}
		break;
	default:
		{
			return DefWindowProc(hWnd, message, wParam, lParam);
		}
		break;
	}
	return 0;
}
