#include "ManagerSet.h"

ManagerSet::ManagerSet()
	: timeManager{}, pathManager{}, inputManager{}, sceneManager{}, eventManager{}, cameraManager{}, preyGame{}, preyGraphics{}, collisionManager{}
{

}

ManagerSet::~ManagerSet()
{

}



void ManagerSet::Initalize(IGraphicsEngine* _graphics, PreyGameEngine* _gameEngine, InputManager* _inputManager, TimeManager* _timeManager, SceneManager* _sceneManager, PathManager* _pathManager, EventManager* _eventManger, CameraManager* _cameraManager, CollsionManager* _collisionManager)
{
	preyGame = _gameEngine;
	preyGraphics = _graphics;
	inputManager = _inputManager;
	timeManager = _timeManager;
	pathManager = _pathManager;
	sceneManager = _sceneManager;
	eventManager = _eventManger;
	cameraManager = _cameraManager;
	collisionManager = _collisionManager;
}
