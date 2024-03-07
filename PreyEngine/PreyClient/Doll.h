#pragma once
#include <string>
#include "Entity.h"

class ManagerSet;
class LoadMapData;
class QuestManager;
class AObject;
class DogScript;

class Doll :public Entity
{
public:
	Doll(std::string _name, ManagerSet* _managerSet, OBJECT_TYPE _type, LoadMapData* _objectManager, QuestManager* _questManager, DogScript* _dogScript);
	virtual ~Doll();

	virtual void Update(float _deltaTime) override;
private:
	ManagerSet* managerSet;
	QuestManager* questManager;
	LoadMapData* objectManager;
	AObject* aObject;
	DogScript* dogScript;

};

