#pragma once
#include <string>
#include "Entity.h"

class ManagerSet;
class LoadMapData;
class AObject;

class Lighting : public Entity
{
public:
	Lighting(std::string _name, ManagerSet* _managerSet, OBJECT_TYPE _type, LoadMapData* _objectManager);
	virtual ~Lighting();

private:
	ManagerSet* managerSet;
	LoadMapData* objectManager;
	AObject* aObject;
};

