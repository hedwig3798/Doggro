#pragma once
#include <string>
#include "Entity.h"

class ManagerSet;
class LoadMapData;
class AObject;

class Closet :public Entity
{
public:
	Closet(std::string _name, ManagerSet* _managerSet, OBJECT_TYPE _type, LoadMapData* _objectManager);
	virtual ~Closet();

private:
	ManagerSet* managerSet;
	LoadMapData* objectManager;
	AObject* aObject;
};

