#pragma once
#include <string>
#include "Entity.h"

class ManagerSet;
class LoadMapData;
class AObject;

class Bed : public Entity
{
public:
	Bed(std::string _name, ManagerSet* _managerSet, OBJECT_TYPE _type, LoadMapData* _objectManager);
	virtual ~Bed();

private:
	ManagerSet* managerSet;
	LoadMapData* objectManager;
	AObject* aObject;

};

