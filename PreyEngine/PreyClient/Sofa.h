#pragma once
#include <string>
#include "Entity.h"

class ManagerSet;
class LoadMapData;
class AObject;

class Sofa :public Entity
{
public:
	Sofa(std::string _name, ManagerSet* _managerSet, OBJECT_TYPE _type, LoadMapData* _objectManager);
	virtual ~Sofa();

private:
	ManagerSet* managerSet;
	LoadMapData* objectManager;
	AObject* aObject;

};

