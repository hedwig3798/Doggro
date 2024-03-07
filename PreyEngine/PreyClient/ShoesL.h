#pragma once
#include <string>
#include "Entity.h"

class ManagerSet;
class LoadMapData;
class AObject;
class DogScript;

class ShoesL :public Entity
{
public:
	ShoesL(std::string _name, ManagerSet* _managerSet, OBJECT_TYPE _type, LoadMapData* _objectManager, DogScript* _dogScript);
	virtual ~ShoesL();

	virtual void Update(float _deltaTime) override;
private:
	ManagerSet* managerSet;
	LoadMapData* objectManager;
	AObject* aObject;
	DogScript* dogScript;

};

