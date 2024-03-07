#pragma once
#include <string>
#include "Entity.h"

class ManagerSet;
class LoadMapData;
class QuestManager;
class AObject;
class DogScript;

class Soju : public Entity
{
public:
	Soju(std::string _name, ManagerSet* _managerSet, OBJECT_TYPE _type, LoadMapData* _objectManager, QuestManager* _questManager, DogScript* _dogScript);
	virtual ~Soju();

	virtual void Update(float _deltaTime) override;
private:
	ManagerSet* managerSet;
	LoadMapData* objectManager;
	QuestManager* questManager;
	AObject* aObject;
	DogScript* dogScript;

};

