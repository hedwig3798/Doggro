#pragma once
#include "Entity.h"

class ManagerSet;
class LoadMapData;
class BoxCollider;
class AObject;

class ClockCollider : public Entity
{
public:
	ClockCollider(std::string _name, ManagerSet* _managerSet, OBJECT_TYPE _type, LoadMapData* _objectManager);
	virtual ~ClockCollider();


private:
	ManagerSet* managerSet;
	LoadMapData* objectManager;
	AObject* aObject;
};

