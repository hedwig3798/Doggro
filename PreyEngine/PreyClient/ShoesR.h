#pragma once
#include <string>
#include "Entity.h"

class ManagerSet;
class LoadMapData;
class AObject;
class DogScript;

class ShoesR :public Entity
{
public:
	ShoesR(std::string _name, ManagerSet* _managerSet, OBJECT_TYPE _type, LoadMapData* _objectManager, DogScript* _dogScript);
	virtual ~ShoesR();

	virtual void Update(float _deltaTime) override;
private:
	ManagerSet* managerSet;
	LoadMapData* objectManager;
	AObject* aObject;
	DogScript* dogScript;

};

