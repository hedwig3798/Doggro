#include "CameraComponent.h"
#include "IGraphicsEngine.h"
#include "PreyGameEngine.h"
#include "InputManager.h"
#include "ManagerSet.h"
#include "Entity.h"
#include "ICamera.h"

#include "Transform.h"

CameraComponent::CameraComponent(Entity* _entity)
	: Component(_entity, "Camera"), camera{}, moveSpeed{}, managerSet{}, previousMatrix{}, currnetMatrix{}
{
	managerSet = _entity->GetManagerset();

	float screenWidth = managerSet->GetPreyGame()->GetScreenWidth();
	float screenHeight = managerSet->GetPreyGame()->GetScreenHeight();

	managerSet->GetGraphics()->CreateCamera(&camera, screenWidth, screenHeight);
	managerSet->GetGraphics()->SetMainCamera(camera);

	Vector3 position = entity->GetComponent<Transform>()->GetPosition();
	camera->SetPosition(position.x - 100.f, position.y + 100.f, position.z + 100.f);
}




CameraComponent::~CameraComponent()
{

}

void CameraComponent::Update(float _deltaTime)
{
	InputManager* inputManager = managerSet->GetInputManager();

	moveSpeed = 20.0f;

	float mouseWheel = managerSet->GetPreyGame()->GetMouseWheelData();
	
	if (inputManager->IsKeyState(KEY::F2, KEY_STATE::TAP))
	{
		managerSet->GetGraphics()->SetMainCamera(camera);
	}

	// ī�޶� Entity�� ��ġ�� ���� ī�޶� �̵��ϰԲ� ��������.

	// ������Ʈ�� ���� ��ġ�� ��������.
	currnetMatrix = GetEntity()->GetComponent<Transform>()->GetFinalMatrix();
	

	// Translate�� �ش��ϴ� x �κ�
	if (currnetMatrix._41 - previousMatrix._41 > 0)
	{
		camera->MoveRight(-moveSpeed * _deltaTime);
	}
	else if (currnetMatrix._41 - previousMatrix._41 == 0)
	{}
	else
	{
		camera->MoveRight(moveSpeed * _deltaTime);
	}


	// Translate�� �ش��ϴ� y �κ�
	if (currnetMatrix._43 - previousMatrix._43 > 0)
	{
		// ��
		camera->MoveUP(-moveSpeed * _deltaTime);
	}
	else if (currnetMatrix._43 - previousMatrix._43 == 0)
	{
		// ��� ����
	}
	else
	{
		// �Ʒ�
		camera->MoveUP(moveSpeed * _deltaTime);
	}

	
	if (mouseWheel != 0)
	{
		if (mouseWheel > 0)
		{
			// ���
			camera->MoveFoward(moveSpeed * _deltaTime);
			mouseWheel = 0.0f;
			managerSet->GetPreyGame()->SetMouseWheelData(mouseWheel);
		}
		else
		{
			// ����
			camera->MoveFoward(-moveSpeed * _deltaTime);
			mouseWheel = 0.0f;
			managerSet->GetPreyGame()->SetMouseWheelData(mouseWheel);
		}
	}



// 	// Down
// 	if (inputManager->IsKeyState(KEY::Q, KEY_STATE::HOLD))
// 	{
// 		camera->MoveUP(-moveSpeed * _deltaTime);
// 	}
// 
// 	// Front
// 	if (inputManager->IsKeyState(KEY::W, KEY_STATE::HOLD))
// 	{
// 		camera->MoveFoward(moveSpeed * _deltaTime);
// 	}
// 
// 	// Up
// 	if (inputManager->IsKeyState(KEY::E, KEY_STATE::HOLD))
// 	{
// 		camera->MoveUP(moveSpeed * _deltaTime);
// 	}
// 
// 	// Left
// 	if (inputManager->IsKeyState(KEY::A, KEY_STATE::HOLD))
// 	{
// 		camera->MoveRight(-moveSpeed * _deltaTime);
// 	}
// 
// 	// Back
// 	if (inputManager->IsKeyState(KEY::S, KEY_STATE::HOLD))
// 	{
// 		camera->MoveFoward(-moveSpeed * _deltaTime);
// 	}
// 
// 	// Right
// 	if (inputManager->IsKeyState(KEY::D, KEY_STATE::HOLD))
// 	{
// 		camera->MoveRight(moveSpeed * _deltaTime);
// 	}

	// ������Ʈ�� ���� ��ġ�� ��������.
	previousMatrix = GetEntity()->GetComponent<Transform>()->GetFinalMatrix();
}

void CameraComponent::Render()
{

	int i = 0;
}
