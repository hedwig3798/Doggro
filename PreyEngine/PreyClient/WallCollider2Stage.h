#pragma once
#include "Entity.h"

class ManagerSet;
class LoadMapData;
class StaticCollider;
class AObject;

class WallCollider2Stage : public Entity
{
public:
	WallCollider2Stage(std::string _name, ManagerSet* _managerSet, OBJECT_TYPE _type, LoadMapData* _objectManager);
	virtual ~WallCollider2Stage();


private:
	ManagerSet* managerSet;
	LoadMapData* objectManager;
	AObject* aObject;

};

