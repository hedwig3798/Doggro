#pragma once
#include "Entity.h"

class ManagerSet;
class QuestManager;
class LoadMapData;

class Human : public Entity
{
public:
	Human(std::string _name, ManagerSet* _managerSet, OBJECT_TYPE _type, LoadMapData* _objectManager, QuestManager* _questManager);
	virtual ~Human();

	virtual void Update(float _deltaTime) override;

private:
	ManagerSet* managerSet;
	QuestManager* questManager;
	
};

