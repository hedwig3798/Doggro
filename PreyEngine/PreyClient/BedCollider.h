#pragma once
#include "Entity.h"

class ManagerSet;
class LoadMapData;
class StaticCollider;
class AObject;

class BedCollider : public Entity
{
public:
	BedCollider(std::string _name, ManagerSet* _managerSet, OBJECT_TYPE _type, LoadMapData* _objectManager);
	virtual ~BedCollider();


private:
	ManagerSet* managerSet;
	LoadMapData* objectManager;
	AObject* aObject;
};

