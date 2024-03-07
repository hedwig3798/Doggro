#pragma once
#include <string>
#include "Entity.h"

class ManagerSet;
class LoadMapData;
class AObject;
class DogScript;
class QuestManager;
class LeashScript;

class Leash : public Entity
{
public:
	Leash(std::string _name, ManagerSet* _managerSet, OBJECT_TYPE _type, LoadMapData* _objectManager, QuestManager* _questManager, DogScript* _dogScript);
	virtual ~Leash();

	virtual void Update(float _deltaTime) override;
private:
	ManagerSet* managerSet;
	QuestManager* questManager;
	LoadMapData* objectManager;
	AObject* aObject;
	DogScript* dogScript;
};

