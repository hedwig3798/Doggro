#pragma once
#include <windows.h>

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

	float screenWidth = 1920.0f;
	float screenHeight = 1080.0f;

	PreyGameEngine* preyGameEngine;
};
