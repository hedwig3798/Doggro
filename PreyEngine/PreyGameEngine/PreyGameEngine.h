#pragma once
#include "headers.h"

class EventManager;

/// <summary>
/// Game Engine���� � �͵��� ������� �ұ�?
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

	// Mouse Wheel Data ���� Getter/Setter
	float GetMouseWheelData() const { return mouseWheelData; }
	void SetMouseWheelData(float val) { mouseWheelData = val; }

	float GetScreenHeight() const { return screenHeight; }
	float GetScreenWidth() const { return screenWidth; }

	EventManager* GetEventManager() const { return eventManager; }

private:
	// ��� �ð�
	float elapsedTime;
	bool isElapsedTimeZero;
	float deltaTime;
	
	// ���콺 �� �Է� �ޱ� ���� �ʿ��ϴ�.
	float mouseWheelData;

	// Window â size
	float screenHeight;
	float screenWidth;

	float dt = 0.0f;

	EventManager* eventManager;
	
};

