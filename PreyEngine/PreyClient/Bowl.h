#pragma once
#include <string>
#include "Entity.h"

class ManagerSet;
class QuestManager;
class LoadMapData;
class AObject;
class DogScript;
class BowlScript;

class Bowl : public Entity
{
public:
	Bowl(std::string _name, ManagerSet* _managerSet, OBJECT_TYPE _type, LoadMapData* _objectManager, QuestManager* _questManager, DogScript* _dogScript);
	virtual ~Bowl();

	virtual void Update(float _deltaTime) override;

private:
	ManagerSet* managerSet;
	QuestManager* questManager;
	LoadMapData* objectManager;
	AObject* aObject;
	DogScript* dogScript;
};

