#pragma once
#include <string>
#include "Entity.h"

class ManagerSet;
class LoadMapData;
class AObject;

class Wall : public Entity
{
public:
	Wall(std::string _name, ManagerSet* _managerSet, OBJECT_TYPE _type, LoadMapData* _objectManager);
	virtual ~Wall();

private:
	ManagerSet* managerSet;
	LoadMapData* objectManager;
	AObject* aObject;

};

