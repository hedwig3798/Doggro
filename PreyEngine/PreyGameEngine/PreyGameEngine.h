#pragma once
#include "headers.h"

class EventManager;

/// <summary>
/// Game Engine에는 어떤 것들이 담겨져야 할까?
/// 
/// 24-01-16 LYS
/// </summary>
class PreyGameEngine
{
public:
	PreyGameEngine();
	~PreyGameEngine();

	void Initalize(HWND _hwnd);
	void Update();
	void Render();
	void Finalize();

	// Mouse Wheel Data 값을 Getter/Setter
	float GetMouseWheelData() const { return mouseWheelData; }
	void SetMouseWheelData(float val) { mouseWheelData = val; }

	float GetScreenHeight() const { return screenHeight; }
	float GetScreenWidth() const { return screenWidth; }

	EventManager* GetEventManager() const { return eventManager; }

private:
	// 경과 시간
	float elapsedTime;
	bool isElapsedTimeZero;
	float deltaTime;
	
	// 마우스 휠 입력 받기 위해 필요하다.
	float mouseWheelData;

	// Window 창 size
	float screenHeight;
	float screenWidth;

	float dt = 0.0f;

	EventManager* eventManager;
	
};

