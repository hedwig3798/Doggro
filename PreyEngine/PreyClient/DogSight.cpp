#include "DogSight.h"

#include "FilterCollider.h"
#include "ManagerSet.h"
#include "QuestManager.h"

#include "Transform.h"
#include "DogSightScript.h"

DogSight::DogSight(std::string _name, ManagerSet* _managerSet, OBJECT_TYPE _type, QuestManager* _questManager)
	: Entity(_name, _managerSet, _type)
{
	managerSet = _managerSet;
	questManager = _questManager;

	GetComponent<Transform>()->SetPosition(Vector3(130.0f, 50.0f, 0.0f));

	CreateComponent<DogSightScript>(this);

	CreateComponent2<FilterCollider>(this, managerSet->GetCollisionManager());
	GetComponent<FilterCollider>()->SetSize(Vector3(150.f, 150.f, 150.f));
	GetComponent<FilterCollider>()->Start();
}

DogSight::~DogSight()
{
}
