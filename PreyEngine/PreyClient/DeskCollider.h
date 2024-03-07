#pragma once
#include "Entity.h"

class ManagerSet;
class LoadMapData;
class StaticCollider;
class AObject;

class DeskCollider : public Entity
{
public:
	DeskCollider(std::string _name, ManagerSet* _managerSet, OBJECT_TYPE _type, LoadMapData* _objectManager);
	virtual ~DeskCollider();


private:
	ManagerSet* managerSet;
	LoadMapData* objectManager;
	AObject* aObject;
};

