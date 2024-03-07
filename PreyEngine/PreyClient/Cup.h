#pragma once
#include <string>
#include "Entity.h"

class AObject;

class LoadMapData;
class ManagerSet;
class QuestManager;
class DogScript;

class Cup :public Entity
{
public:
	Cup(std::string _name, ManagerSet* _managerSet, OBJECT_TYPE _type, LoadMapData* _objectManager, QuestManager* _questManager, DogScript* _dogScript);
	virtual ~Cup();

	virtual void Update(float _deltaTime) override;
private:
	ManagerSet* managerSet;
	QuestManager* questManager;
	LoadMapData* objectManager;
	AObject* aObject;	
	DogScript* dogScript;

};

