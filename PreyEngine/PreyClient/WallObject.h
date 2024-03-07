#pragma once
#include <string>
#include "Entity.h"

class ManagerSet;
class LoadMapData;
class AObject;

class WallObject :public Entity
{
public:
	WallObject(std::string _name, ManagerSet* _managerSet, OBJECT_TYPE _type, LoadMapData* _objectManager);
	virtual ~WallObject();

private:
	ManagerSet* managerSet;
	LoadMapData* objectManager;
	AObject* aObject;

};

