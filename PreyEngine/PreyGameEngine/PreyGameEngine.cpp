#include "PreyGameEngine.h"
#include <windows.h>


#include "IGraphicsEngine.h"
#include "ResourceManager.h"
#include "CameraManager.h"
#include "SceneManager.h"
#include "InputManager.h"
#include "PathManager.h"
#include "TimeManager.h"

/// test
#include "TestScene.h"

#include "EventManager.h"

#include "Entity.h"
#include "Transform.h"
#include "Collider.h"
#include "ManagerSet.h"


PreyGameEngine::PreyGameEngine()
	: deltaTime{}, elapsedTime{}, mouseWheelData{}, eventManager{}, screenHeight{}, screenWidth{}
{

}

PreyGameEngine::~PreyGameEngine()
{

}

void PreyGameEngine::Initalize(HWND _hwnd)
{
	RECT rect = {};
	GetWindowRect(_hwnd, &rect);

	screenWidth = rect.right - rect.left;
	screenHeight = rect.bottom - rect.top;

	eventManager = new EventManager();
	eventManager->Awake(_hwnd, this);
	eventManager->Start();
}

void PreyGameEngine::Update()
{
	/// Unity Event Function�� �����ؼ� Game Engine�� Update�� ��������.
	/// ��� Game Engine�� Event Function ������ ������ �� ���� ������?

	// �ð� Update
	deltaTime = static_cast<float>(eventManager->GetManagerSet()->GetTimeManager()->Update());

 	// Ű �Է� Update
	eventManager->GetManagerSet()->GetInputManager()->Update();

	// frame �̰� 50 �������̶���� ? 1�ʴ� / 50���� ��� = 0.02 �׷��� 50 �������̷�! -�̱���-
	constexpr float FIXED_DELTA_TIME = 0.02f;
	elapsedTime += deltaTime;

	if (elapsedTime >= FIXED_DELTA_TIME)
		isElapsedTimeZero = false;
	
	eventManager->Update(deltaTime);

	while (isElapsedTimeZero == false)
	{

		elapsedTime -= FIXED_DELTA_TIME;
		eventManager->FixedUpdate(FIXED_DELTA_TIME);

		if (elapsedTime <= 0.f)
		{
			isElapsedTimeZero = true;
			break;
		}
	}

	
	eventManager->LateUpdate(deltaTime);

	//SoundManager::GetInstance()->Update();
	dt += deltaTime;
}

void PreyGameEngine::Render()
{
	eventManager->Render();
}

void PreyGameEngine::Finalize()
{
	eventManager->Finalize();
}
