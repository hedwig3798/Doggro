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
/// Unity Event function�� ���� �ߴ�.
/// 
/// �ٸ� �Ŵ������� ������ ������ ���� ������ �� ����ϰ� �����ְ� �ϴ� ������ �Ѵ�.
/// 
/// </summary>
class EventManager
{
public:
	EventManager();
	~EventManager();

	// ���� ���� ManagerSet�� �ֱ� ���� ���� ����� �ϴ� �͵�
	void Awake(HWND _hwnd, PreyGameEngine* _gameEngine);
	
	// ��? �̰� ��� �������??
	//void OnEnable(); 

	// �� �� Manager���� ���� ��������.
	void Start();

 	// ������ �ӵ��� ������ ������ �Ҹ���, ���� ����� �� �� ����Ѵ�.
	void FixedUpdate(float _deltaTime);

 	// ������ �� �� ���� ����Ǹ� ���� Object�� Update �Ѵ�. (�ִϸ��̼� ����)
	void Update(float _deltaTime);

 	// ī�޶� ����� �� ����Ѵ�.
	void LateUpdate(float _deltaTime);
	
 	// Update�� ������ �׸���.
	void Render();

	// ���� Finalize�� ���� ���̴�.
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

