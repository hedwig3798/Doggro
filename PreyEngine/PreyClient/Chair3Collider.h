#pragma once
#include "Entity.h"

class ManagerSet;
class LoadMapData;
class StaticCollider;
class AObject;

class Chair3Collider : public Entity
{
public:
	Chair3Collider(std::string _name, ManagerSet* _managerSet, OBJECT_TYPE _type, LoadMapData* _objectManager);
	virtual ~Chair3Collider();

private:
	ManagerSet* managerSet;
	LoadMapData* objectManager;
	AObject* aObject;
};

