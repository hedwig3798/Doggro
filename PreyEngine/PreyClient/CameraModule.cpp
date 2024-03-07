#include "CameraModule.h"
#include "Entity.h"
#include "DogFSM.h"
#include "ICamera.h"
#include "DogScript.h"
#include "Transform.h"
#include "ManagerSet.h"
#include "InputManager.h"
#include "PreyGameEngine.h"
#include "IGraphicsEngine.h"
#include "CollsionManager.h"

CameraModule::CameraModule(Entity* _entity)
	: Component(_entity, "CameraModule")
{
	managerSet = entity->GetManagerset();
	
	dogInitalizePositon.resize(3);
	dogAddMovePosition.resize(3);

	float screenWidth = managerSet->GetPreyGame()->GetScreenWidth();
	float screenHeight = managerSet->GetPreyGame()->GetScreenHeight();

	managerSet->GetGraphics()->CreateCamera(&camera, screenHeight, screenWidth);
	managerSet->GetGraphics()->SetMainCamera(camera);
	camera->SetPosition(deltaPostionX, deltaPostionY, deltaPostionZ);
	camera->SetRotation(angleX, angleY, angleZ);
	//camera->AddFOV()
}

CameraModule::~CameraModule()
{
	
}

void CameraModule::Update(float _deltaTime)
{
	managerSet->GetCollisionManager()->PickedObject(camera);
	InputManager* inputManager = managerSet->GetInputManager();
	Transform* transform = entity->GetComponent<Transform>();

	mainCamera = entity->GetManagerset()->GetGraphics()->IsMainCamera(camera);
	if (!mainCamera) return;
	
	mouseWheel = managerSet->GetPreyGame()->GetMouseWheelData();
	
 	Vector3 zero = { 0.f,0.f,0.f };

	// 강아지 FSM에 있던 speed 에서 가져온다.
	DogFSM* dogFSM = entity->GetComponent<DogFSM>();
	float moveSpeed = dogFSM->GetSpeed();

	std::vector<float> dogMoveSpeed = dogFSM->GetDirectSpeed();

	std::vector<float> direct = { 0.f, 0.f, 0.f };

	/// 충돌하면 카메라가 움직이지 않게 해야 
	bool isCollision = entity->GetComponent<DogScript>()->GetIsCollision();

	if (isCollision)
	{
		return;
	}

	if (dogMoveSpeed != direct && currentZoom != zoomMax)
	{
		camera->Traslation(dogMoveSpeed[0], dogMoveSpeed[1], dogMoveSpeed[2]);

		// 줌을 했을 때 이동한 거리만큼 다시 돌려놔야 한다.
		if (firstZoom)
		{
			dogAddMovePosition[0] += dogMoveSpeed[0];
			dogAddMovePosition[1] += dogMoveSpeed[1];
			dogAddMovePosition[2] += dogMoveSpeed[2];
		}
	}

 	// 휠 키를 통해 줌 인 / 줌아웃 기능
	if (mouseWheel != 0)
	{
		// 휠 위로
		if (mouseWheel >= 0)
		{
			currentZoom -= 0.1f;

			if (currentZoom <= zoomMin)
			{
				currentZoom = zoomMin;
				mouseWheel = 0.0f;				
				managerSet->GetPreyGame()->SetMouseWheelData(mouseWheel);
				return;
			}

			if (!firstZoom)
			{
				Vector3 position = transform->GetPosition();
				dogInitalizePositon[0] = position.x;
				dogInitalizePositon[1] = position.y;
				dogInitalizePositon[2] = position.z;

				camera->Traslation(dogInitalizePositon[0], 0, dogInitalizePositon[2]);
				firstZoom = true;
				mouseWheel = 0.0f;
				managerSet->GetPreyGame()->SetMouseWheelData(mouseWheel);
				camera->MoveFoward(moveSpeed);
				return;
			}
			camera->MoveFoward(moveSpeed);
			mouseWheel = 0.0f;
			managerSet->GetPreyGame()->SetMouseWheelData(mouseWheel);
		}
		// 휠 아래로
		else
		{
			currentZoom += 0.1f;

			if (currentZoom > zoomMax)
			{
				currentZoom = zoomMax;
				mouseWheel = 0.0f;
				managerSet->GetPreyGame()->SetMouseWheelData(mouseWheel);

				if (firstZoom)
				{
					// 초기 위치에 있던 위치로 되돌리고 이동한 위치들을 되돌린다.
					camera->Traslation(-dogInitalizePositon[0], 0, -dogInitalizePositon[2]);
					camera->Traslation(-dogAddMovePosition[0], -dogAddMovePosition[1], -dogAddMovePosition[2]);
					// 더한 값들을 초기화 해줘야 한다.
					dogAddMovePosition[0] = 0.0f;
					dogAddMovePosition[1] = 0.0f;
					dogAddMovePosition[2] = 0.0f;
					camera->MoveFoward(-moveSpeed);
					firstZoom = false;
				}
				return;
			}
			
			camera->MoveFoward(-moveSpeed);


			mouseWheel = 0.0f;
			managerSet->GetPreyGame()->SetMouseWheelData(mouseWheel);
		}
	}
// 	std::vector<float> cameraCurrentPosition = camera->GetPostion();
// 
// 	if (cameraCurrentPosition[1] > deltaPostionY && cameraCurrentPosition[2] < deltaPostionZ)
// 	{
// 		float overX = cameraCurrentPosition[0] - deltaPostionX;
// 		float overY = cameraCurrentPosition[1] - deltaPostionY;
// 		float overZ = cameraCurrentPosition[2] - deltaPostionZ;
// 
// 		camera->Traslation(-overX, -overY, -overZ);
// 	}
}

void CameraModule::ZoomIn(float _deltaTime)
{
	Transform* transform = entity->GetComponent<Transform>();
	DogFSM* dogFSM = entity->GetComponent<DogFSM>();
	float moveSpeed = dogFSM->GetSpeed();

	if (count < 1000)
	{
		Zoom = true;
		if (!zoomIn)
		{
			Vector3 position = transform->GetPosition();
			dogInitalizePositon[0] = position.x;
			dogInitalizePositon[1] = position.y;
			dogInitalizePositon[2] = position.z;

			camera->Traslation(dogInitalizePositon[0], 0, dogInitalizePositon[2]);
			zoomIn = true;
			camera->MoveFoward(100.f);
			return;
		}

		camera->MoveFoward(1.f);
		count++;
	}
	else Zoom = false;
}
