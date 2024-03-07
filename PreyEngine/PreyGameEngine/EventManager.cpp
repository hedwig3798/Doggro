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
/// handle Window�� �ʿ��ϰų� Manager���� �����ϱ� ���ؼ� �ʿ��ϴ�.
/// </summary>
/// <param name="_hwnd"></param>
void EventManager::Awake(HWND _hwnd, PreyGameEngine* _gameEngine)
{
	// manager Set�� ���� ���� �ʿ��ϴ�.
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

	// prey GameEngine initalize �Ŀ� �߰��ϸ� �ȴ�.
	
// 	���⿡ �� �߰� ������ �ؾ� �Ѵ�.
   	//TestScene* testScene = new TestScene("TestScene1");
   	//TestScene2* testScene2 = new TestScene2("TestScene2");
   
   	// ���⼭ �� �߰�
   	//sceneManager->CreateScene(testScene);
   
   
   //	sceneManager->CreateScene(testScene2);
   
   	// �ʱ� �� ����
   //	sceneManager->SetCurrentScene(testScene);
   
   	// �� ����
   	//sceneManager->Initalize(managerSet);
   	 	 	 	
}

void EventManager::FixedUpdate(float _deltaTime)
{
	// ���� ���
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
