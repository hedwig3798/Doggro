#pragma once

class TimeManager;
class InputManager;
class CameraManager;
class SceneManager;
class PathManager;
class IGraphicsEngine;
class EventManager;
class CollsionManager;
class PreyGameEngine;

class ManagerSet
{
public:
	ManagerSet();
	~ManagerSet();

	void Initalize(
		IGraphicsEngine* _graphics,
		PreyGameEngine* _gameEngine,
		InputManager* _inputManager,
		TimeManager* _timeManager,
		SceneManager* _sceneManager,
		PathManager* _pathManager,
		EventManager* _eventManger,
		CameraManager* _cameraManager,
		CollsionManager* _collisionManager
		);

	TimeManager* GetTimeManager() const { return timeManager; }
	PathManager* GetPathManager() const { return pathManager; }
	InputManager* GetInputManager() const { return inputManager; }
	SceneManager* GetSceneManager() const { return sceneManager; }
	EventManager* GetEventManager() const { return eventManager; }
	CameraManager* GetCameraManager() const { return cameraManager; }
	PreyGameEngine* GetPreyGame() const { return preyGame; }
	IGraphicsEngine* GetGraphics() const { return preyGraphics; }
	CollsionManager* GetCollisionManager() const { return collisionManager; }

private:

	TimeManager* timeManager;
	PathManager* pathManager;
	InputManager* inputManager;
	SceneManager* sceneManager;
	EventManager* eventManager;
	CameraManager* cameraManager;
	PreyGameEngine* preyGame;
	IGraphicsEngine* preyGraphics;
	CollsionManager* collisionManager;
};

