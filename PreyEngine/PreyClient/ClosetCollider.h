#pragma once
#include "Entity.h"

class ManagerSet;
class LoadMapData;
class StaticCollider;
class AObject;

class ClosetCollider : public Entity
{
public:
	ClosetCollider(std::string _name, ManagerSet* _managerSet, OBJECT_TYPE _type, LoadMapData* _objectManager);
	virtual ~ClosetCollider();


private:
	ManagerSet* managerSet;
	LoadMapData* objectManager;
	AObject* aObject;
};

