#pragma once
#include <string>
#include "Entity.h"

class ManagerSet;
class LoadMapData;
class AObject;

class Cabinet :public Entity
{
public:
	Cabinet(std::string _name, ManagerSet* _managerSet, OBJECT_TYPE _type, LoadMapData* _objectManager);
	virtual ~Cabinet();

private:
	ManagerSet* managerSet;
	LoadMapData* objectManager;
	AObject* aObject;
};

