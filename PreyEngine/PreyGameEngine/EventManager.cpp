#include "EventManager.h"

#include "CameraManager.h"
#include "SceneManager.h"
#include "InputManager.h"
#include "PathManager.h"
#include "TimeManager.h"
#include "CollsionManager.h"
#include "ManagerSet.h"

#include "Scene.h"
#include "TestScene.h"
#include "TestScene2.h"

#include "PreyGameEngine.h"
#include "IGraphicsEngine.h"

EventManager::EventManager()
{

}

EventManager::~EventManager()
{

}

/// <summary>
/// handle Window가 필요하거나 Manager끼리 연결하기 위해서 필요하다.
/// </summary>
/// <param name="_hwnd"></param>
void EventManager::Awake(HWND _hwnd, PreyGameEngine* _gameEngine)
{
	// manager Set에 들어가기 전에 필요하다.
	CreateGrapicsEngine(&preyGraphicsEngine);
	preyGraphicsEngine->Initialize(_hwnd);

	managerSet = new ManagerSet();
	pathManager = new PathManager();
	timeManager = new TimeManager();
	sceneManager = new SceneManager();
	eventManager = new EventManager();
	inputManager = new InputManager();
	cameraManager = new CameraManager();
	collisionManager = new CollsionManager();

	managerSet->Initalize(preyGraphicsEngine, _gameEngine, inputManager, timeManager, sceneManager, pathManager, eventManager, cameraManager, collisionManager);
	cameraManager->Initalize(_hwnd, managerSet);
	inputManager->Initalize(_hwnd);
} 

void EventManager::Start()
{
	pathManager->Load();
//	SoundManager::GetInstance()->Initialize(pathManager);
	timeManager->Initalize();
	//collisionManager->Initialize(managerSet);

	// prey GameEngine initalize 후에 추가하면 된다.
	
// 	여기에 씬 추가 생성을 해야 한다.
   	//TestScene* testScene = new TestScene("TestScene1");
   	//TestScene2* testScene2 = new TestScene2("TestScene2");
   
   	// 여기서 씬 추가
   	//sceneManager->CreateScene(testScene);
   
   
   //	sceneManager->CreateScene(testScene2);
   
   	// 초기 씬 설정
   //	sceneManager->SetCurrentScene(testScene);
   
   	// 씬 시작
   	//sceneManager->Initalize(managerSet);
   	 	 	 	
}

void EventManager::FixedUpdate(float _deltaTime)
{
	// 물리 계산
	collisionManager->Update(_deltaTime);
}

void EventManager::Update(float _deltaTime)
{
	sceneManager->Update(_deltaTime);
}

void EventManager::LateUpdate(float _deltaTime)
{
	cameraManager->Update(_deltaTime);
}

void EventManager::Render()
{	
	sceneManager->Render();
}

void EventManager::Finalize()
{
	sceneManager->Finalize();
	collisionManager->Finalize();

	//SoundManager::GetInstance()->DestoryInstance();
	delete managerSet;
	delete pathManager;
	delete timeManager;
	delete sceneManager;
	delete eventManager;
	delete inputManager;
	delete cameraManager;
	delete collisionManager;
}
