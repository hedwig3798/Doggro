#pragma once
#include "Entity.h"

class ManagerSet;
class LoadMapData;
class StaticCollider;
class AObject;

class WallCollider : public Entity
{
public:
	WallCollider(std::string _name, ManagerSet* _managerSet, OBJECT_TYPE _type, LoadMapData* _objectManager);
	virtual ~WallCollider();


private:
	ManagerSet* managerSet;
	LoadMapData* objectManager;
	AObject* aObject;
};

