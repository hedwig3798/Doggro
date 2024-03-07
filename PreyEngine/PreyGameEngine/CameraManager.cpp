#include "CameraManager.h"
#include "InputManager.h"
#include "TimeManager.h"
#include "ICamera.h"
#include "ManagerSet.h"
#include "IGraphicsEngine.h"
#include "PreyGameEngine.h"

CameraManager::CameraManager()
	: camera{}, graphics{}, managerSet{}, previousX(0.0f), previousY(0.0f), cameraX(0.0f), cameraY(0.0f), cameraZ(0.0f)
{
	
}

CameraManager::CameraManager(float _screenHight, float _screenWidth)
	: camera{}, graphics{}, managerSet{}, previousX(0.0f), previousY(0.0f), cameraX(0.0f), cameraY(0.0f), cameraZ(0.0f)
{
		
}

CameraManager::~CameraManager()
{

}

void CameraManager::Initalize(HWND _hwnd, ManagerSet* _managerSet)
{
	this->managerSet = _managerSet;

	graphics = managerSet->GetGraphics();

	float screenHeight = managerSet->GetPreyGame()->GetScreenHeight();
 	float screenWidth = managerSet->GetPreyGame()->GetScreenWidth();

	graphics->CreateCamera(&camera, screenHeight, screenWidth);
	graphics->SetMainCamera(camera);
	camera->SetPosition(-500.f, 500.f, 500.f);
}

void CameraManager::Update(float _deltaTime)
{
	InputManager* inputmanager = managerSet->GetInputManager();
	float mouseWheel = managerSet->GetPreyGame()->GetMouseWheelData();

	float deltaTime = _deltaTime;
	
	

	// SetMainCamera Debug Test
// 	if (inputmanager->IsKeyState(KEY::F1, KEY_STATE::TAP))
// 	{
// 		graphics->SetMainCamera(camera);
// 	}

	// Unreal 우클릭 누르면 시점을 조절할 수 있다.
	if (inputmanager->IsKeyState(KEY::RMOUSE, KEY_STATE::HOLD))
	{
		// Mouse의 이동속도를 조절한다.
		if (mouseWheel != 0)
		{
			if (mouseWheel > 0)
			{
				// 위쪽 휠일 때 양수
				moveSpeed += 5.0f;
				mouseWheel = 0.0f;
				managerSet->GetPreyGame()->SetMouseWheelData(mouseWheel);
			}
			else
			{
				// 아래쪽 휠일 때 음수
				moveSpeed -= 5.0f;
				camera->MoveFoward(-moveSpeed * _deltaTime);
				mouseWheel = 0.0f;
				managerSet->GetPreyGame()->SetMouseWheelData(mouseWheel);
			}
		}
		
		// 마우스 움직임을 통해 시점을 자유롭게 볼 수 있다.
		if (inputmanager->IsKeyState(KEY::RMOUSE, KEY_STATE::HOLD))
		{
			float currentX = static_cast<float>(inputmanager->GetCurrentMousePos().x);
			float currentY = static_cast<float>(inputmanager->GetCurrentMousePos().y);
			camera->RotateRight((currentX - previousX) * cameraMoveSpeed * deltaTime);
			camera->RotateUp((currentY - previousY) * cameraMoveSpeed * deltaTime);
		}

		// Down
		if (inputmanager->IsKeyState(KEY::Q, KEY_STATE::HOLD))
		{
			camera->MoveUP(-moveSpeed * deltaTime);
		}

		// Front
		if (inputmanager->IsKeyState(KEY::W, KEY_STATE::HOLD))
		{
			camera->MoveFoward(moveSpeed * deltaTime);
		}

		// Up
		if (inputmanager->IsKeyState(KEY::E, KEY_STATE::HOLD))
		{
			camera->MoveUP(moveSpeed * deltaTime);
		}

		// Left
		if (inputmanager->IsKeyState(KEY::A, KEY_STATE::HOLD))
		{
			camera->MoveRight(-moveSpeed * deltaTime);
		}

		// Back
		if (inputmanager->IsKeyState(KEY::S, KEY_STATE::HOLD))
		{
			camera->MoveFoward(-moveSpeed * deltaTime);
		}

		// Right
		if (inputmanager->IsKeyState(KEY::D, KEY_STATE::HOLD))
		{
			camera->MoveRight(moveSpeed * deltaTime);
		}
	}
	

	// 이전 좌표를 가지고 있는다.
	previousX = static_cast<float>(inputmanager->GetCurrentMousePos().x);
	previousY = static_cast<float>(inputmanager->GetCurrentMousePos().y);
}

std::vector<float> CameraManager::GetPosition()
{
	return this->camera->GetPostion(); 
}

std::vector<float> CameraManager::GetClickVector(int _x, int _y)
{
	return this->camera->GetClickVector(_x, _y);
}

