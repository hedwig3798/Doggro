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
	/// Unity Event Function을 참고해서 Game Engine의 Update를 구현하자.
	/// 사실 Game Engine은 Event Function 만으로 굴러갈 수 있지 않을까?

	// 시간 Update
	deltaTime = static_cast<float>(eventManager->GetManagerSet()->GetTimeManager()->Update());

 	// 키 입력 Update
	eventManager->GetManagerSet()->GetInputManager()->Update();

	// frame 이게 50 프레임이라던데 ? 1초당 / 50번의 장면 = 0.02 그래서 50 프레임이래! -이기태-
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
