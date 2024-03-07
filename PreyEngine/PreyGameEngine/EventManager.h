#pragma once
#include "headers.h"

class CameraManager;
class SceneManager;
class InputManager;
class PathManager;
class TimeManager;
class CollsionManager;
class PreyGameEngine;
class IGraphicsEngine;
class Scene;

class ManagerSet;


/// <summary>
/// Unity Event function을 참고 했다.
/// 
/// 다른 매니저들을 가지고 있으며 게임 엔진을 더 깔끔하게 보여주게 하는 역할을 한다.
/// 
/// </summary>
class EventManager
{
public:
	EventManager();
	~EventManager();

	// 시작 전에 ManagerSet에 넣기 전에 실행 해줘야 하는 것들
	void Awake(HWND _hwnd, PreyGameEngine* _gameEngine);
	
	// 음? 이건 어떻게 사용하지??
	//void OnEnable(); 

	// 이 때 Manager들을 연결 시켜주자.
	void Start();

 	// 프레임 속도가 낮으면 여러번 불리고, 물리 계산은 이 때 계산한다.
	void FixedUpdate(float _deltaTime);

 	// 프레임 당 한 번만 실행되며 각종 Object를 Update 한다. (애니메이션 포함)
	void Update(float _deltaTime);

 	// 카메라 계산할 때 사용한다.
	void LateUpdate(float _deltaTime);
	
 	// Update가 끝나면 그린다.
	void Render();

	// 각종 Finalize도 있을 것이다.
	void Finalize();
	
	ManagerSet* GetManagerSet() const { return managerSet; }
private:
	Scene* scene = {};

	CameraManager* cameraManager = {};
	SceneManager* sceneManager = {};
	InputManager* inputManager = {};
	PathManager* pathManager = {};
	TimeManager* timeManager = {};
	CollsionManager* collisionManager = {};
	IGraphicsEngine* preyGraphicsEngine = {};
	EventManager* eventManager = {};
	ManagerSet* managerSet = {};
};

