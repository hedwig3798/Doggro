#pragma once
#include <string>
#include "Entity.h"

class ManagerSet;
class LoadMapData;
class AObject;
class DogScript;

class Clock :public Entity
{
public:
	Clock(std::string _name, ManagerSet* _managerSet, OBJECT_TYPE _type, LoadMapData* _objectManager, DogScript* _dogScript);
	virtual ~Clock();

	virtual void Update(float _deltaTime) override;
private:
	ManagerSet* managerSet;
	LoadMapData* objectManager;
	AObject* aObject;
	DogScript* dogScript;

};

