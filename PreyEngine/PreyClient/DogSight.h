#pragma once
#include "Entity.h"

class ManagerSet;
class QuestManager;
class FilterCollider;

class DogSight : public Entity
{
public:
	DogSight(std::string _name, ManagerSet* _managerSet, OBJECT_TYPE _type, QuestManager* _questManager);
	virtual ~DogSight();


private:
	ManagerSet* managerSet;
	QuestManager* questManager;
	
};

