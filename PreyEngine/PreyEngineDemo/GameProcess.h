#pragma once
#include <windows.h>


/// <summary>
/// 엔진 만들기 시작
/// 2023.12.29
/// 최명기
/// </summary>

class PreyGameEngine;

class GameProcess
{
public:
	GameProcess();
	~GameProcess();

	void Initalize(HINSTANCE hInstance);
	void Update();
	void Finalize();

	static LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

	float GetScreenWidth() const { return screenWidth; }
	float GetScreenHeight() const { return screenHeight; }

private:
	HWND hWnd;
	MSG msg;

	float screenWidth = 1920.0;
	float screenHeight = 1080.0f;

	PreyGameEngine* preyGameEngine;
};  
