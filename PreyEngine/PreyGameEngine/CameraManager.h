#pragma once
#include "headers.h"

class IGraphicsEngine;
class InputManager;
class TimeManager;
class ManagerSet;
class ICamera;

/// <summary>
/// 카메라를 관리하는 매니저
/// 카메라의 정보를 가져오기 위해 게임 엔진에 있는 Get, Set을 사용해야 한다.
/// 
/// 2024.01.15 chlaudrl
/// </summary>
class CameraManager 
{
public:
	CameraManager();
	CameraManager(float _screenHight, float _screenWidth);
	virtual ~CameraManager();

	void Initalize(HWND _hwnd, ManagerSet* _managerSet);
	void Update(float _deltaTime);


	float GetCameraX() const { return cameraX; }
	float GetCameraY() const { return cameraY; }
	float GetCameraZ() const { return cameraZ; }

	std::vector<float> GetPosition();
	std::vector<float> GetClickVector(int _x, int _y) ;

	// CreateCamera 만들어서 그래픽스에서 가져온다.
	// Update에서 사용할 것이다!
	ICamera* GetCamera() { return this->camera; };

private:
	float moveSpeed = 50.0f;
	float cameraMoveSpeed = 10.0f;

	// 이전 좌표 X, Y
	float previousX;
	float previousY;

	// Debug용 카메라 Manager 위치
	float cameraX;
	float cameraY;
	float cameraZ;

	ICamera* camera;
	IGraphicsEngine* graphics;
	ManagerSet* managerSet;
};