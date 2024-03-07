#pragma once
#include <string>
#include "Entity.h"

class ManagerSet;
class LoadMapData;
class AObject;

class Cloths : public Entity
{
public:
	Cloths(std::string _name, ManagerSet* _managerSet, OBJECT_TYPE _type, LoadMapData* _objectManager);
	virtual ~Cloths();

private:
	ManagerSet* managerSet;
	LoadMapData* objectManager;
	AObject* aObject;

};

