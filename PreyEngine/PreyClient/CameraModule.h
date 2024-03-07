#pragma once
#include "Component.h"

class ManagerSet;
class ICamera;

class CameraModule : public Component
{
public:
	CameraModule(Entity* _entity);
	virtual ~CameraModule();

	// 이거 하기 전에 Manager를 받아와야 하는데
	virtual void Update(float _deltaTime) override;

	void ZoomIn(float _deltaTime);
	ICamera* GetCamera() const { return camera; }
	bool GetMainCamera() const { return mainCamera; }

	bool Zoom = true;
	bool firstZoom = false;
private:
	bool mainCamera = false;
	bool zoomIn = false;
	
	float dt = 0.0f;

	ICamera* camera;
	ManagerSet* managerSet;

	float deltaPostionX = -770.f;
	float deltaPostionY = 980.f;
	float deltaPostionZ = -930.f;

	float angleX = 0.7f;
	float angleY = 16.5f;
	float angleZ = 0.0f;

	// Zoom Max Min
	float zoomMax = 2.0f;
	float zoomMin = 1.0f;
	float currentZoom = 2.0f;

	float mouseWheel;
	int count = 0;

	std::vector<float> dogInitalizePositon;
	std::vector<float> dogAddMovePosition;
};
