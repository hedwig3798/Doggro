#pragma once
#include "headers.h"

class IGraphicsEngine;
class InputManager;
class TimeManager;
class ManagerSet;
class ICamera;

/// <summary>
/// ī�޶� �����ϴ� �Ŵ���
/// ī�޶��� ������ �������� ���� ���� ������ �ִ� Get, Set�� ����ؾ� �Ѵ�.
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

	// CreateCamera ���� �׷��Ƚ����� �����´�.
	// Update���� ����� ���̴�!
	ICamera* GetCamera() { return this->camera; };

private:
	float moveSpeed = 50.0f;
	float cameraMoveSpeed = 10.0f;

	// ���� ��ǥ X, Y
	float previousX;
	float previousY;

	// Debug�� ī�޶� Manager ��ġ
	float cameraX;
	float cameraY;
	float cameraZ;

	ICamera* camera;
	IGraphicsEngine* graphics;
	ManagerSet* managerSet;
};