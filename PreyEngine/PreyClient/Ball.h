#pragma once
#include <string>

#include "Entity.h"

class ManagerSet;
class LoadMapData;
class QuestManager;
class AObject;
class DogScript;

class Ball : public Entity
{
public:
	Ball(std::string _name, ManagerSet* _managerSet, OBJECT_TYPE _type, LoadMapData* _objectManager, QuestManager* _questManager, DogScript* _dogScript);
	virtual ~Ball();

	virtual void Update(float _deltaTime) override;
private:
	ManagerSet* managerSet;
	LoadMapData* objectManager;
	QuestManager* questManager;
	AObject* aObject;
	DogScript* dogScript;

};

