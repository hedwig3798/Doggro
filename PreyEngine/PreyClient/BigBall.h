#pragma once
#include <string>
#include "Entity.h"
#include "Collider.h"
#include "Script.h"

class ManagerSet;
class LoadMapData;
class AObject;
class DogScript;

class BigBall : public Entity
{
public:
	BigBall(std::string _name, ManagerSet* _managerSet, OBJECT_TYPE _type, LoadMapData* _objectManager, DogScript* _dogScript);
	virtual ~BigBall();

	virtual void Update(float _deltaTime) override;
public:
	bool CollisionCheck();

private:
	ManagerSet* managerSet;
	LoadMapData* objectManager;
	AObject* aObject;
	DogScript* dogScript;

	Collision ballCollision;
};


