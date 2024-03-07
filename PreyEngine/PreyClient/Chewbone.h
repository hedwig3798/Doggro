#pragma once
#include <string>
#include "Entity.h"

class ManagerSet;
class LoadMapData;
class AObject;
class QuestManager;
class DogScript;

class Chewbone : public Entity
{
public:
	Chewbone(std::string _name, ManagerSet* _managerSet, OBJECT_TYPE _type, LoadMapData* _objectManager, QuestManager* _questManager, DogScript* _dogScript);
	virtual ~Chewbone();

	virtual void Update(float _deltaTime) override;

private:
	ManagerSet* managerSet;
	QuestManager* questManager;
	LoadMapData* objectManager;
	AObject* aObject;
	DogScript* dogScript;
};

