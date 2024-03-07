#pragma once
#include "Entity.h"

class ManagerSet;
class LoadMapData;
class StaticCollider;
class AObject;

class WallCollider2 : public Entity
{
public:
	WallCollider2(std::string _name, ManagerSet* _managerSet, OBJECT_TYPE _type, LoadMapData* _objectManager);
	virtual ~WallCollider2();


private:
	ManagerSet* managerSet;
	LoadMapData* objectManager;
	AObject* aObject;
};
