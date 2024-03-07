#pragma once
#include "Entity.h"

class ManagerSet;
class LoadMapData;
class StaticCollider;
class AObject;

class ChairCollider : public Entity
{
public:
	ChairCollider(std::string _name, ManagerSet* _managerSet, OBJECT_TYPE _type, LoadMapData* _objectManager);
	virtual ~ChairCollider();

private:
	ManagerSet* managerSet;
	LoadMapData* objectManager;
	AObject* aObject;
};

